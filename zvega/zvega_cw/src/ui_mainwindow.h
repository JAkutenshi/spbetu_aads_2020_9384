/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *layout;
    QTextBrowser *textBrowser;
    QPushButton *save;
    QTextBrowser *textBrowser_3;
    QPushButton *startButtom;
    QTextBrowser *n21;
    QTextBrowser *n24;
    QPushButton *random;
    QTextBrowser *textBrowser_4;
    QTextBrowser *textBrowser_2;
    QLineEdit *lineEdit;
    QTextBrowser *n31;
    QGraphicsView *graphicsView;
    QTextBrowser *textBrowser_6;
    QTextBrowser *textBrowser_5;
    QPushButton *info;
    QTextBrowser *n25;
    QTextBrowser *n22;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1588, 875);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 1581, 821));
        layout = new QGridLayout(gridLayoutWidget);
        layout->setObjectName(QString::fromUtf8("layout"));
        layout->setSizeConstraint(QLayout::SetMaximumSize);
        layout->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(gridLayoutWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        layout->addWidget(textBrowser, 3, 0, 1, 1);

        save = new QPushButton(gridLayoutWidget);
        save->setObjectName(QString::fromUtf8("save"));

        layout->addWidget(save, 7, 1, 1, 1);

        textBrowser_3 = new QTextBrowser(gridLayoutWidget);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));

        layout->addWidget(textBrowser_3, 5, 0, 1, 1);

        startButtom = new QPushButton(gridLayoutWidget);
        startButtom->setObjectName(QString::fromUtf8("startButtom"));

        layout->addWidget(startButtom, 0, 1, 1, 1);

        n21 = new QTextBrowser(gridLayoutWidget);
        n21->setObjectName(QString::fromUtf8("n21"));

        layout->addWidget(n21, 3, 1, 1, 1);

        n24 = new QTextBrowser(gridLayoutWidget);
        n24->setObjectName(QString::fromUtf8("n24"));

        layout->addWidget(n24, 9, 1, 1, 1);

        random = new QPushButton(gridLayoutWidget);
        random->setObjectName(QString::fromUtf8("random"));

        layout->addWidget(random, 1, 0, 1, 1);

        textBrowser_4 = new QTextBrowser(gridLayoutWidget);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));

        layout->addWidget(textBrowser_4, 9, 0, 1, 1);

        textBrowser_2 = new QTextBrowser(gridLayoutWidget);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        layout->addWidget(textBrowser_2, 4, 0, 1, 1);

        lineEdit = new QLineEdit(gridLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setClearButtonEnabled(false);

        layout->addWidget(lineEdit, 0, 0, 1, 1);

        n31 = new QTextBrowser(gridLayoutWidget);
        n31->setObjectName(QString::fromUtf8("n31"));

        layout->addWidget(n31, 11, 1, 1, 1);

        graphicsView = new QGraphicsView(gridLayoutWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        QFont font;
        font.setPointSize(16);
        graphicsView->setFont(font);

        layout->addWidget(graphicsView, 5, 1, 1, 1);

        textBrowser_6 = new QTextBrowser(gridLayoutWidget);
        textBrowser_6->setObjectName(QString::fromUtf8("textBrowser_6"));

        layout->addWidget(textBrowser_6, 11, 0, 1, 1);

        textBrowser_5 = new QTextBrowser(gridLayoutWidget);
        textBrowser_5->setObjectName(QString::fromUtf8("textBrowser_5"));

        layout->addWidget(textBrowser_5, 10, 0, 1, 1);

        info = new QPushButton(gridLayoutWidget);
        info->setObjectName(QString::fromUtf8("info"));

        layout->addWidget(info, 1, 1, 1, 1);

        n25 = new QTextBrowser(gridLayoutWidget);
        n25->setObjectName(QString::fromUtf8("n25"));

        layout->addWidget(n25, 10, 1, 1, 1);

        n22 = new QTextBrowser(gridLayoutWidget);
        n22->setObjectName(QString::fromUtf8("n22"));

        layout->addWidget(n22, 4, 1, 1, 1);

        textBrowser_2->raise();
        textBrowser->raise();
        textBrowser_4->raise();
        startButtom->raise();
        random->raise();
        lineEdit->raise();
        textBrowser_3->raise();
        info->raise();
        n25->raise();
        textBrowser_5->raise();
        textBrowser_6->raise();
        n24->raise();
        n21->raise();
        n22->raise();
        n31->raise();
        graphicsView->raise();
        save->raise();
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1588, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2.1. \320\224\320\273\321\217 \320\267\320\260\320\264\320\260\320\275\320\275\320\276\320\263\320\276 \321\202\320\265\320\272\321\201\321\202\320\260 \320\276\320\277\321\200\320\265\320\264\320\265\320\273\320\270\321\202\321\214 \321\207\320\270\321\201\320\273\320\276 \320\262\321\205\320\276\320\266\320\264\320\265\320\275\320\270\320\271 \320\272\320\260\320\266\320\264\320\276\320\263\320\276 \321\201\320\270\320\274\320\262\320\276\320\273\320\260.</p></body></html>", nullptr));
        save->setText(QApplication::translate("MainWindow", "Save png", nullptr));
        textBrowser_3->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2.3. \320\237\320\276\321\201\321\202\321\200\320\276\320\270\321\202\321\214 \321\203\320\277\320\276\321\200\321\217\320\264\320\276\321\207\320\265\320\275\320\275\320\276\320\265 \320\264\320\265\321\200\320\265\320\262\320\276 \320\245\320\260\321\204\321\204\320\274\320\265\320\275\320\260, \320\270\320\274\320\265\321\216\321\211\320\265\320\265 \320\274\320\270\320\275\320\270\320\274\320\260\320\273\321\214\320\275\321\203\321\216</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;"
                        "\">\320\262\321\213\321\201\320\276\321\202\321\203 \320\270\320\267 \320\262\321\201\320\265\321\205 \320\264\320\265\321\200\320\265\320\262\321\214\320\265\320\262 \320\245\320\260\321\204\321\204\320\274\320\265\320\275\320\260. \320\235\320\260\320\264\320\277\320\270\321\201\320\260\321\202\321\214 \321\203\320\267\320\273\321\213 \320\264\320\265\321\200\320\265\320\262\320\260 (\321\201\320\270\320\274\320\262\320\276\320\273(\321\213), \321\207\320\270\321\201\320\273\320\276</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\262\321\205\320\276\320\266\320\264\320\265\320\275\320\270\320\271).</p></body></html>", nullptr));
        startButtom->setText(QApplication::translate("MainWindow", "Ok", nullptr));
        random->setText(QApplication::translate("MainWindow", "Random string", nullptr));
        textBrowser_4->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2.4. \320\222\321\213\320\277\320\270\321\201\320\260\321\202\321\214 \320\272\320\276\320\264 \320\245\320\260\321\204\321\204\320\274\320\265\320\275\320\260 \320\264\320\273\321\217 \320\262\321\201\320\265\321\205 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262, \320\262\321\205\320\276\320\264\321\217\321\211\320\270\321\205 \320\262 \321\202\320\265\320\272\321\201\321\202.</p></body></html>", nullptr));
        textBrowser_2->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2.2. \320\241\321\205\320\265\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272\320\270 \320\270\320\267\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \320\277\321\200\320\276\321\206\320\265\321\201\321\201 \320\262\321\213\320\277\320\276\320\273\320\275\320\265\320\275\320\270\321\217 \320\260\320\273\320\263\320\276\321\200\320\270\321\202\320\274\320\260 \320\245\320\260\321\204\321\204\320\274\320\265\320\275\320\260.</p></body></html>", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        lineEdit->setInputMask(QString());
        lineEdit->setPlaceholderText(QString());
        textBrowser_6->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">3.1. \320\235\320\260 \320\272\320\260\320\266\320\264\320\276\320\274 \321\210\320\260\320\263\320\265 \321\203\320\272\320\260\320\267\320\260\321\202\321\214 \320\276\321\207\320\265\321\200\320\265\320\264\320\275\320\276\320\271 \320\276\321\202\321\200\320\265\320\267\320\276\320\272 \320\262\321\205\320\276\320\264\320\275\320\276\320\271 \320\261\320\270\321\202\320\276\320\262\320\276\320\271</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\277\320\276\321\201\320\273\320"
                        "\265\320\264\320\276\320\262\320\260\321\202\320\265\320\273\321\214\320\275\320\276\321\201\321\202\320\270 (\320\264\320\262\320\276\320\270\321\207\320\275\321\213\320\271 \320\272\320\276\320\264), \320\264\320\265\320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\260\320\275\320\275\321\213\320\271 \320\277\320\276 \321\215\321\202\320\276\320\274\321\203 \320\276\321\202\321\200\320\265\320\267\320\272\321\203 \321\201\320\270\320\274\320\262\320\276\320\273, \320\260</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\321\202\320\260\320\272\320\266\320\265 \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\320\276\320\265 \320\277\320\276\321\201\320\273\320\265 \320\276\320\261\321\200\320\260\320\261\320\276\321\202\320\272\320\270 \321\215\321\202\320\276\320\263\320\276 \320\276\321\202\321\200\320\265\320\267\320\272\320\260 (\320\277\320\276\321\201\320\273\320\265 \320\262\321\213\320\264\320\265"
                        "\320\273\320\265\320\275\320\270\321\217 \321\201\320\270\320\274\320\262\320\276\320\273\320\260)</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\272\320\276\320\264\320\276\320\262\320\276\320\265 \320\264\320\265\321\200\320\265\320\262\320\276. \320\242.\320\276. \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \321\210\320\260\320\263\320\276\320\262 \320\264\320\276\320\273\320\266\320\275\320\276 \321\201\320\276\320\262\320\277\320\260\321\201\321\202\321\214 \321\201 \320\272\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276\320\274</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\320\264\320\265\320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\260\320\275\320\275\321\213\321\205 \321\201\320\270\320\274\320\262\320\276\320\273\320\276\320\262.</p></body></html>", nullptr));
        textBrowser_5->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">2.5. \320\237\320\276\320\264\321\201\321\207\320\270\321\202\320\260\321\202\321\214 \320\264\320\273\320\270\320\275\321\203 \320\267\320\260\320\272\320\276\320\264\320\270\321\200\320\276\320\262\320\260\320\275\320\275\320\276\320\263\320\276 \320\277\320\276\320\273\321\203\321\207\320\265\320\275\320\275\321\213\320\274 \320\272\320\276\320\264\320\276\320\274 \321\202\320\265\320\272\321\201\321\202\320\260.</p></body></html>", nullptr));
        info->setText(QApplication::translate("MainWindow", "Info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
