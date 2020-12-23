#include "table.h"

Table::Table(QString title) : QGroupBox(title){
    layout = new QVBoxLayout;
}
