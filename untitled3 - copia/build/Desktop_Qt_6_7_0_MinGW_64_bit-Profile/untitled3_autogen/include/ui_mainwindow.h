/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *codigo;
    QTextBrowser *tokens;
    QPushButton *Abrir;
    QTextBrowser *errores;
    QPushButton *Limpiar;
    QPushButton *Guardar;
    QPushButton *Analizar;
    QPushButton *pushButton_5;
    QTextBrowser *TxtPila;
    QTextBrowser *TxtPilaOp;
    QTextBrowser *TxtPilaCuadruplosOP;
    QTextBrowser *TxtPilaCuadruplosSignos;
    QTextBrowser *TxtPilaCuadruplosSaltos;
    QTableWidget *tablaCuadruplos;
    QTextBrowser *txtPilaRellenar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1119, 600);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(55, 53, 50);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        codigo = new QTextBrowser(centralwidget);
        codigo->setObjectName("codigo");
        codigo->setGeometry(QRect(10, 10, 231, 331));
        codigo->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        codigo->setReadOnly(false);
        tokens = new QTextBrowser(centralwidget);
        tokens->setObjectName("tokens");
        tokens->setGeometry(QRect(250, 10, 281, 331));
        tokens->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        Abrir = new QPushButton(centralwidget);
        Abrir->setObjectName("Abrir");
        Abrir->setGeometry(QRect(30, 400, 80, 18));
        Abrir->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 42, 50);"));
        errores = new QTextBrowser(centralwidget);
        errores->setObjectName("errores");
        errores->setGeometry(QRect(550, 390, 231, 181));
        errores->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        Limpiar = new QPushButton(centralwidget);
        Limpiar->setObjectName("Limpiar");
        Limpiar->setGeometry(QRect(140, 400, 80, 18));
        Limpiar->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 42, 50);"));
        Guardar = new QPushButton(centralwidget);
        Guardar->setObjectName("Guardar");
        Guardar->setGeometry(QRect(240, 400, 80, 18));
        Guardar->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 42, 50);"));
        Analizar = new QPushButton(centralwidget);
        Analizar->setObjectName("Analizar");
        Analizar->setGeometry(QRect(340, 400, 80, 18));
        Analizar->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 42, 50);"));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName("pushButton_5");
        pushButton_5->setGeometry(QRect(450, 400, 80, 18));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(138, 42, 50);"));
        TxtPila = new QTextBrowser(centralwidget);
        TxtPila->setObjectName("TxtPila");
        TxtPila->setGeometry(QRect(30, 440, 501, 31));
        TxtPila->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        TxtPilaOp = new QTextBrowser(centralwidget);
        TxtPilaOp->setObjectName("TxtPilaOp");
        TxtPilaOp->setGeometry(QRect(30, 500, 501, 31));
        TxtPilaOp->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        TxtPilaCuadruplosOP = new QTextBrowser(centralwidget);
        TxtPilaCuadruplosOP->setObjectName("TxtPilaCuadruplosOP");
        TxtPilaCuadruplosOP->setGeometry(QRect(810, 390, 281, 31));
        TxtPilaCuadruplosOP->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        TxtPilaCuadruplosSignos = new QTextBrowser(centralwidget);
        TxtPilaCuadruplosSignos->setObjectName("TxtPilaCuadruplosSignos");
        TxtPilaCuadruplosSignos->setGeometry(QRect(810, 440, 281, 31));
        TxtPilaCuadruplosSignos->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        TxtPilaCuadruplosSaltos = new QTextBrowser(centralwidget);
        TxtPilaCuadruplosSaltos->setObjectName("TxtPilaCuadruplosSaltos");
        TxtPilaCuadruplosSaltos->setGeometry(QRect(810, 490, 281, 31));
        TxtPilaCuadruplosSaltos->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        tablaCuadruplos = new QTableWidget(centralwidget);
        if (tablaCuadruplos->columnCount() < 5)
            tablaCuadruplos->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tablaCuadruplos->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tablaCuadruplos->setObjectName("tablaCuadruplos");
        tablaCuadruplos->setGeometry(QRect(550, 10, 541, 351));
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial")});
        tablaCuadruplos->setFont(font);
        tablaCuadruplos->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        tablaCuadruplos->setEditTriggers(QAbstractItemView::NoEditTriggers);
        txtPilaRellenar = new QTextBrowser(centralwidget);
        txtPilaRellenar->setObjectName("txtPilaRellenar");
        txtPilaRellenar->setGeometry(QRect(810, 540, 281, 31));
        txtPilaRellenar->setStyleSheet(QString::fromUtf8("background-color: rgb(177, 180, 176);"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        codigo->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        tokens->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        Abrir->setText(QCoreApplication::translate("MainWindow", "Abrir", nullptr));
        errores->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        Limpiar->setText(QCoreApplication::translate("MainWindow", "Limpiar", nullptr));
        Guardar->setText(QCoreApplication::translate("MainWindow", "Guardar", nullptr));
        Analizar->setText(QCoreApplication::translate("MainWindow", "Analizar", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tablaCuadruplos->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "#", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tablaCuadruplos->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Operando", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tablaCuadruplos->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Op1", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tablaCuadruplos->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Op2", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tablaCuadruplos->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Resultado", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
