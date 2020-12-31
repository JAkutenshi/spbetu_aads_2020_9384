#ifndef TREAP_H
#define TREAP_H

#include <iostream>
#include <cstdlib>

#include <QGraphicsScene>
#include <QGraphicsTextItem>

#define NODE_WIDTH 40
#define NODE_HEIGHT 40

template <typename T>
class Treap
{
public:
    Treap() {};
    Treap(T key, int priority) : key(key), priority(priority), left(nullptr), right(nullptr) {};

    void insert(T key)
    {
        _insert(root, new Treap<T>(key, rand()));
    }

    void erase(T key)
    {
        _erase(root, key);
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
            /* compute the depth of each subtree */
            int lDepth = maxDepth(t->left);
            int rDepth = maxDepth(t->right);

            /* use the larger one */
            if (lDepth > rDepth)
                return(lDepth + 1);
            else return(rDepth + 1);
        }
    }
private:
    void split(Treap* t, T& key, Treap*& left, Treap*& right)
    {
        if (t == nullptr)
        {
            left = right = nullptr;
        }
        else if (key < t->key)
        {
            split(t->left, key, left, t->left);
            right = t;
        }
        else
        {
            split(t->right, key, t->right, right);
            left = t;
        }
    }

    void merge(Treap*& t, Treap* left, Treap* right)
    {
        if (!left || !right)
            t = left ? left : right;
        else if (left->priority >= right->priority)
        {
            merge(left->right, left->right, right);
            t = left;
        }
        else
        {
            merge(right->left, left, right->left);
            t = right;
        }
    }

    void _insert(Treap*& t, Treap* it)
    {
        if (t == nullptr)
        {
            t = it;
            return;
        }

        if (it->priority > t->priority)
        {
            split(t, it->key, it->left, it->right);
            t = it;
        }
        else
        {
            _insert(it->key < t->key ? t->left : t->right, it);
        }
    }

    void _erase (Treap*& t, T key)
    {
        if (t == nullptr)
            return;
        if (t->key == key)
            this->merge(t, t->left, t->right);
        else if (t->key > key)
            this->_erase(t->left, key);
        else
            this->_erase(t->right, key);
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
            pen.setWidth(2);

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

            // TODO: Выравнивание текста.
            textKey->setDefaultTextColor(myTextColor);
            textKey->setPlainText(nodeKey);
            textKey->setPos(width + nodeKey.size() / 2, depth);
            scene->addItem(textKey);

            // TODO: Выравнивание текста.
            textPriority->setDefaultTextColor(myTextColor);
            textPriority->setPlainText(nodePriotity);
            textPriority->setPos(width + nodePriotity.size() / 2, depth + 10);
            scene->addItem(textPriority);

            _draw(scene, t->left, width - lineSize / 2, lineSize / 2, depth + 60);
            _draw(scene, t->right, width + lineSize / 2, lineSize / 2, depth + 60);
        }

    }

private:
    T key;
    int priority;
    Treap* left, * right;
    Treap* root = nullptr;

};

#endif // TREAP_H
