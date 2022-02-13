#include "treenode.h"

TreeNode::TreeNode(QObject *parent) : QObject(parent)
{
    if(parent != nullptr)
        this->m_parentNode = qobject_cast<TreeNode*>(parent);
    else
        this->m_parentNode = nullptr;
    this->m_childNode.clear();
    this->m_siblingNode.clear();
    this->m_gain = 0;
    this->m_gainV = 0;
    this->m_entropy = 0;
    this->m_dataList.clear();
}

void TreeNode::setParentNode(TreeNode *node)
{
    this->m_parentNode = node;
}

void TreeNode::addSiblingNode(TreeNode *node)
{
    this->m_siblingNode.append(node);
}

void TreeNode::addChildNode(TreeNode *node)
{
    this->m_childNode.append(node);
}

void TreeNode::setEntropy(const double entropy)
{
    this->m_entropy = entropy;
}

double TreeNode::getEntropy() const
{
    return this->m_entropy;
}

void TreeNode::setGain(const double gain)
{
    this->m_gain = gain;
}

double TreeNode::getGain() const
{
    return this->m_gain;
}

void TreeNode::setGainV(const double gainV)
{
    this->m_gainV = gainV;
}

double TreeNode::getGainV() const
{
    return this->m_gainV;
}

void TreeNode::setDataList(const QStringList &dataList)
{
    this->m_dataList = dataList;
}

QStringList TreeNode::getDataList() const
{
    return this->m_dataList;
}
