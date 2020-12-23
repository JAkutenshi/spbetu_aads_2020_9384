#include "window.h"
#include "tree.h"

#include <QFileDialog>
#include <fstream>
#include <sstream>
#include <cmath>
#include <ctime>

Window::Window() : tree(nullptr), array_size(1000), index(0), array(new int[array_size]){
    setFixedSize(800, 600);

    scene = new Scene();
    scene->add_item(tree);
    scene->add_line(tree);

    view = new QGraphicsView(scene);
    view->setFixedWidth(480);

    statistic = new Statistic();
    program_gen = new ProgramGen();
    user_gen = new UserGen();


    connect(user_gen->get_choose_button(), SIGNAL(clicked(bool)), this, SLOT(chose_file()));
    connect(user_gen->get_generate_button(), SIGNAL(clicked(bool)), this, SLOT(user_generate()));
    connect(program_gen->get_generate_button(), SIGNAL(clicked(bool)), this, SLOT(program_generate()));

    layout = new QGridLayout;
    layout->addWidget(view,0,0,3,1);
    layout->addWidget(statistic,0,1);
    layout->addWidget(program_gen,1,1);
    layout->addWidget(user_gen,2,1);

    this->setLayout(layout);
}

Window::~Window(){
    if(tree){
        delete tree;
    }
    delete scene;
    delete view;
    delete statistic;
    delete program_gen;
    delete user_gen;
    delete layout;
    delete[] array;
}

void Window::user_generate(){
    if(tree){
        delete tree;
    }
    tree = nullptr;
    clock_t start = clock();
    for(int i = 0; i < index; i++){
        tree ? tree = tree->insert(tree, array[i]) : tree = new Tree(array[i]);
    }
    clock_t end = clock();
    double mseconds = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    scene->clear();
    scene->add_item(tree);
    scene->add_line(tree);
    statistic->add_info(mseconds, tree->get_operation_count(tree), (int)log2(index) + 1, tree->get_depth(tree), tree->average_find_time(tree), tree->worst_find_time(tree));
}

void Window::program_generate(){
    index = 0;
    double mseconds = 0;
    for(int i = 0; i < 8; i++){
        array[index++] = i;
    }
    if(program_gen->get_best_case_button()->isChecked()){
        do{
            if(tree){
                delete tree;
            }
            tree = nullptr;
            clock_t start = clock();
            for(int i = 0; i < 8; i++){
                tree ? tree = tree->insert(tree, array[i]) : tree = new Tree(array[i]);
            }
            clock_t end = clock();
            mseconds = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        }while(tree->get_depth(tree) != log2(8) + 1);
        scene->clear();
        scene->add_item(tree);
        scene->add_line(tree);
        statistic->add_info(mseconds, tree->get_operation_count(tree), (int)log2(index) + 1, tree->get_depth(tree), tree->average_find_time(tree), tree->worst_find_time(tree));
    }
    else if(program_gen->get_middle_case_button()->isChecked()){
        do{
            if(tree){
                delete tree;
            }
            tree = nullptr;
            clock_t start = clock();
            for(int i = 0; i < 8; i++){
                tree ? tree = tree->insert(tree, array[i]) : tree = new Tree(array[i]);
            }
            clock_t end = clock();
            mseconds = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        }while(tree->get_depth(tree) >= log2(8)+1 && tree->get_depth(tree) < 7);
        scene->clear();
        scene->add_item(tree);
        scene->add_line(tree);
        statistic->add_info(mseconds, tree->get_operation_count(tree), (int)log2(index) + 1, tree->get_depth(tree), tree->average_find_time(tree), tree->worst_find_time(tree));
    }
    else if(program_gen->get_worst_case_button()->isChecked()){
        do{
            if(tree){
                delete tree;
            }
            tree = nullptr;
            clock_t start = clock();
            for(int i = 0; i < 8; i++){
                tree ? tree = tree->insert(tree, array[i]) : tree = new Tree(array[i]);
            }
            clock_t end = clock();
            mseconds = (double)(end - start) / CLOCKS_PER_SEC * 1000;
        }while(tree->get_depth(tree) != 8);
        scene->clear();
        scene->add_item(tree);
        scene->add_line(tree);
        statistic->add_info(mseconds, tree->get_operation_count(tree), (int)log2(index) + 1, tree->get_depth(tree), tree->average_find_time(tree), tree->worst_find_time(tree));
    }
}

void Window::chose_file(){
    QString _file = QFileDialog::getOpenFileName(this, tr("Open File"));
    char *path = _file.toUtf8().data();

    std::ifstream file(path);
    if(file.is_open()){
        index = 0;
        std::string temp;
        while(std::getline(file, temp)){
            std::istringstream str(temp);
            std::string num;
            while(getline(str, num, ' ')){
                array[index++] = std::stoi(num);
            }
        }
        file.close();
    }
}
