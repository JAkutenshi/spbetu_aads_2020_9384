#include <string>
#include <fstream>
#include <algorithm>
#include "BinaryTree.h"

using namespace std;

BinaryTree<char> *genNode(const string &, unsigned int = 1);
bool isThereRightNode(const string &, unsigned int &);
unsigned int treeDepth(BinaryTree<char> *);
unsigned int treeLenght(BinaryTree<char> *, unsigned int = 0);
void printResult(string);

int main(){
    string inputType;
    cout << "Type Console to write binary tree in console or File to read binary tree from document: ";
    cin >> inputType;
    if(inputType == "Console"){
        cout << "Type binary tree: ";
        string temp;
        cin >> temp;
        printResult(temp);
    }
    else if(inputType == "File"){
        cout << "Type binary tree document path: ";
        string temp;
        cin >> temp;
        ifstream inputFile(temp);
        if(inputFile.is_open()){
            while(getline(inputFile, temp))
                printResult(temp);
            inputFile.close();
        }
        else{
            cout << "FILE NOT OPEN" << endl;
            return -1;
        }
    }
    else{
        cout << "BAD INPUT CONFIGURATION" << endl;
        return -1;
    }
}

BinaryTree<char> *genNode(const string &string, unsigned int index){
    BinaryTree<char> *leftNode = nullptr, *rightNode = nullptr;

    if (string[index] == ')')
        return nullptr;

    if (string[index + 1] == '(')
        leftNode = genNode(string, index + 2);

    unsigned int temp = index + 1;
    if (isThereRightNode(string, temp))
        rightNode = genNode(string, temp);

    return new BinaryTree<char>(string[index], leftNode, rightNode);
}

bool isThereRightNode(const string &string, unsigned int &index){
    unsigned int countBracket = 0;

    if (string[index] == '/'){
        index += 2;
        return true;
    }
    else if (string[index] == ')')
        return false;

    do{
        if (string[index] == '(')
            countBracket++;
        else if (string[index] == ')')
            countBracket--;
        index++;
    }while (countBracket > 0);

    if (string[index] == '('){
        index++;
        return true;
    }
    return false;
}

unsigned int treeDepth(BinaryTree<char> *tree){
    if (tree->isNullBinaryTree())
        return 0;
    else
        return max(treeDepth(tree->getLeftNode()), treeDepth(tree->getRirghtNode())) + 1;
}

unsigned int treeLenght(BinaryTree<char> *tree, unsigned int depth){
    if(tree->isNullBinaryTree() || !tree->isNode())
        return 0;
    else
        return depth++ + treeLenght(tree->getLeftNode(), depth) + treeLenght(tree->getRirghtNode(), depth);
}

void printResult(string BT){
    BinaryTree<char> *tree = genNode(BT);
    if(!tree->isNullBinaryTree()){
        // tree->printBinaryTree();
        cout << "Max depth = " << treeDepth(tree) << " Lenght = " << treeLenght(tree) <<endl;
    }
    else
        cout << "NULL" << endl;
}