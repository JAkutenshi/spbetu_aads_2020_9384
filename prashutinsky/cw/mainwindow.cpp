#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#define KEY_MAX 1000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    z = new Graphics_view_zoom(ui->graphicsView);
    z->set_modifiers(Qt::NoModifier);
    z_2 = new Graphics_view_zoom(ui->graphicsView_3);
    z_2->set_modifiers(Qt::NoModifier);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    scene_2 = new QGraphicsScene();
    ui->graphicsView_3->setScene(scene_2);
    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCreate_variant_triggered(){
    int data = QInputDialog::getInt(this, "Create variant.", "Enter amount of elements: ");
    int random;
    for (int i = 0; i < KEY_MAX; i++) {
        treap.erase(i);
    }
    for(int i = 0; i < data; i++){
        random = rand() % KEY_MAX;
        treap.insert(random);
    }
    scene->clear();
    treap.draw(scene);
}

void MainWindow::on_Open_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Explorer", QDir::homePath(), tr("Load File (*.DOCX)"));

    QFile file(filepath);
    if(!file.open(QFile::ReadOnly | QFile::ReadOnly))
    {
        QMessageBox::warning(this, "Warning!", "File not open.");
    }
    else
    {
        QTextStream in(&file);
        QString str = in.readLine();

        QStringList lst = str.split(" ");

        QVector<int> data;

        for (qsizetype index = 0; index < lst.size(); index++)
        {
            QString num = lst[index];
            data.push_back(num.toInt());
        }

        for(QVector<int>::iterator iter = data.begin();iter != data.end();iter++)
        {
                treap.insert(*iter);
        }

        scene->clear();
        treap.draw(scene);
    }

    file.close();
}

void MainWindow::on_Enter_triggered()
{
    QString str = QInputDialog::getText(this, "Enter Traversal.", "Enter Preorder Traversal: ");

    QStringList lst = str.split(" ");

    QVector<int> data;

    for (qsizetype index = 0; index < lst.size(); index++)
    {
        QString num = lst[index];
        data.push_back(num.toInt());
    }

    for(QVector<int>::iterator iter = data.begin();iter != data.end();iter++)
    {
            treap.insert(*iter);
    }

    scene->clear();
    treap.draw(scene);
}

void MainWindow::on_actionEnter_Key_triggered()
{
    int data = QInputDialog::getInt(this, "Enter Key.", "Enter Key: ");
    treap.insert(data);
    scene->clear();
    treap.draw(scene);
}

void MainWindow::on_actionErase_Key_triggered()
{
    int data = QInputDialog::getInt(this, "Erase Key.", "Enter Key: ");
    treap.erase(data);
    scene->clear();
    treap.draw(scene);
}

void MainWindow::on_FINISH_THE_TASK_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "The confirmation.", "Are you sure you want to finish trying?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        ui->stackedWidget->setCurrentIndex(2);
        QString str;
        unsigned count = 0;
        double percent = 100;
        treap.KLR(str);
        str.chop(1);
        if(MainWindow::ui->lineEditKLR->text() == str){
            count++;
        }
        MainWindow::ui->AllResults->append("KLR\n");
        MainWindow::ui->AllResults->append("You ansver:\t" + MainWindow::ui->lineEditKLR->text() + "\n");
        MainWindow::ui->AllResults->append("Right ansver:\t" + str + "\n");
        str.clear();
        treap.LKR(str);
        str.chop(1);
        if(MainWindow::ui->lineEditLKR->text() == str){
            count++;
        }
        MainWindow::ui->AllResults->append("LKR\n");
        MainWindow::ui->AllResults->append("You ansver:\t" + MainWindow::ui->lineEditLKR->text() + "\n");
        MainWindow::ui->AllResults->append("Right ansver:\t" + str + "\n");
        str.clear();
        treap.LRK(str);
        str.chop(1);
        if(MainWindow::ui->lineEditLRK->text() == str){
            count++;
        }
        MainWindow::ui->AllResults->append("LRK\n");
        MainWindow::ui->AllResults->append("You ansver:\t" + MainWindow::ui->lineEditLRK->text() + "\n");
        MainWindow::ui->AllResults->append("Right ansver:\t" + str + "\n");
        str.clear();
        str.push_back("Your results: ");
        str.push_back(QString::number(count));
        str.push_back("/3 (");
        str.push_back(QString::number(count*percent/3));
        str.push_back("%)\n");
        MainWindow::ui->AllResults->append(str);


        create2task();
    }
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton GoTo1 = QMessageBox::question(this, "Test.", "Do you want to start the test?", QMessageBox::Yes|QMessageBox::No);
    if(GoTo1 == QMessageBox::Yes){
        ui->stackedWidget->setCurrentIndex(1);
        on_actionCreate_variant_triggered();
    }
}

void MainWindow::on_FINISH_THE_TASK_3_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this, "The confirmation.", "Are you sure you want to finish trying?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        ui->stackedWidget->setCurrentIndex(3);
        QString str;
        unsigned count = 0;
        double percent = 100;
        treap.KLR(str);
        str.chop(1);
        if(MainWindow::ui->lineEditKLR_4->text() == str){
            count++;
        }
        MainWindow::ui->AllResults_2->append("KLR\n");
        MainWindow::ui->AllResults_2->append("You ansver:\t" + MainWindow::ui->lineEditKLR_4->text() + "\n");
        MainWindow::ui->AllResults_2->append("Right ansver:\t" + str + "\n");
        str.clear();
        treap.LKR(str);
        str.chop(1);
        if(MainWindow::ui->lineEditLKR_4->text() == str){
            count++;
        }
        MainWindow::ui->AllResults_2->append("LKR\n");
        MainWindow::ui->AllResults_2->append("You ansver:\t" + MainWindow::ui->lineEditLKR_4->text() + "\n");
        MainWindow::ui->AllResults_2->append("Right ansver:\t" + str + "\n");
        str.clear();
        treap.LRK(str);
        str.chop(1);
        if(MainWindow::ui->lineEditLRK_4->text() == str){
            count++;
        }
        MainWindow::ui->AllResults_2->append("LRK\n");
        MainWindow::ui->AllResults_2->append("You ansver:\t" + MainWindow::ui->lineEditLRK_4->text() + "\n");
        MainWindow::ui->AllResults_2->append("Right ansver:\t" + str + "\n");
        str.clear();
        str.push_back("Your results: ");
        str.push_back(QString::number(count));
        str.push_back("/3 (");
        str.push_back(QString::number(count*percent/3));
        str.push_back("%)\n");
        MainWindow::ui->AllResults_2->append(str);
    }
}
void MainWindow::on_pushButton_2_clicked()
{
    close();
}

void MainWindow::create2task(){
    int random;
    unsigned data = QInputDialog::getInt(this, "Create variant.", "Enter amount of elements: ");
    for (int i = 0; i < KEY_MAX; i++) {
        treap.erase(i);
    }
    for(unsigned i = 0; i < data; i++){
        random = rand() % KEY_MAX;
        treap.insert(random);
    }

    scene->clear();
    treap.draw(scene_2);

    int keyreturn = treap.Create2task();
    MainWindow::ui->FinishResults_2->setText("Key = " + QString::number(keyreturn) + "\tpriority = 0");
}

void MainWindow::on_pushButton_3_clicked()
{
    MainWindow::ui->FinishResults_2->clear();
    MainWindow::ui->FinishResults->clear();
    MainWindow::ui->FinishResults_2->clear();
    MainWindow::ui->lineEditLRK->clear();
    MainWindow::ui->lineEditLKR->clear();
    MainWindow::ui->lineEditKLR->clear();
    MainWindow::ui->lineEditLRK_4->clear();
    MainWindow::ui->lineEditLKR_4->clear();
    MainWindow::ui->lineEditKLR_4->clear();
    MainWindow::scene->clear();
    MainWindow::scene_2->clear();
    ui->stackedWidget->setCurrentIndex(0);
}
