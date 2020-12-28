#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <cstdlib>

#include <QAction>
#include <QFileDialog>
#include <QTextBrowser>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

#include <QMessageBox>

#define NODE_WIDTH 20
#define NODE_HEIGHT 20

enum class Tree_Traversals
{
    Preorder,
    Inorder,
    Postorder
};

template <typename T>
class Treap
{
public:
    Treap() {};
    Treap(T key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {};

    void insert(T key, QGraphicsScene* scene = nullptr, QTextBrowser* browser = nullptr)
    {
        _insert(root, new Treap<T>(key, rand()), scene, browser);
    }

    void erase(T key, QGraphicsScene* scene = nullptr, QTextBrowser* browser = nullptr)
    {
        _erase(root, key, scene, browser);
    }

    void draw(QGraphicsScene* scene)
    {
        _draw(scene, root, pow(2, maxDepth(root)) * 10, pow(2, maxDepth(root)) * 10);
    }

    int maxDepth(Treap*& t)
    {
        if (t == nullptr)
            return 0;
        else
        {
            int lDepth = maxDepth(t->left);
            int rDepth = maxDepth(t->right);

            if (lDepth > rDepth)
                return(lDepth + 1);
            else return(rDepth + 1);
        }
    }

    void save(const Tree_Traversals type, QTextStream& stream)
    {
        _save(type, stream, root);
    }

private:
    void split(Treap* t, T& key, Treap*& left, Treap*& right, QGraphicsScene* scene, QTextBrowser* browser)
    {
        if (t == nullptr)
        {
            left = right = nullptr;
        }
        else if (key < t->key)
        {
            if (scene && browser)
            {
                QString info;
                info.append("Split Node: Key of new Node less than Key of this Node");
                info.append(writeInfo(t));
                info.append(". Go right.");
                browser->append(info);
            }
            split(t->left, key, left, t->left, scene, browser);
            right = t;
        }
        else
        {
            if (scene && browser)
            {
                QString info;
                info.append("Split Node: Key of new Node less than Key of this Node");
                info.append(writeInfo(t));
                info.append(". Go left.");
                browser->append(info);
            }
            split(t->right, key, t->right, right, scene, browser);
            left = t;
        }
    }

    void merge(Treap*& t, Treap* left, Treap* right, QGraphicsScene* scene, QTextBrowser* browser)
    {
        if (!left || !right)
            t = left ? left : right;
        else if (left->priority >= right->priority)
        {
            if (scene && browser)
            {
                QString info;
                info.append("Merge Node: Priority of left Node ");
                info.append(writeInfo(left));
                info.append(" highter than Priority of right Node ");
                info.append(writeInfo(right));
                browser->append(info);
            }

            merge(left->right, left->right, right, scene, browser);
            t = left;
        }
        else
        {
            QString info;
            info.append("Merge Node: Priority of left Node ");
            info.append(writeInfo(left));
            info.append(" less than Priority of right Node ");
            info.append(writeInfo(right));
            browser->append(info);

            merge(right->left, left, right->left, scene, browser);
            t = right;
        }
    }

    void _insert(Treap*& t, Treap* it, QGraphicsScene* scene, QTextBrowser* browser)
    {
        if (t == nullptr)
        {
            if (scene && browser)
            {
                QString info;
                info.append("Insert Node: ");
                info.append(writeInfo(it));
                browser->append(info);
            }

            t = it;
            return;
        }

        if (it->priority > t->priority)
        {
            if (scene && browser)
            {
                QString info;
                info.append("Insert Node: Priority of New Node ");
                info.append(writeInfo(it));
                info.append(" highter than Priority of This Node ");
                info.append(writeInfo(t));
                browser->append(info);
            }

            split(t, it->key, it->left, it->right, scene, browser);
            t = it;
        }
        else
        {
            if (scene && browser)
            {
                QString info;
                info.append("Insert Node: New Node ");
                info.append(writeInfo(it));
                info.append(" less than key of This Node ");
                info.append(writeInfo(t));
                browser->append(info);
            }

            _insert(it->key < t->key ? t->left : t->right, it, scene, browser);
        }
    }

    void _erase (Treap*& t, T key, QGraphicsScene* scene, QTextBrowser* browser)
    {
        if (t == nullptr)
        {
            if (scene && browser)
            {
                browser->append("Erase Node: Key not found!");
            }

            return;
        }
        if (t->key == key)
        {
            if (scene && browser)
            {
                browser->append("Erase Node: Key found!");

                QString info;
                info.append("Erase ");
                info.append(writeInfo(t));
                browser->append(info);
            }

            this->merge(t, t->left, t->right, scene, browser);
        }
        else if (t->key > key)
        {
            if (scene && browser)
            {
                QString info;
                info.append("Erease Node: This Node ");
                info.append(writeInfo(t));
                info.append(" highter than that key ");
                info.append(writeInfo(t));
                info.append(" Go to left node.");
                browser->append(info);
            }
            this->_erase(t->left, key, scene, browser);
        }
        else
        {
            if (scene && browser)
            {
                QString info;
                info.append("Erease Node: This Node ");
                info.append(writeInfo(t));
                info.append(" less than that key ");
                info.append(writeInfo(t));
                info.append(" Go to rigth node.");
                browser->append(info);
            }
            this->_erase(t->right, key, scene, browser);
        }
    }

    void _draw(QGraphicsScene* scene, Treap*& t, int width, int lineSize, int depth = 0)
    {
        QPen pen;
        if (t == nullptr)
        {
            return;
        }
        else
        {
            pen.setBrush(Qt::black);
            pen.setWidth(4);

            if (t->left != nullptr)
                scene->addLine(width + NODE_WIDTH / 2, depth + NODE_HEIGHT / 2, width - lineSize / 2 + NODE_WIDTH / 2, depth + 60 + NODE_HEIGHT / 2, pen);

            if (t->right != nullptr)
                scene->addLine(width + NODE_WIDTH / 2, depth + NODE_HEIGHT / 2, width + lineSize / 2 + NODE_WIDTH / 2, depth + 60 + NODE_HEIGHT / 2, pen);

            scene->addEllipse(width, depth, NODE_WIDTH, NODE_HEIGHT, pen, QBrush(Qt::gray));

            QString nodeKey, nodePriotity;
            nodeKey = QString::fromStdString(std::to_string(t->key));
            nodePriotity = QString::fromStdString(std::to_string(t->priority));

            QGraphicsTextItem* textKey = new QGraphicsTextItem;
            QGraphicsTextItem* textPriority = new QGraphicsTextItem;

            const QColor myTextColor = QColor(Qt::black);

            textKey->setDefaultTextColor(myTextColor);
            textKey->setPlainText(nodeKey);
            textKey->setPos(width + nodeKey.size() / 2, depth + 15);
            scene->addItem(textKey);

            textPriority->setDefaultTextColor(myTextColor);
            textPriority->setPlainText(nodePriotity);
            textPriority->setPos(width + nodePriotity.size() / 2, depth + 30);
            scene->addItem(textPriority);

            _draw(scene, t->left, width - lineSize / 2, lineSize / 2, depth + 60);
            _draw(scene, t->right, width + lineSize / 2, lineSize / 2, depth + 60);
        }

    }

    void _save(const Tree_Traversals type, QTextStream& stream, Treap*& t)
    {
        if (t == nullptr)
        {
            return;
        }

        if (type == Tree_Traversals::Inorder)
        {
            _save(type, stream, t->left);

            writeInfo(stream, t);

            _save(type, stream, t->right);
        }
        else if (type == Tree_Traversals::Postorder)
        {
            std::string data;

            _save(type, stream, t->left);
            _save(type, stream, t->right);

            writeInfo(stream, t);
        }
        else if (type == Tree_Traversals::Preorder)
        {
            writeInfo(stream, t);

            _save(type, stream, t->left);
            _save(type, stream, t->right);
        }
    }

    QString writeInfo(Treap*& t)
    {
        std::string data;

        data += "Key: ";
        data += std::to_string(t->key);
        data += " ";
        data += "Priority: ";
        data += std::to_string(t->priority);

        QString info;
        info.append(QString::fromStdString(data));

        return info;
    }

    void writeInfo(QTextStream& stream, Treap*& t)
    {
        std::string data;

        data += "Key: ";
        data += std::to_string(t->key);
        data += " ";
        data += "Priority: ";
        data += std::to_string(t->priority);
        data += "\n";

        QString info;
        info.append(QString::fromStdString(data));

        stream << info;
    }

private:
    T key;
    int priority;
    Treap* left, * right;
    Treap* root = nullptr;

};

#endif // TREAP_H
