#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include "filedeal.h"
#include <QPaintEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



#define DETECT_WIDTH      640
#define DETECT_HEIGHT     480
#define TEST_TIME         1000 //unit/s


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showDecisionTree();
    void decisionTree_training(ValueDef &val, ValueDef &valRole, int roleId);
protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
private slots:
    void on_actionOpen_triggered();
    void on_actionserialSet_triggered();
    void on_actionquit_triggered();
    void showValueArray(ValueDef &val, ValueDef &valRole, int roleId, quint64 msec);
    void threadFinised();
private:
    Ui::MainWindow *ui;
    QString m_filePath;
    FileDeal *m_filedeal;
    QPixmap m_pix;


};
#endif // MAINWINDOW_H
