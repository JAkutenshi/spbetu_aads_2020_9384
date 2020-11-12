#include <iostream>
#include "BinaryTree.h"
int index = 0;

int numberOfElements(BinaryTree<char> *root)
{
    int count = 1;
    if (root->leftSubTree != nullptr) {
        count += numberOfElements(root->leftSubTree);
    }
    if (root->rightSubTree != nullptr) {
        count += numberOfElements(root->rightSubTree);
    }
    return count;
}

void makeDirectOrderArray(BinaryTree<char> *tree,char *array){
    if(!tree->isNull(tree)){
        array[index] = tree->rootData;
        index++;
        makeDirectOrderArray(tree->leftSubTree,array);
        makeDirectOrderArray(tree->rightSubTree,array);
    }
}

void check(BinaryTree<char> *tree){
    if(!tree->isNull(tree)){
        cout<<tree->rootData;
        check(tree->leftSubTree);
        check(tree->rightSubTree);
    }
}

void atLeastTwoEqualElements(BinaryTree<char> *tree){
    int size = numberOfElements(tree);
    char *array = new char[size];
    makeDirectOrderArray(tree,array);

    int i, j;
    char duplicate = '\0';

    for(i = 0; i < size; i++) {
        for (j = i + 1; j < size; j++) {
            if (array[i] == array[j]) {
                duplicate = array[i];
                break;
            }
        }
        if(duplicate!='\0') break;
    }

    if(duplicate=='\0'){
        cout<<"There are no identical elements"<<endl;
    }

    else {
        cout<<"At least one identical element - "<<duplicate<<endl;
    }
}

void displayBinaryTree(BinaryTree<char> *tree, int depth = 0){
    if(!tree->isNull(tree)){
        displayBinaryTree(tree->rightSubTree,depth+1);
        for(unsigned int i = 0; i<depth; i++)
            std::cout << "\t";
        std::cout << tree->rootData << std::endl;
        displayBinaryTree(tree->leftSubTree, depth+1);
    }
}

int main(){

    BinaryTree<char> p;
    BinaryTree<char> *j;

    cout<<"Choose way to enter forest:\n1 - read from console\n2 - read from file"<<endl;
    char c;
    scanf("%c",&c);
    getchar();

    switch(c){
        case '1':
            cout << "Enter forest like this (a(e) b c), where a, b and c - main trees of forest"<<endl;
            p.readHList(p.list);
            break;
        case '2': p.readHListFile(p.list); break;
        default: cout<<"You haven't choose anything"<<endl; return 1;
    }
    //p.printHList(p.list);
    j = p.TreeFromForest(p.list);

    cout<<"Binary tree in direct order: ";
    j->printBtDirectOrder(j);
    cout<<'\n';

    cout<<"Binary tree representation in console:\n----------------------"<<endl;
    for(int i = 0; i< numberOfElements(j);i++){
        cout<<'\n';
    }
    displayBinaryTree(j);
    for(int i = 0; i< numberOfElements(j);i++){
        cout<<'\n';
    }
    cout<<"----------------------"<<endl;

    atLeastTwoEqualElements(j);
}
