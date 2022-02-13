#include "filedeal.h"
#include <QFile>
#include <QMessageBox>
#include <QTime>
#include <QtDebug>
static const QStringList g_funcList = {"filter", "mainfilter", "pre_notmain"};
QMutex FileDeal::m_mutex;
FileDeal::FileDeal(QObject *parent) : QThread(parent)
{
    QStringList attrList;
    m_sitDownTree = new DecisionTree;
    m_StandUpTree = new DecisionTree;
    m_holdSitDownTree = new DecisionTree;
    m_holdStandUpTree = new DecisionTree;
    m_GoTree = new DecisionTree;
    m_RunTree = new DecisionTree;
    m_JumpTree = new DecisionTree;
    m_sitDownTree->setActionType("sitDown");         //坐下
    m_holdSitDownTree->setActionType("holdSitDown"); //保持坐下
    m_StandUpTree->setActionType("standUp");         //站起来
    m_holdStandUpTree->setActionType("holdStandUp"); //保持站立姿势
    m_GoTree->setActionType("go");                   //走
    m_RunTree->setActionType("run");                 //跑
    m_JumpTree->setActionType("jump");               //跳
    attrList<<"X"<<"Y"<<"width"<<"height";
    m_sitDownTree->setAttrList(attrList);
    m_holdSitDownTree->setAttrList(attrList);
    m_StandUpTree->setAttrList(attrList);
    m_holdStandUpTree->setAttrList(attrList);
    m_GoTree->setAttrList(attrList);
    m_RunTree->setAttrList(attrList);
    m_JumpTree->setAttrList(attrList);
}

void FileDeal::parseFile(const QString &fileName)
{
    m_fileName = fileName;
}
void FileDeal::run()
{
    int typeId;
    QString line;
    QFile file(m_fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(nullptr, tr("open file failure!"), tr("can't open file %1").arg(m_fileName));
        return;
    }
    QTime starttime(0, 0, 0, 0);
    QTime endtime(0, 0, 0, 0);
    while(!file.atEnd()){
        line = file.readLine();
        int pos = line.indexOf('-');
        if(pos != -1){
            int timeEnd = line.indexOf(']');
            int typeEnd = line.lastIndexOf(':');
            QString typeStr = line.mid(timeEnd+2, typeEnd-timeEnd-2);
            typeId = g_funcList.indexOf(typeStr);
            if(typeId != 0)
                continue;
            QString timeStr = line.mid(pos+2, timeEnd-pos-2);
            QString dataStr = line.mid(typeEnd+2).trimmed();
            QStringList dataList = dataStr.split(" ");
            ValueDef *valueList=nullptr;
            ValueDef *roleValueList=nullptr;
            int buffer[4];
            int roleBuffer[4];
            int roleId;
            if(dataList.length() != 18)
                continue;
            roleId = dataList.at(0).toUInt();
            for(int i = 0; i < 4; i++){
                buffer[i] = dataList.at(i+1).toInt();
                roleBuffer[i] = dataList.at(5+i).toInt();
            }
            valueList = (ValueDef *)buffer;
            roleValueList = (ValueDef *)roleBuffer;
            quint64 msec = 0;
            msec = starttime.msecsTo(endtime);
            if(msec == 0){
                endtime = QTime::fromString(timeStr, "hh:mm:ss:zzz");
            }else{
                if(starttime.hour()==0&&starttime.minute()==0&&starttime.second()==0&&starttime.msec()==0){
                    starttime = endtime;
                }
                endtime = QTime::fromString(timeStr, "hh:mm:ss:zzz");
                msec = starttime.msecsTo(endtime);
            }
            FileDeal::m_mutex.lock();
            emit traning(*valueList, *roleValueList, roleId);
            //emit resultReady(*valueList, *roleValueList, roleId, msec);
        }
    }
    file.close();
}
/*
void FileDeal::run()
{
    int typeId;
    QString line;
    QFile file(m_fileName);
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        QMessageBox::warning(nullptr, tr("open file failure!"), tr("can't open file %1").arg(m_fileName));
        return;
    }
    QTime starttime(0, 0, 0, 0);
    QTime endtime(0, 0, 0, 0);
    while(!file.atEnd()){
        line = file.readLine();
        int pos = line.indexOf('-');
        if(pos != -1){
            int timeEnd = line.indexOf(']');
            int typeEnd = line.lastIndexOf(':');
            QString typeStr = line.mid(timeEnd+2, typeEnd-timeEnd-2);
            typeId = g_funcList.indexOf(typeStr);
            if(typeId != 0)
                continue;
            QString timeStr = line.mid(pos+2, timeEnd-pos-2);
            QString dataStr = line.mid(typeEnd+2).trimmed();
            QStringList dataList = dataStr.split(" ");
            ValueDef *valueList=nullptr;
            ValueDef *roleValueList=nullptr;
            int buffer[4];
            int roleBuffer[4];
            int roleId;
            if(dataList.length() != 18)
                continue;
            roleId = dataList.at(0).toUInt();
            for(int i = 0; i < 4; i++){
                buffer[i] = dataList.at(i+1).toInt();
                roleBuffer[i] = dataList.at(5+i).toInt();
            }
            valueList = (ValueDef *)buffer;
            roleValueList = (ValueDef *)roleBuffer;
            quint64 msec = 0;
            msec = starttime.msecsTo(endtime);
            if(msec == 0){
                endtime = QTime::fromString(timeStr, "hh:mm:ss:zzz");
            }else{
                if(starttime.hour()==0&&starttime.minute()==0&&starttime.second()==0&&starttime.msec()==0){
                    starttime = endtime;
                }
                endtime = QTime::fromString(timeStr, "hh:mm:ss:zzz");
                msec = starttime.msecsTo(endtime);
            }
            FileDeal::m_mutex.lock();
            emit traning(*valueList, *roleValueList, roleId);
            //emit resultReady(*valueList, *roleValueList, roleId, msec);
        }
    }
    file.close();
}
*/
