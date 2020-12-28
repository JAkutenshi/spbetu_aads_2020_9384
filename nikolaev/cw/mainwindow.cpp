#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    zoom = new Graphics_view_zoom(ui->graphicsView);
    zoom->set_modifiers(Qt::NoModifier);

    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->textBrowser->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Open_triggered()
{
    QString filepath = QFileDialog::getOpenFileName(this, "Load", QDir::homePath(), tr("Load File (*.txt)"));

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
            data.emplace_back(num.toInt());
        }

        for(QVector<int>::iterator iter = data.begin();iter != data.end();iter++)
        {
            if (ui->actionStep_by_step_analysis->isChecked())
            {
                ui->textBrowser->append("");
                treap.insert(*iter, scene, ui->textBrowser);
            }
            else
            {
                treap.insert(*iter);
            }
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
        data.emplace_back(num.toInt());
    }

    for(QVector<int>::iterator iter = data.begin();iter != data.end();iter++)
    {
        if (ui->actionStep_by_step_analysis->isChecked())
        {
            ui->textBrowser->append("");
            treap.insert(*iter, scene, ui->textBrowser);
        }
        else
        {
            treap.insert(*iter);
        }
    }

    scene->clear();
    treap.draw(scene);
}

void MainWindow::on_actionEnter_Key_triggered()
{
    int data = QInputDialog::getInt(this, "Enter Key.", "Enter Key: ");
    if (ui->actionStep_by_step_analysis->isChecked())
    {
        ui->textBrowser->append("");
        treap.insert(data, scene, ui->textBrowser);
    }
    else
    {
        treap.insert(data);
    }

    scene->clear();
    treap.draw(scene);
}

void MainWindow::on_actionErase_Key_triggered()
{
    int data = QInputDialog::getInt(this, "Erase Key.", "Enter Key: ");
    if (ui->actionStep_by_step_analysis->isChecked())
    {
        ui->textBrowser->append("");
        treap.erase(data, scene, ui->textBrowser);
    }
    else
    {
        treap.erase(data);
    }

    scene->clear();
    treap.draw(scene);
}

void MainWindow::on_actionGanerate_triggered()
{
    int size = QInputDialog::getInt(this, "Generate Treap.", "Enter Count Numbers: ");

    if (size <= 0)
    {
        QMessageBox::warning(this, "Warning!", "Wrong data!");
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this, "Generate Treap.", "You want to specify a range?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes)
        {
            int min = QInputDialog::getInt(this, "Enter min.", "Enter min: ");
            int max = QInputDialog::getInt(this, "Enter max.", "Enter max: ");

            if (min > max)
                std::swap(min, max);

            for(int iter = 0; iter < size; iter++)
            {
                if (ui->actionStep_by_step_analysis->isChecked())
                {
                    ui->textBrowser->append("");
                    treap.insert(rand() % (max - min + 1) + min, scene, ui->textBrowser);
                }
                else
                {
                    treap.insert(rand() % (max - min + 1) + min);
                }
            }
        }
        else
        {
            for(int iter = 0; iter < size; iter++)
            {
                if (ui->actionStep_by_step_analysis->isChecked())
                {
                    ui->textBrowser->append("");
                    treap.insert(rand(), scene, ui->textBrowser);
                }
                else
                {
                    treap.insert(rand());
                }
            }
        }

        scene->clear();
        treap.draw(scene);
    }
}

void MainWindow::on_actionImage_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save Treap Image", QDir::homePath(), tr("TreapImage(*.png)"));

    if (scene->width() > 8192 || scene->height() > 4320 || scene->width() < 1 || scene->height() < 1)
    {
        QMessageBox::warning(this, "Warning!", "Cannot save image!");
    }
    else
    {
        QImage image(scene->width(), scene->height(), QImage::Format_ARGB32_Premultiplied);
        image.fill(NULL);

        QPainter painter(&image);
        scene->render(&painter);

        image.save(filepath);
    }
}

void MainWindow::on_actionPreorder_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save Treap Info", QDir::homePath(), tr("TreapPreorder(*.txt)"));

    QFile file(filepath);
    if(!file.open(QFile::WriteOnly | QFile::WriteOnly))
    {
        QMessageBox::warning(this, "Warning!", "File not open.");
    }
    else
    {
        QTextStream stream(&file);
        treap.save(Tree_Traversals::Preorder, stream);
    }

    file.close();
}

void MainWindow::on_actionInorder_triggered()
{
    QString filepath = QFileDialog::getSaveFileName(this, "Save Treap Info", QDir::homePath(), tr("TreapInorder(*.txt)"));

    QFile file(filepath);
    if(!file.open(QFile::WriteOnly | QFile::WriteOnly))
    {
        QMessageBox::warning(this, "Warning!", "File not open.");
    }
    else
    {
        QTextStream stream(&file);
        treap.save(Tree_Traversals::Inorder, stream);
    }

    file.close();
}

void MainWindow::on_actionPostorder_triggered()
{

    QString filepath = QFileDialog::getSaveFileName(this, "Save Treap Info", QDir::homePath(), tr("TreapPostorder(*.txt)"));
    QFile file(filepath);
    if(!file.open(QFile::WriteOnly | QFile::WriteOnly))
    {
        QTextStream stream(&file);
        QMessageBox::warning(this, "Warning!", "File not open.");
    }
    else
    {
        QTextStream stream(&file);
        treap.save(Tree_Traversals::Postorder, stream);
    }

    file.close();
}

void MainWindow::on_actionStep_by_step_analysis_triggered(bool checked)
{
    if (checked)
    {
       ui->pushButton->show();
       ui->pushButton_2->show();
       ui->textBrowser->show();
    }
    else
    {
       ui->pushButton->hide();
       ui->pushButton_2->hide();
       ui->textBrowser->hide();
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->textBrowser->clear();
}
