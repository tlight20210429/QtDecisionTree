#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QtDebug>
#include <QDesktopWidget>
#include <QTreeWidgetItem>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QScatterSeries>
#include <QTime>
#include <QPainter>

QT_CHARTS_USE_NAMESPACE


static const QColor clist[5] = {Qt::red, Qt::green, Qt::blue, Qt::yellow, Qt::black};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int i;
    m_filePath = ".";
    QDesktopWidget *desktop = QApplication::desktop();
    resize(DETECT_WIDTH<<1, 900);
 //   move((desktop->width()-this->width())/2, (desktop->height()-this->height())/2);
    move((desktop->width()-this->width())/2, 0);
    m_pix = QPixmap(size());
    m_pix.fill(Qt::white);
    setAutoFillBackground(true);
    QChart *chart = new QChart;
//    chart->setTitle("x and width changed");
    QChartView *chartView = new QChartView(chart, ui->tab_2);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(1);
    QStringList serNamelist = {"x", "width", "y", "height", "mean"};
    QScatterSeries *series = nullptr;
    for(i = 0; i < 2; i++){
        series = new QScatterSeries();
        series->setName(serNamelist.at(i));
        series->setMarkerSize(1);
        pen.setColor(clist[i]);
        series->setPen(pen);
        chart->addSeries(series);
    }
    chart->createDefaultAxes();
    QList<QAbstractAxis *> localAxes = chart->axes();
    QValueAxis *axisX = qobject_cast<QValueAxis*>(localAxes.at(0));
    QValueAxis *axisY = qobject_cast<QValueAxis*>(localAxes.at(1));
    axisX->setTitleText("s");
    axisX->setMax(TEST_TIME);
    axisY->setTitleText("pix");
    axisY->setMax(DETECT_WIDTH);
//    axisY->setTickCount(8);
//    axisY->setMinorTickCount(4);
    ui->verticalLayout_2->addWidget(chartView);

    chart = new QChart;
 //   chart->setTitle("y and height changed");
    chartView = new QChartView(chart, ui->tab_2);
    for(i = 2; i < 4; i++){
        series = new QScatterSeries();
        series->setName(serNamelist.at(i));
        pen.setColor(clist[i]);
        series->setPen(pen);
        series->setMarkerSize(1);
        chart->addSeries(series);
    }
    chart->createDefaultAxes();
    localAxes = chart->axes();
    axisX = qobject_cast<QValueAxis*>(localAxes.at(0));
    axisY = qobject_cast<QValueAxis*>(localAxes.at(1));
    axisX->setTitleText("s");
    axisX->setMax(TEST_TIME);
    axisY->setTitleText("pix");
    axisY->setMax(DETECT_HEIGHT);
    ui->verticalLayout_2->addWidget(chartView);

    chart = new QChart;
//    chart->setTitle("mean changed");
    chartView = new QChartView(chart, ui->tab_2);
    series = new QScatterSeries();
    series->setName(serNamelist.at(i));
    pen.setColor(clist[i]);
    series->setPen(pen);
    series->setMarkerSize(1);
    chart->addSeries(series);
    chart->createDefaultAxes();
    localAxes = chart->axes();
    axisX = qobject_cast<QValueAxis*>(localAxes.at(0));
    axisY = qobject_cast<QValueAxis*>(localAxes.at(1));
    axisX->setTitleText("s");
    axisX->setMax(TEST_TIME);
    axisY->setTitleText("pix");
    axisY->setMax(256);
    ui->verticalLayout_2->addWidget(chartView);
//**************************************************************

}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
 * 功能:显示读取到的数据
 * val:要显示的数据结构
 * return:None
 */
void MainWindow::showValueArray(ValueDef &val, ValueDef &valRole, int roleId, quint64 msec)
{
    QList<QChartView *> list = ui->tab_2->findChildren<QChartView *>(QString(), Qt::FindDirectChildrenOnly);
    QChart *xwidthChart = list.at(0)->chart();
    QChart *yheightChart = list.at(1)->chart();
    QChart *meanChart = list.at(2)->chart();
    QList<QAbstractSeries *> xwidthSeries = xwidthChart->series();
    QList<QAbstractSeries *> yheightSeries = yheightChart->series();
    QList<QAbstractSeries *> meanSeries = meanChart->series();
    QScatterSeries *xSeries = qobject_cast<QScatterSeries *>(xwidthSeries.at(0));
    QScatterSeries *widthSeries = qobject_cast<QScatterSeries *>(xwidthSeries.at(1));
    QScatterSeries *ySeries = qobject_cast<QScatterSeries *>(yheightSeries.at(0));
    QScatterSeries *heightSeries = qobject_cast<QScatterSeries *>(yheightSeries.at(1));
    QScatterSeries *meanSerie = qobject_cast<QScatterSeries *>(meanSeries.first());
    int sec = msec/1000;
    xSeries->append(sec, val.posX);
    widthSeries->append(sec, val.width);
    heightSeries->append(sec, val.height);
    meanSerie->append(sec, val.mean);
    if(sec > TEST_TIME){
        xSeries->clear();
        ySeries->clear();
        widthSeries->clear();
        heightSeries->clear();
        meanSerie->clear();
    }
    FileDeal::m_mutex.unlock();
}

void MainWindow::threadFinised()
{
  //  disconnect(m_filedeal, &FileDeal::resultReady, this, &MainWindow::showValueArray);
    disconnect(m_filedeal, &FileDeal::traning, this, &MainWindow::decisionTree_training);
    disconnect(m_filedeal, &FileDeal::finished, this, &MainWindow::threadFinised);
    delete m_filedeal;
}
/*
 * 功能:显示训练好的决策树
 * return:None
 */
void MainWindow::showDecisionTree()
{

}
/*
 * 功能:决策树训练
 * val:待训练的数据
 * return:None
 */
void MainWindow::decisionTree_training(ValueDef &val, ValueDef &valRole, int roleId)
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(&m_pix);
    painter.drawLine(QLineF(0,0,m_pix.width(),m_pix.height()));
    ui->label->setPixmap(m_pix);

}
void MainWindow::on_actionOpen_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(this, tr("open test data file"), m_filePath, tr("txt (*.log)"));
    if(fileName.isEmpty()){
        return;
    }
    m_filedeal = new FileDeal;
 //   connect(m_filedeal, &FileDeal::resultReady, this, &MainWindow::showValueArray);
    connect(m_filedeal, &FileDeal::traning, this, &MainWindow::decisionTree_training);
    connect(m_filedeal, &FileDeal::finished, this, &MainWindow::threadFinised);
    m_filedeal->parseFile(fileName);
    QList<QChartView *> list = ui->tab_2->findChildren<QChartView *>(QString(), Qt::FindDirectChildrenOnly);
    QChart *xwidthChart = list.at(0)->chart();
    QChart *yheightChart = list.at(1)->chart();
    QChart *meanChart = list.at(2)->chart();
    QList<QAbstractSeries *> xwidthSeries = xwidthChart->series();
    QList<QAbstractSeries *> yheightSeries = yheightChart->series();
    QList<QAbstractSeries *> meanSeries = meanChart->series();
    QScatterSeries *xSeries = qobject_cast<QScatterSeries *>(xwidthSeries.at(0));
    QScatterSeries *widthSeries = qobject_cast<QScatterSeries *>(xwidthSeries.at(1));
    QScatterSeries *ySeries = qobject_cast<QScatterSeries *>(yheightSeries.at(0));
    QScatterSeries *heightSeries = qobject_cast<QScatterSeries *>(yheightSeries.at(1));
    QScatterSeries *meanSerie = qobject_cast<QScatterSeries *>(meanSeries.first());
    xSeries->clear();
    ySeries->clear();
    widthSeries->clear();
    heightSeries->clear();
    meanSerie->clear();
    m_filedeal->start();
}
void MainWindow::on_actionserialSet_triggered()
{

}
void MainWindow::on_actionquit_triggered()
{
    qApp->quit();
}
