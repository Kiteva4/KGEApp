#include "TreeNode.h"
#include "TreeModelTest.h"

#include <QCoreApplication>
#include <QStringList>
#include <QMimeData>
#include <QIODevice>
#include <QDataStream>

TreeModelTest::TreeModelTest(const QStringList &modalities, QObject *parent)
    : QAbstractItemModel(parent)
{
    QStringList data = modalities;

    QVector<QVariant> rootData;

    for (const QString &header : modalities)
        rootData << header;

    m_rootNode = new TreeNode(rootData, nullptr);
    setupModelData(data, m_rootNode);
}

TreeModelTest::TreeModelTest()
{
    QVector<QVariant> rootData;
    rootData << "WORLD";

    m_rootNode = new TreeNode(rootData, nullptr);

    tempItemList.push_front("1 obj");
    tempItemList.push_front("2 obj");
    tempItemList.push_front("3 obj");
    tempItemList.push_front("4 obj");
    tempItemList.push_front("5 obj");

    setupModelData(tempItemList, m_rootNode);

    setupModelData(tempItemList, getItem(index(0, 0)));
    setupModelData(tempItemList, getItem(index(0, 0, index(0,0))));
    setupModelData(tempItemList, getItem(index(1, 0, index(0,0))));
    setupModelData(tempItemList, getItem(index(2, 0, index(0,0))));
}

TreeModelTest::~TreeModelTest()
{
    delete m_rootNode;
}

int TreeModelTest::columnCount(const QModelIndex &parent) const
{
    return getItem(parent)->columnCount();
}

static const char s_treeNodeMimeType[] = "application/x-treenode";

//returns the mime type
QStringList TreeModelTest::mimeTypes() const
{
    return QStringList() << s_treeNodeMimeType;
}

//receives a list of model indexes list
QMimeData *TreeModelTest::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *mimeData = new QMimeData;
    QByteArray data; //a kind of RAW format for datas

    //QDataStream is independant on the OS or proc architecture
    //serialization of C++'s basic data types, like char, short, int, char *, etc.
    //Serialization of more complex data is accomplished
    //by breaking up the data into primitive units.
    QDataStream stream(&data, QIODevice::WriteOnly);
    QList<TreeNode *> nodes;

    //
    foreach (const QModelIndex &index, indexes) {
        TreeNode *node = getItem(index);
        if (!nodes.contains(node))
            nodes << node;
    }
    stream << QCoreApplication::applicationPid();
    stream << nodes.count();
    foreach (TreeNode *node, nodes) {
        stream << reinterpret_cast<qlonglong>(node);
    }
    mimeData->setData(s_treeNodeMimeType, data);
    return mimeData;
}

bool TreeModelTest::dropMimeData(const QMimeData *mimeData, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_ASSERT(action == Qt::MoveAction);
    Q_UNUSED(column)
    //test if the data type is the good one
    if (!mimeData->hasFormat(s_treeNodeMimeType)) {
        return false;
    }
    QByteArray data = mimeData->data(s_treeNodeMimeType);
    QDataStream stream(&data, QIODevice::ReadOnly);
    qint64 senderPid;
    stream >> senderPid;
    if (senderPid != QCoreApplication::applicationPid()) {
        // Let's not cast pointers that come from another process...
        return false;
    }
    TreeNode *parentNode = getItem(parent);
    Q_ASSERT(parentNode);
    int count;
    stream >> count;
    if (row == -1) {
        // valid index means: drop onto item. I chose that this should insert
        // a child item, because this is the only way to create the first child of an item...
        // This explains why Qt calls it parent: unless you just support replacing, this
        // is really the future parent of the dropped items.
        if (parent.isValid())
            row = 0;
        else
            // invalid index means: append at bottom, after last toplevel
            row = rowCount(parent);
    }
    for (int i = 0; i < count; ++i) {
        // Decode data from the QMimeData
        qlonglong nodePtr;
        stream >> nodePtr;
        TreeNode *node = reinterpret_cast<TreeNode *>(nodePtr);

        // Adjust destination row for the case of moving an item
        // within the same parent, to a position further down.
        // Its own removal will reduce the final row number by one.
        if (node->row() < row && parentNode == node->parentNode())
            --row;

        // Remove from old position
        removeNode(node);

        // Insert at new position
        //qDebug() << "Inserting into" << parent << row;
        beginInsertRows(parent, row, row);
        parentNode->insertChild(row, node);
        endInsertRows();
        ++row;
    }
    return true;
}

Qt::DropActions TreeModelTest::supportedDropActions() const
{
    return Qt::MoveAction;
}

Qt::DropActions TreeModelTest::supportedDragActions() const
{
    return Qt::MoveAction;
}

QVariant TreeModelTest::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeNode *node = getItem(index);
    return node->data(index.column());
}

Qt::ItemFlags TreeModelTest::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsDropEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QVariant TreeModelTest::headerData(int section, Qt::Orientation orientation,
                                   int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return m_rootNode->data(section);

    return QVariant();
}

//returns a pointer to the "index"
TreeNode * TreeModelTest::getItem(const QModelIndex &index) const
{
    if (!index.isValid())
        return m_rootNode;
    else
        return static_cast<TreeNode*>(index.internalPointer());
}

void TreeModelTest::removeNode(TreeNode *node)
{
    const int row = node->row();
    QModelIndex idx = createIndex(row, 0, node);
    beginRemoveRows(idx.parent(), row, row);
    node->parentNode()->removeChild(row);
    endRemoveRows();
}

QModelIndex TreeModelTest::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeNode *parentNode = getItem(parent);

    TreeNode *childNode = parentNode->child(row);
    if (childNode)
        return createIndex(row, column, childNode);
    else
        return QModelIndex();
}

QModelIndex TreeModelTest::parent(const QModelIndex &index) const
{
    TreeNode *childNode = getItem(index);
    if (childNode == m_rootNode)
        return QModelIndex();

    TreeNode *parentNode = childNode->parentNode();
    if (parentNode == m_rootNode)
        return QModelIndex();

    return createIndex(parentNode->row(), 0, parentNode);
}

int TreeModelTest::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
        return 0;

    TreeNode *parentNode = getItem(parent);
    return parentNode->childCount();
}

void TreeModelTest::setupModelData(const QStringList &lines, TreeNode *parent)
{
    QList<TreeNode*> parents;
    QList<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count())
    {
        int position = 0;
        while (position < lines[number].length())
        {
            if (lines[number].at(position) != ' ')
                break;
            ++position;
        }

        const QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            const QStringList columnStrings = lineData.split('\t', QString::SkipEmptyParts);

            QVector<QVariant> columnData;

            columnData.reserve(columnStrings.size());

            for (const QString &columnString : columnStrings)
                columnData << columnString;

            if (position > indentations.last())
            {
                if (parents.last()->childCount() > 0)
                {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            }
            else
            {
                while (position < indentations.last() && parents.count() > 0)
                {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new node to the current parent's list of children.
            parents.last()->appendChild(new TreeNode(columnData, parents.last()));
        }

        ++number;
    }
}
