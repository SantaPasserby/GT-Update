#include "serialdialog.h"
#include "ui_serialdialog.h"
#include <QSerialPortInfo>
#include <QSerialPort>
#include <QFile>
#include <QIODevice>
#include <QTextStream>
SerialDialog::SerialDialog(SerialParameter serialParameter,QWidget *parent) :
    QDialog(parent),
    serialParameter(serialParameter),
    ui(new Ui::SerialDialog)
{
    ui->setupUi(this);
    // 隐藏默认的标题栏，创建新的标题栏
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);
    // 设置标题
    setWindowTitle(tr("串口设置"));
    // 串口设置初始化
    serialSetInit();

}

SerialDialog::~SerialDialog()
{
    delete ui;
}

void SerialDialog::serialSetInit()
{
    // 获取当前系统可用的串口号
    QList<QSerialPortInfo> serialList;
    serialList = QSerialPortInfo::availablePorts();
    QSerialPortInfo serialPort;
    ui->comComboBox->setEditable(true); // 设置为可编辑
    foreach(serialPort, serialList)     // 将可用串口号作为comComboBox的条目
    {
    ui->comComboBox->addItem(serialPort.portName());
    }

    // 波特率
    QStringList   baudStringList;
    baudStringList << "110"<< "300"<< "600"<< "1200" << "2400" << "4800"
               << "9600" << "19200" << "38400" << "57600" << "115200"
               << "12800" << "256000";
    ui->baudComboBox->setEditable(true);
    ui->baudComboBox->addItems(baudStringList);

    // 校验
    ui->parityComboBox->addItem(tr("无"), QSerialPort::NoParity);
    ui->parityComboBox->addItem(tr("奇校验"), QSerialPort::EvenParity);
    ui->parityComboBox->addItem(tr("偶校验"), QSerialPort::OddParity);

    // 数据位
    ui->dataBitsComboBox->addItem("5", QSerialPort::Data5);
    ui->dataBitsComboBox->addItem("6", QSerialPort::Data6);
    ui->dataBitsComboBox->addItem("7", QSerialPort::Data7);
    ui->dataBitsComboBox->addItem("8", QSerialPort::Data8);

    // 停止位
    ui->stopBitsComboBox->addItem("无", QSerialPort::OneStop);
    ui->stopBitsComboBox->addItem("1", QSerialPort::OneStop);
    ui->stopBitsComboBox->addItem("1.5", QSerialPort::OneAndHalfStop);
    ui->stopBitsComboBox->addItem("2", QSerialPort::TwoStop);

    ui->comComboBox->setCurrentText(serialParameter.portNum);
    ui->baudComboBox->setCurrentText(serialParameter.baudRate);
    ui->parityComboBox->setCurrentText(serialParameter.parity);
    ui->dataBitsComboBox->setCurrentText(serialParameter.dataBits);
    ui->dataBitsComboBox->setCurrentText(serialParameter.stopBits);
    ui->checkBox->setCheckState(serialParameter.isHexShow);

    switch (serialParameter.appendType) {
    case 0:
            ui->radioButton_1->setChecked(true);
        break;
    case 1:
            ui->radioButton_2->setChecked(true);
        break;
    case 2:
            ui->radioButton_3->setChecked(true);
        break;
    case 3:
            ui->radioButton_4->setChecked(true);
        break;
    default:
        break;
    }

}

void SerialDialog::on_serialCancelBtn_clicked()
{
    close();
}


// 串口设置->确定
void SerialDialog::on_serialApplyBtn_clicked()
{
    QFile file("config.ini");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);

    // 保存
    out << "[PORT]\n";
    out << "COM=" << ui->comComboBox->itemText(ui->comComboBox->currentIndex())  << "\n";
    out << "BAUD=" << ui->baudComboBox->itemText(ui->baudComboBox->currentIndex()) << "\n";
    out << "PARITY=" << ui->parityComboBox->itemText(ui->parityComboBox->currentIndex()) << "\n";
    out << "DATALEN=" << ui->dataBitsComboBox->itemText(ui->dataBitsComboBox->currentIndex()) << "\n";
    out << "STOPBITS=" << ui->stopBitsComboBox->itemText(ui->stopBitsComboBox->currentIndex()) << "\n";
    if(ui->radioButton_1->isChecked())
        appendType = 0;
    else if(ui->radioButton_2->isChecked())
        appendType = 1;
    else if(ui->radioButton_3->isChecked())
        appendType = 2;
    else if(ui->radioButton_4->isChecked())
        appendType = 3;

    out << "APPENDTYPE=" << appendType <<"\n";
    out << "SHOWHEX=" << ui->checkBox->isChecked() <<"\n";
    out << "[UPDATE]\n";
    out << "DVICETYPE=" << "\n";
    file.close();
    close();
}
