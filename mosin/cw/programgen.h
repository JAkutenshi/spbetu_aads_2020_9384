#ifndef PROGRAMGEN_H
#define PROGRAMGEN_H

#include <QGroupBox>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPushButton>

class ProgramGen : public QGroupBox{
public:
    ProgramGen();
    ~ProgramGen();
    QRadioButton* get_best_case_button() const;
    QRadioButton* get_middle_case_button() const;
    QRadioButton* get_worst_case_button() const;
    QPushButton* get_generate_button() const;

private:
    QVBoxLayout* layout;
    QRadioButton* best_case;
    QRadioButton* middle_case;
    QRadioButton* worst_case;
    QPushButton* generate;
};

#endif // PROGRAMGEN_H
