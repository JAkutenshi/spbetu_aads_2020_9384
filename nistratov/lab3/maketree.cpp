#include "maketree.h"
#include <iostream>
#include <string>

maketree::maketree()
{

}

BinaryTree<char> *maketree::createTree(std::string str)
{
    BinaryTree<char> *symb = new BinaryTree<char>();
    std::string str1 ="";
    std::string str2 = "";
    if (str[1] != '\0') {
       symb = new BinaryTree<char>(slit(str, str1, str2));
    }
    else {
        symb = new BinaryTree<char>(str[0]);
        symb->left = nullptr;
        symb->right = nullptr;
        return symb;
    }
    symb->left = createTree(str1);
    symb->right = createTree(str2);
    return symb;
}

char maketree::slit(std::string str, std::string &data1, std::string &data2)
{
    unsigned int ind_now = 0;
    bool open_bracket = false, symval = false;;
    for(unsigned int i = 0; i < str.length(); i++) {
        if (str[i] == '(')
            open_bracket = true;
        if (str[i] == ')')
            open_bracket = false;
        if (!open_bracket) {
            if (str[i] == '-' || str[i] == '+') {
                symval = true;
                ind_now = i;
            }
            if (str[i] == '*')
            {
                if (!symval){
                symval = true;
                ind_now = i;
                }
            }
        }
    }
    for(unsigned int i = 0; i < str.length(); i++) {
        if (i < ind_now)
            data1 += str[i];
        if (i > ind_now)
            data2 += str[i];
    }
    if (data1[0] == '(' && data1[data1.length()-1] == ')'){
        data1.erase(0,1);
        data1.erase(data1.length()-1);
    }
    if (data2[0] == '(' && data2[data2.length()-1] == ')'){
        data2.erase(0,1);
        data2.erase(data2.length()-1);
    }
    return str[ind_now];
}

void maketree::printTree(BinaryTree<char> *symb, std::string &output, int offset)
{
    if(symb != nullptr){
        printTree(symb->left, output, offset);
        printTree(symb->right, output, offset);
        output+= symb->data;
    }
}

void maketree::calcTree(BinaryTree<char> *tr)
{
    if(tr->left != nullptr && tr->right != nullptr)
    {

        if (tr->getData() == '-')
        {
            calcTree(tr->left);
            calcTree(tr->right);
            if (tr->left->getData() < '0' || tr->left->getData() > '9' || \
                tr->right->getData() < '0' || tr->right->getData() > '9') return;
            int k = tr->left->getData()-tr->right->getData();
            if (k < 0 )
            {
                tr->left->data = 0 + 48;
                tr->right->data = abs(k) + 48;
                return;
            }
            tr->data = k + 48;
            std::cout << (tr->left->getData()-tr->right->getData()) << std::endl;
            tr->left = nullptr;
            tr->right = nullptr;
            return;
        }
            calcTree(tr->left);
            calcTree(tr->right);
    }
}
