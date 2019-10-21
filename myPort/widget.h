#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

    void initSerialPort();

private:
    Ui::Widget *ui;    
    QSerialPort MySerial;
public slots:
    void OpenFile();
    void OpenCom_pushButton_clicked();
    void SendFile_pushButton_clicked();
};

#endif // WIDGET_H
