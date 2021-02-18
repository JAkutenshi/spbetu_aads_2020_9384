#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QScatterSeries>
#include <QMessageBox>
#include <QInputDialog>

#include <string>
#include <vector>
#include <chrono>
#include <cmath>


#include "adaptive_encode.h"
#include "priority_queue.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    CodeTree *Tree;

    const QString possibleCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz~!@#$%^&*()_+|/.<=>-?`';:,\"1234567890 ";


    QString generateAverageCase(int amount);
    QString generateWorstCase(int amount);
    QString generateBestCase(int amount);

    CodeTree* Adaptive_MakeTree(const char* message);
    char* Adaptive_decode(const CodeTree* tree, vector<char> code);
    vector<char> Adaptive_encode(const CodeTree* tree, const char* message);

    QString VectorToString(vector<char> code);

    double AdaptiveEncode_time(QString text);
    double StaticEncode_time(QString text);

    double AdaptiveDecode_time(QString text);
    double StaticDecode_time(QString text);

    QString GetRandomString(int randomStringLength);

    size_t Adaptive_bits(int count_of_letters);
    size_t Static_bits(int count_of_letters);

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
