#ifndef FILEDEAL_H
#define FILEDEAL_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMetaType>
#include "decisiontree.h"

typedef struct
{
    int posX;
    int width;
    int height;
    int mean;
}ValueDef;

typedef struct
{
    int posX;
    int posY;
    int width;
    int height;
    int mean;
    int judge;
}DataListDef;

Q_DECLARE_METATYPE(ValueDef);

class FileDeal : public QThread
{
    Q_OBJECT

public:
    explicit FileDeal(QObject *parent = nullptr);
    void parseFile(const QString &fileName);
    static QMutex m_mutex;
    void run() override;
signals:
    void resultReady(ValueDef &val, ValueDef &valRole, int roleId, quint64 msec);
    void traning(ValueDef &val, ValueDef &valRole, int roleId);
private:
    QString m_fileName;
    DecisionTree *m_sitDownTree;
    DecisionTree *m_StandUpTree;
    DecisionTree *m_holdSitDownTree;
    DecisionTree *m_holdStandUpTree;
    DecisionTree *m_GoTree;
    DecisionTree *m_RunTree;
    DecisionTree *m_JumpTree;
    QList<DataListDef *> m_dataList;
};

#endif // FILEDEAL_H
