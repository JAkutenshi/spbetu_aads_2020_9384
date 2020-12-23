#ifndef USERGEN_H
#define USERGEN_H

#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>

class UserGen : public QGroupBox{
public:
    UserGen();
    ~UserGen();
    QPushButton* get_choose_button() const;
    QPushButton* get_generate_button() const;

private:
    QVBoxLayout* layout;
    QPushButton* choose_file;
    QPushButton* generate;
};

#endif // USERGEN_H
