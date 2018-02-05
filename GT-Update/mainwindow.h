#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollBar>
#include "serialdialog.h"
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "serialparameter.h"
#include "qextserialport-1.2win-alpha/win_qextserialport.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void initInterface();
    Win_QextSerialPort *myCom;
    QScrollBar *scrollBar;
    QTimer *readTimer;
    SerialParameter serialParmeter;
    bool isFirstOpen;           // 是否首次打开
    QString fileName;
    void readSerialCfg();

private slots:
    void readMyCom();
    void sendMyCom();
    void resetTimer();
    void on_exitBtn_clicked();
    void on_infoBtn_clicked();
    void on_connectBtn_clicked();
    void on_serialBtn_clicked();
    void on_disconnectBtn_clicked();
    void on_selectBtn_clicked();
};

#endif // MAINWINDOW_H
