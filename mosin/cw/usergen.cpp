#include "usergen.h"

UserGen::UserGen() : QGroupBox(tr("Generation")){
    choose_file = new QPushButton(tr("choose file"));
    generate = new QPushButton(tr("generate"));
    layout = new QVBoxLayout;
    layout->addWidget(choose_file);
    layout->addWidget(generate);
    setLayout(layout);
}

UserGen::~UserGen(){
    delete choose_file;
    delete generate;
    delete layout;
}

QPushButton* UserGen::get_choose_button() const{
    return choose_file;
}

QPushButton* UserGen::get_generate_button() const{
    return generate;
}
