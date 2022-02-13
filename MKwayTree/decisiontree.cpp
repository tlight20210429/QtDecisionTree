#include "decisiontree.h"

DecisionTree::DecisionTree(QObject *parent) : QObject(parent)
{
    m_rootNode = new TreeNode;
}

void DecisionTree::setActionType(const QString &aType)
{
    this->m_actionType = aType;
}

QString DecisionTree::getActionType() const
{
    return this->m_actionType;
}

void DecisionTree::setAttrList(const QStringList &attrList)
{
    this->m_attrList = attrList;
}

QStringList DecisionTree::getAttrList() const
{
    return this->m_attrList;
}

void DecisionTree::setDataList(const QStringList &dataList)
{
    this->m_dataList = dataList;
}

TreeNode *DecisionTree::getRootNode()
{
    return this->m_rootNode;
}

void DecisionTree::freeDecisionTree()
{

}
