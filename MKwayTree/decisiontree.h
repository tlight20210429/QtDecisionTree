#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <QObject>
#include "treenode.h"
class DecisionTree : public QObject
{
    Q_OBJECT
public:
    explicit DecisionTree(QObject *parent = nullptr);
    void setActionType(const QString &aType);
    QString getActionType() const;
    void setAttrList(const QStringList &attrList);
    QStringList getAttrList() const;
    void setDataList(const QStringList &dataList);
    TreeNode *getRootNode();
    void freeDecisionTree();
signals:
private:
    QString m_actionType;           //动作类型
    QStringList m_attrList;         //属性
    QStringList m_dataList;         //数据集
    TreeNode *m_rootNode;           //决策树根节点
};

#endif // DECISIONTREE_H
