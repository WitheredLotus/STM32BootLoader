#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QFileDialog>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->FileButton->setText("打开文件");
    ui->OpenCom_pushButton->setText("打开串口");
    ui->SendFile_pushButton->setText("发送文件");

    connect(ui->FileButton, &QPushButton::clicked, this, &Widget::OpenFile);
    connect(ui->OpenCom_pushButton, &QPushButton::clicked, this, &Widget::OpenCom_pushButton_clicked);
    connect(ui->SendFile_pushButton, &QPushButton::clicked, this, &Widget::SendFile_pushButton_clicked);

    initSerialPort();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::initSerialPort()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {

        MySerial.setPort(info);
        if(MySerial.open(QIODevice::ReadWrite))
        {
            ui->COM_comboBox->addItem(info.portName());
            MySerial.close();
        }
    }

    QStringList baudList;           //波特率
    QStringList parityList;         //校验位
    QStringList dataBitsList;       //数据位
    QStringList stopBitsList;       //停止位

    baudList<<"1200"<<"2400"<<"4800"<<"9600"<<"38400"<<"115200";

    ui->Bound_comboBox->addItems(baudList);//波特率
    ui->Bound_comboBox->setCurrentIndex(3);//从0开始索引 9600

    parityList<<"无"<<"奇"<<"偶";

    ui->CheckBit_comboBox->addItems(parityList);//校验位
    ui->CheckBit_comboBox->setCurrentIndex(0);

    dataBitsList<<"5"<<"6"<<"7"<<"8";
    ui->DataBit_comboBox->addItems(dataBitsList);//数据位
    ui->DataBit_comboBox->setCurrentIndex(3);

    stopBitsList<<"1";
    stopBitsList<<"1.5";
    stopBitsList<<"2";

    ui->StopBit_comboBox->addItems(stopBitsList);//停止位
    ui->StopBit_comboBox->setCurrentIndex(0);

}

void Widget::OpenFile()
{
    static QString lastName="C:";

    QString filename = QFileDialog::getOpenFileName(this, "文件对话框", lastName, "*");
    lastName = filename;
    qDebug() << filename;

    ui->FilePath_lineEdit->setText(filename);

}

void Widget::OpenCom_pushButton_clicked()
{
    MySerial.setPortName(ui->COM_comboBox->currentText());//设置串口号;也就是说打开的是当前显示的串口

    if(ui->OpenCom_pushButton->text()=="打开串口")//打开串口
    {
        if(MySerial.open(QIODevice::ReadWrite))//读写方式打开,成功后设置串口
        {
            MySerial.setBaudRate(ui->Bound_comboBox->currentText().toInt());//设置波特率
            MySerial.setDataBits(QSerialPort::Data8);//设置数据位
            MySerial.setParity(QSerialPort::NoParity);//设置校验位
            MySerial.setFlowControl(QSerialPort::NoFlowControl);//设置流控制
            MySerial.setStopBits(QSerialPort::OneStop);//设置停止位
            ui->OpenCom_pushButton->setText("关闭串口");
        }
        else//串口打开失败
        {
          //  QMessageBox::about(NULL, "提示", "要打开串口哦！");
            qDebug() <<"串口打开失败";
            return ;
        }
    }
    else if(ui->OpenCom_pushButton->text()=="关闭串口")//关闭串口
    {
        ui->OpenCom_pushButton->setText("打开串口");
        MySerial.close();//关串口
    }
}

void Widget::SendFile_pushButton_clicked()
{

    QByteArray SendData;

    QString filename = ui->FilePath_lineEdit->text();
    qDebug() << "in SendFile_pushButton_clicked:" << filename;
    QFile file(filename);

    if(ui->OpenCom_pushButton->text()=="关闭串口")//打开串口才可以发送数据
    {

        if(file.open(QIODevice::ReadOnly)){
            QDataStream in(&file);
            qint8 ch;

            qDebug() <<"File Size(Byte):"<<file.size();

            const int framesize = 200;

            int Size = file.size() / framesize;

            for (int i = 0; i < Size; i++) {

                for (int k = 0; k < framesize; k++) {
                    in >> ch;
                    SendData.append(ch);
                }

//                SendData.append(0xAA);
//                SendData.append(0x55);
                MySerial.write(SendData,SendData.length()); //写入缓冲区
                SendData.clear();                           //清空数据
            }

            //处理剩余的数据
            for (int i = 0; i < file.size()-framesize*Size; i++) {
//                SendData.append(0xAA);
//                SendData.append(0x55);
                MySerial.write(SendData,SendData.length()); //写入缓冲区
            }

        }else {
            qDebug() << "打开文件失败";
        }

    }else {
        qDebug() << "串口未打开";
    }
}
