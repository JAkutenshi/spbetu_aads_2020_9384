#include "programgen.h"

ProgramGen::ProgramGen() : QGroupBox(tr("Generation")){
    best_case = new QRadioButton(tr("best case"));
    middle_case = new QRadioButton(tr("average case"));
    worst_case = new QRadioButton(tr("worst case"));
    generate = new QPushButton(tr("generate"));

    best_case->setChecked(true);

    layout = new QVBoxLayout;
    layout->addWidget(best_case);
    layout->addWidget(middle_case);
    layout->addWidget(worst_case);
    layout->addWidget(generate);
    setLayout(layout);
}

ProgramGen::~ProgramGen(){
    delete best_case;
    delete middle_case;
    delete worst_case;
    delete generate;
    delete layout;
}

QRadioButton* ProgramGen::get_best_case_button() const{
    return best_case;
}

QRadioButton* ProgramGen::get_middle_case_button() const{
    return middle_case;
}

QRadioButton* ProgramGen::get_worst_case_button() const{
    return worst_case;
}

QPushButton* ProgramGen::get_generate_button() const{
    return generate;
}
