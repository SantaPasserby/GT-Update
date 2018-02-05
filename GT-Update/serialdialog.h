#ifndef SERIALDIALOG_H
#define SERIALDIALOG_H

#include <QDialog>
#include <QSerialPort>
#include <QList>
#include <QRadioButton>
#include "serialparameter.h"
namespace Ui {
class SerialDialog;
}

class SerialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SerialDialog(SerialParameter serialParameter,QWidget *parent = 0);
    ~SerialDialog();

private slots:
    void on_serialCancelBtn_clicked();

    void on_serialApplyBtn_clicked();

private:
    Ui::SerialDialog *ui;
    SerialParameter serialParameter;
    qint8 appendType;
    void serialSetInit();


};

#endif // SERIALDIALOG_H
