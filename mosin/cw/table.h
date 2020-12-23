#ifndef TABLE_H
#define TABLE_H

#include <QGroupBox>
#include <QVBoxLayout>

class Table : public QGroupBox{
public:
    Table(QString);

private:
    QVBoxLayout* layout;
};

#endif // TABLE_H
