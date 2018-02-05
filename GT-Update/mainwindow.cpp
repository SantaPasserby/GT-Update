#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTextCodec>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle(tr("固件升级1.0"));
    setWindowIcon(QIcon("update.ico"));
    initInterface();            // 初始化界面
    readSerialCfg();            // 读取本地文件的串口配置
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::readMyCom()
{
    int byteLen = myCom->bytesAvailable(); //返回串口缓冲区字节数
    if(byteLen)
    {
       QByteArray temp = myCom->readAll();    //返回读取的字节
       ui->textEdit->insertPlainText(QString("接收到%1字节\n").arg(byteLen));
       scrollBar->setSliderPosition(scrollBar->maximum());
    }
}
void MainWindow::resetTimer()
{
    readTimer->setInterval(10);
}

void MainWindow::sendMyCom()
{
    myCom->write(ui->lineEdit->text().toLocal8Bit());
}

void MainWindow::initInterface()
{
    ui->exitBtn->setText(tr("退出"));
//    ui->exitBtn->setStyleSheet("QPushButton#exitBtn {min-width: 10px;}");
    ui->serialBtn->setText(tr("串口设置"));
    ui->connectBtn->setText(tr("连接"));
    ui->disconnectBtn->setText(tr("断开"));
    ui->disconnectBtn->setVisible(false);
    ui->selectBtn->setText(tr("选择文件"));
    ui->serialLabel->setText(tr("请连接,9600,8,1,0,CLOSE"));
    ui->spreadBtn->setText(tr("展开v"));
    ui->enterBtn->setText(tr("进入主程序"));
    ui->infoBtn->setText(tr("固件信息"));
    ui->startBtn->setText(tr("开始升级"));
    ui->sendBtn->setText(tr("发送"));
    ui->lineEdit->setText("AT");
    ui->statusLabel->setText(tr("等待升级..."));
    ui->statusLabel->setStyleSheet("QLabel#statusLabel { background-color:#00FF00; }");
    ui->textEdit->setPlaceholderText(tr("接收区："));
//    serialDialog = new SerialDialog(this);
    readTimer = new QTimer(this);
}


// 退出
void MainWindow::on_exitBtn_clicked()
{
    close();
}

// 固件信息获取
void MainWindow::on_infoBtn_clicked()
{

}


// 连接串口
void MainWindow::on_connectBtn_clicked()
{
    readSerialCfg();
    QSerialPortInfo serialInfoTest(serialParmeter.portNum);
    QSerialPortInfo InfoserialInfoTmp;
    int i;

    QList<QSerialPortInfo> availableSerialList = QSerialPortInfo::availablePorts();
    int count = availableSerialList.count();
    for( i = 0; i < count; i++ )
    {
        if(serialParmeter.portNum == availableSerialList[i].portName())
            break;
    }
    if(i == availableSerialList.count())
        QMessageBox::warning(this,
                             tr("警告"),
                             tr("不存在此端口号%1！").arg(serialParmeter.portNum),
                             QMessageBox::Ok);

    else if(serialInfoTest.isBusy())
    {
        QMessageBox::warning(this,
                             tr("警告"),
                             tr("%1已经被占用了!").arg(serialParmeter.portNum),
                             QMessageBox::Ok);
    }
    else
    {
        //
        myCom = new Win_QextSerialPort(serialParmeter.portNum, QextSerialBase::EventDriven);
        myCom->open(QIODevice::ReadWrite);
        myCom->setBaudRate(BAUD115200);
        myCom->setDataBits(DATA_8);
        myCom->setParity(PAR_NONE);
        myCom->setStopBits(STOP_1);
        myCom->setFlowControl(FLOW_OFF);
    //    myCom->setTimeout(500);
        scrollBar = ui->textEdit->verticalScrollBar();
        readTimer->start(10);
    //    myCom->setTimeout(10);
        connect(readTimer, SIGNAL(timeout()), this, SLOT(readMyCom()));
        connect(myCom, SIGNAL(readyRead()),this, SLOT(resetTimer()));
        connect(ui->sendBtn, SIGNAL(clicked()), this, SLOT(sendMyCom()));
        ui->connectBtn->setVisible(false);
        ui->disconnectBtn->setVisible(true);
        ui->serialBtn->setEnabled(false);
        ui->serialLabel->setText(QString("%1: %2 bps, %3,%4,%5,%6").arg(serialParmeter.portNum)\
                                 .arg(serialParmeter.baudRate)\
                                 .arg(serialParmeter.parity)\
                                 .arg(serialParmeter.dataBits)\
                                 .arg(serialParmeter.stopBits)\
                                 .arg(serialParmeter.appendType));
     }
}
void MainWindow::on_serialBtn_clicked()
{
    readSerialCfg();
    SerialDialog serialDialog(serialParmeter);
    serialDialog.move(pos().x()+(width()-serialDialog.width())/2,
                      pos().y()+(height()-serialDialog.height())/2);   // 子窗体显示在父窗体的中间位置
    serialDialog.exec();
}


// 读取串口配置(保存在config.ini)
void MainWindow::readSerialCfg()
{
    QFile file("config.ini");
    QList<QByteArray> arrayList;
    QList<QString> stringListTemp;
    QByteArray str1;
    QString str2;
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
     QTextStream in(&file);
     while (!file.atEnd()) {
            arrayList << file.readLine();
     }
    foreach(str1, arrayList)
    {
        str2 = codec->toUnicode(str1).section("=",-1,-1).remove("\n",Qt::CaseInsensitive).section("]",-1,-1);
        if(!str2.isEmpty())
            stringListTemp << str2;
        qDebug() << stringListTemp;
    }
    serialParmeter.portNum = stringListTemp.value(0);
    serialParmeter.baudRate = stringListTemp.value(1);
    serialParmeter.parity = stringListTemp.value(2);
    serialParmeter.dataBits = stringListTemp.value(3);
    serialParmeter.stopBits = stringListTemp.value(4);
}

// 关闭串口
void MainWindow::on_disconnectBtn_clicked()
{
    myCom->close();
    ui->disconnectBtn->setVisible(false);
    ui->connectBtn->setVisible(true);
    ui->serialBtn->setEnabled(true);
    ui->serialLabel->setText(tr("串口关闭！"));
}

void MainWindow::on_selectBtn_clicked()
{
   QFileDialog::getOpenFileUrl(
                              this,
                              "Select one or more files to open",
                              QUrl(QDir::currentPath()),
                              "Images (*.png *.xpm *.jpg)");
}
