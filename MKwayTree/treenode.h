#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>

class TreeNode : public QObject
{
    Q_OBJECT
public:
    explicit TreeNode(QObject *parent = nullptr);
    void setParentNode(TreeNode *node);
    void addSiblingNode(TreeNode *node);
    void addChildNode(TreeNode *node);
    void setEntropy(const double entropy);
    double getEntropy() const;
    void setGain(const double gain);
    double getGain() const;
    void setGainV(const double gainV);
    double getGainV() const;
    void setDataList(const QStringList &dataList);
    QStringList getDataList() const;
signals:
private:
    QString m_nodeName;                 //节点名称
    TreeNode *m_parentNode;             //父节点
    QList<TreeNode *> m_childNode;      //孩子节点
    QList<TreeNode *> m_siblingNode;    //兄弟节点
    double m_entropy;                   //节点的熵值
    double m_gain;                      //信息增益
    double m_gainV;                     //信息增益率
    QStringList m_dataList;             //数据子集
};

#endif // TREENODE_H
