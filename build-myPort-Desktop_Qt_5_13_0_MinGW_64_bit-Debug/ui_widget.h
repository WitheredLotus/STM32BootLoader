/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *FileButton;
    QComboBox *COM_comboBox;
    QComboBox *Bound_comboBox;
    QComboBox *CheckBit_comboBox;
    QComboBox *DataBit_comboBox;
    QComboBox *StopBit_comboBox;
    QPushButton *OpenCom_pushButton;
    QLineEdit *FilePath_lineEdit;
    QPushButton *SendFile_pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(566, 315);
        FileButton = new QPushButton(Widget);
        FileButton->setObjectName(QString::fromUtf8("FileButton"));
        FileButton->setGeometry(QRect(470, 160, 80, 20));
        COM_comboBox = new QComboBox(Widget);
        COM_comboBox->setObjectName(QString::fromUtf8("COM_comboBox"));
        COM_comboBox->setGeometry(QRect(70, 70, 72, 22));
        Bound_comboBox = new QComboBox(Widget);
        Bound_comboBox->setObjectName(QString::fromUtf8("Bound_comboBox"));
        Bound_comboBox->setGeometry(QRect(70, 110, 72, 22));
        CheckBit_comboBox = new QComboBox(Widget);
        CheckBit_comboBox->setObjectName(QString::fromUtf8("CheckBit_comboBox"));
        CheckBit_comboBox->setGeometry(QRect(70, 150, 72, 22));
        DataBit_comboBox = new QComboBox(Widget);
        DataBit_comboBox->setObjectName(QString::fromUtf8("DataBit_comboBox"));
        DataBit_comboBox->setGeometry(QRect(70, 200, 72, 22));
        StopBit_comboBox = new QComboBox(Widget);
        StopBit_comboBox->setObjectName(QString::fromUtf8("StopBit_comboBox"));
        StopBit_comboBox->setGeometry(QRect(70, 240, 72, 22));
        OpenCom_pushButton = new QPushButton(Widget);
        OpenCom_pushButton->setObjectName(QString::fromUtf8("OpenCom_pushButton"));
        OpenCom_pushButton->setGeometry(QRect(190, 70, 80, 20));
        FilePath_lineEdit = new QLineEdit(Widget);
        FilePath_lineEdit->setObjectName(QString::fromUtf8("FilePath_lineEdit"));
        FilePath_lineEdit->setGeometry(QRect(230, 170, 191, 20));
        SendFile_pushButton = new QPushButton(Widget);
        SendFile_pushButton->setObjectName(QString::fromUtf8("SendFile_pushButton"));
        SendFile_pushButton->setGeometry(QRect(470, 190, 80, 20));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        FileButton->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        OpenCom_pushButton->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
        SendFile_pushButton->setText(QCoreApplication::translate("Widget", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
