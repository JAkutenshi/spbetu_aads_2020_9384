#ifndef TREAP_H
#define TREAP_H

#include <cmath>
#include <iostream>
#include <cstdlib>

#include <QAction>
#include <QFileDialog>
#include <QTextBrowser>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#define NODE_WIDTH 20
#define NODE_HEIGHT 20

enum class TreapTraversal
{
    NLR,
    LNR,
    LRN
};

template <typename T>
class Treap
{
public:
    Treap() {};
    Treap(T key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {};

    void insert(T key, QVector<std::pair<Treap<T>*, QString>>* list = nullptr)
    {
        _insert(root, new Treap<T>(key, rand()), list);
    }

    void erase(T key, QVector<std::pair<Treap<T>*, QString>>* list = nullptr)
    {
        _erase(root, key, list);
        list->push_back(std::make_pair(root->copy(), "Получившееся дерево: "));
    }

    void draw(QGraphicsScene* scene)
    {
        this->_drawTree(scene, pow(2, this->maxDepth()) * 10, pow(2, this->maxDepth()) * 10);
    }

    int maxDepth() const
    {
        int lDepth = this->left != nullptr ? this->left->maxDepth() : 0;

        int rDepth = this->right != nullptr ? this->right->maxDepth() : 0;

        if (lDepth > rDepth)
            return(lDepth + 1);
        else return(rDepth + 1);

    }

    void save(QFile& file, TreapTraversal traversal)
    {
        _save(root, file, traversal);
    }

    QString getNodeData()
    {
        QString data;
        data.append("Ключ (");
        data.append(QString::fromStdString(std::to_string(this->key)));
        data.append("). Приоритет (");
        data.append(QString::fromStdString(std::to_string(this->priority)));
        data.append(") \n");
        return data;
    }

    Treap<T>* copy() const
    {
        Treap<T>* newTreap = new Treap<T>(this->key, this->priority);

        if (this->left != nullptr)
            newTreap->left = this->left->copy();

        if (this->right != nullptr)
            newTreap->right = this->right->copy();

        return newTreap;
    }

private:
    void split(Treap* t, T& key, Treap*& left, Treap*& right,QVector<std::pair<Treap<T>*, QString>>* list)
    {
        if (t == nullptr)
        {
            left = right = nullptr;
        }
        else if (t->key > key)
        {

            QString info;
            info.append("Ключ новой ноды (");
            info.append(QString::fromStdString(std::to_string(key)));
            info.append(") <= Ключа текущей ноды! (");
            info.append(QString::fromStdString(std::to_string(t->key)));
            info.append(")\nИдем в правую ветвь!");
            list->push_back(std::make_pair(t->copy(), info));

            split(t->left, key, left, t->left, list);
            right = t;
        }
        else
        {
            QString info;
            info.append("Ключ новой ноды (");
            info.append(QString::fromStdString(std::to_string(key)));
            info.append(") > Ключа текущей ноды! (");
            info.append(QString::fromStdString(std::to_string(t->key)));
            info.append(")\nИдем в левую ветвь!");
            list->push_back(std::make_pair(t->copy(), info));

            split(t->right, key, t->right, right, list);
            left = t;
        }
    }

    void merge(Treap*& t, Treap* left, Treap* right, QVector<std::pair<Treap<T>*, QString>>* list)
    {
        if (!left)
        {
            t = right;
            return;
        }
        if (!right)
        {
            t = left;
            return;
        }

        if (left->priority >= right->priority)
        {
            QString info;
            info.append("Приоритет левой ноды (");
            info.append(QString::fromStdString(std::to_string(left->priority)));
            info.append(") > Приоритета правой ноды! (");
            info.append(QString::fromStdString(std::to_string(right->priority)));
            info.append(")\nИдем в правую ветвь!");
            list->push_back(std::make_pair(t->copy(), info));

            merge(left->right, left->right, right, list);
            t = left;
        }
        else
        {
            QString info;
            info.append("Приоритет левой ноды (");
            info.append(QString::fromStdString(std::to_string(left->priority)));
            info.append(") <= Приоритета правой ноды! (");
            info.append(QString::fromStdString(std::to_string(right->priority)));
            info.append(")\nИдем в левую ветвь!");
            list->push_back(std::make_pair(t->copy(), info));

            merge(right->left, left, right->left, list);
            t = right;
        }
    }

    void _insert(Treap*& t, Treap* it, QVector<std::pair<Treap<T>*, QString>>* list)
    {
        if (t == nullptr)
        {
            t = it;
            list->push_back(std::make_pair(t->copy(), "Добавляем элемент в дерево: "));
            return;
        }

        if (it->priority > t->priority)
        {
            QString info;
            info.append("Приоритет новой ноды ");
            info.append(it->getNodeData());
            info.append("> Приоритета текущей ноды! ");
            info.append(t->getNodeData());
            info.append("\nВызываем метод split для перестраивания дерева!");
            list->push_back(std::make_pair(t->copy(), info));

            split(t, it->key, it->left, it->right, list);
            t = it;

            list->push_back(std::make_pair(t->copy(), "Получившееся дерево: "));
        }
        else
        {
            if (it->key < t->key)
            {
                QString info;
                info.append("Ключ новой ноды ");
                info.append(it->getNodeData());
                info.append("< Ключа текущей ноды! ");
                info.append(t->getNodeData());
                info.append("\nИдем в левую ветвь.");
                list->push_back(std::make_pair(t->copy(), info));

                _insert(t->left, it, list);

                list->push_back(std::make_pair(t->copy(), "Получившееся дерево: "));
            }
            else
            {
                QString info;
                info.append("Ключ новой ноды ");
                info.append(it->getNodeData());
                info.append(">= Ключа текущей ноды! ");
                info.append(t->getNodeData());
                info.append("\nИдем в правую ветвь.");
                list->push_back(std::make_pair(t->copy(), info));

                _insert(t->right, it, list);

                list->push_back(std::make_pair(t->copy(), "Получившееся дерево: "));
            }
        }
    }

    void _erase (Treap*& t, T key, QVector<std::pair<Treap<T>*, QString>>* list)
    {
        if (t == nullptr)
        {
            //list->back().second.append("\nНода с таким значением не найдена!");
            return;
        }
        if (t->key == key)
        {
            QString info;
            info.append("Ключ (");
            info.append(key);
            info.append(") Найден! Это нода: ");
            info.append(t->getNodeData());
            list->push_back(std::make_pair(t->copy(), info));

            merge(t, t->left, t->right, list);
        }
        else if (t->key > key)
        {
            QString info;
            info.append("Ключ этой ноды ");
            info.append(t->getNodeData());
            info.append("> искомого ключа! (");
            info.append(key);
            info.append(")\nИдем в левую ветвь.");
            list->push_back(std::make_pair(t->copy(), info));

            _erase(t->left, key, list);

            //list->push_back(std::make_pair(t->copy(), "Получившееся дерево: "));
        }
        else
        {
            QString info;
            info.append("Ключ этой ноды ");
            info.append(t->getNodeData());
            info.append("< искомого ключа! (");
            info.append(key);
            info.append(")\nИдем в правую ветвь.");
            list->push_back(std::make_pair(t->copy(), info));

            _erase(t->right, key, list);

            //list->push_back(std::make_pair(t->copy(), "Получившееся дерево: "));
        }

        //list->push_back(std::make_pair(t->copy(), "Получившееся дерево: "));
    }

    void _drawTree(QGraphicsScene* scene, int width, int lineSize, int depth = 0, bool circle = true)
    {
        QPen pen;
        if (this == nullptr)
        {
            return;
        }
        else
        {
            if (circle)
                pen.setBrush(Qt::red);
            else
                pen.setBrush(Qt::green);

            pen.setWidth(4);

            if (this->left != nullptr)
                scene->addLine(width + NODE_WIDTH / 2, depth + NODE_HEIGHT / 2, width - lineSize / 2 + NODE_WIDTH / 2, depth + 60 + NODE_HEIGHT / 2, pen);

            if (this->right != nullptr)
                scene->addLine(width + NODE_WIDTH / 2, depth + NODE_HEIGHT / 2, width + lineSize / 2 + NODE_WIDTH / 2, depth + 60 + NODE_HEIGHT / 2, pen);

            scene->addEllipse(width, depth, NODE_WIDTH, NODE_HEIGHT, pen, QBrush(Qt::gray));

            QString nodeKey, nodePriotity;
            nodeKey = QString::fromStdString(std::to_string(this->key));
            nodePriotity = QString::fromStdString(std::to_string(this->priority));

            QGraphicsTextItem* textKey = new QGraphicsTextItem;
            QGraphicsTextItem* textPriority = new QGraphicsTextItem;

            const QColor myTextColor = QColor(Qt::black);

            textKey->setDefaultTextColor(myTextColor);
            textKey->setPlainText(nodeKey);
            textKey->setPos(width + nodeKey.size() / 3, depth + 17);
            scene->addItem(textKey);

            textPriority->setDefaultTextColor(myTextColor);
            textPriority->setPlainText(nodePriotity);
            textPriority->setPos(width + nodePriotity.size() / 3, depth + 30);
            scene->addItem(textPriority);

            if (this->left != nullptr)
                this->left->_drawTree(scene, width - lineSize / 2, lineSize / 2, depth + 60, false);

            if (this->right != nullptr)
                this->right->_drawTree(scene, width + lineSize / 2, lineSize / 2, depth + 60, false);
        }
    }

    void _save(Treap*& t, QFile& file, TreapTraversal traversal)
    {
        if (traversal == TreapTraversal::NLR)
            file.write(t->getNodeData().toUtf8());

         if (t->left != nullptr)
            _save(t->left, file, traversal);

         if (traversal == TreapTraversal::LNR)
             file.write(t->getNodeData().toUtf8());

         if (t->right != nullptr)
            _save(t->right, file, traversal);

         if (traversal == TreapTraversal::LRN)
             file.write(t->getNodeData().toUtf8());
    }

private:
    T key;
    int priority;
    Treap* left, * right;
    Treap* root = nullptr;

};

#endif // TREAP_H
