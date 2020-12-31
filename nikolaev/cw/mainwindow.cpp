#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    zoom = new graphicsviewzoom(ui->graphicsView);
    zoom->set_modifiers(Qt::NoModifier);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    ui->delete_item->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_from_file_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Load", QDir::homePath(), tr("Load File (*.txt)"));

    QFile file(filepath);
    if(!file.open(QFile::ReadOnly | QFile::ReadOnly))
    {
        QMessageBox::warning(this, "Внимание!", "Файл не открыт!");
    }
    else
    {
        QString str = file.readLine();

        QStringList lst = str.split(" ");

        for (qsizetype index = 0; index < lst.size(); index++)
        {
            QString num = lst[index];
            treap.insert(num.toInt(), &list);
            ui->horizontalSlider->setRange(0, list.size() - 1);
        }
    }

    file.close();
}

void MainWindow::on_from_string_triggered()
{
    QString str = QInputDialog::getText(this, "Ввод последовательности.", "Введите последовательность чисел: ");
    
    QStringList lst = str.split(" ");
    for (qsizetype index = 0; index < lst.size(); index++)
    {
        QString num = lst[index];
        treap.insert(num.toInt(), &list);
        ui->horizontalSlider->setRange(0, list.size() - 1);
    }
}

void MainWindow::on_add_item_triggered()
{
    int data = QInputDialog::getInt(this, "Добавление элемента.", "Введите ключ: ");
    treap.insert(data, &list);
    ui->horizontalSlider->setRange(0, list.size() - 1);
}

void MainWindow::on_delete_item_triggered()
{
    int data = QInputDialog::getInt(this, "Удаление элемента.", "Введите ключ: ");
    treap.erase(data, &list);
    ui->horizontalSlider->setRange(0, list.size() - 1);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ui->textBrowser->clear();
    ui->textBrowser->append(list[position].second);

    scene->clear();
    list[position].first->draw(scene);
}

void MainWindow::on_generate_triggered()
{
    int size = QInputDialog::getInt(this, "Генерация элементов.", "Введите количество элементов: ");

    if (size <= 0)
    {
        QMessageBox::warning(this, "Внимание!", "Неверные данные!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Генерация элементов.", "Вы хотите задать минимальное / максимальное значение?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            int min = QInputDialog::getInt(this, "Enter min.", "Enter min: ");
            int max = QInputDialog::getInt(this, "Enter max.", "Enter max: ");

            if (min > max)
                std::swap(min, max);

            for(int iter = 0; iter < size; iter++)
            {
                 treap.insert(rand() % (max - min + 1) + min, &list);
            }
        }
        else
        {
            for(int iter = 0; iter < size; iter++)
            {
                 treap.insert(rand(), &list);
            }
        }

        ui->horizontalSlider->setRange(0, list.size() - 1);
        scene->clear();
        list.back().first->draw(scene);
        ui->textBrowser->clear();
        ui->textBrowser->append(list.back().second);

        ui->delete_item->setEnabled(true);
    }
}

void MainWindow::on_NLR_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Сохранить в тектовый документ.", QDir::homePath(), tr("Treap(*.txt)"));

        QFile file(filepath);
        if(!file.open(QFile::WriteOnly | QFile::WriteOnly))
        {
            QMessageBox::warning(this, "Внимание!", "Файл не открыт.");
        }
        else
        {
            treap.save(file, TreapTraversal::NLR);
        }

        file.close();
}

void MainWindow::on_LNR_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Сохранить в тектовый документ.", QDir::homePath(), tr("Treap(*.txt)"));

        QFile file(filepath);
        if(!file.open(QFile::WriteOnly | QFile::WriteOnly))
        {
            QMessageBox::warning(this, "Внимание!", "Файл не открыт.");
        }
        else
        {
            treap.save(file, TreapTraversal::LNR);
        }

        file.close();
}

void MainWindow::on_LRN_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Сохранить в тектовый документ.", QDir::homePath(), tr("Treap(*.txt)"));

        QFile file(filepath);
        if(!file.open(QFile::WriteOnly | QFile::WriteOnly))
        {
            QMessageBox::warning(this, "Внимание!", "Файл не открыт.");
        }
        else
        {
            treap.save(file, TreapTraversal::LRN);
        }

        file.close();
}
