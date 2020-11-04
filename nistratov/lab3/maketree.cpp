#include "maketree.h"
#include <iostream>
#include <string>
#include <list>

BinaryTree<char> *createTree(std::string str)
{
    BinaryTree<char> *symb = new BinaryTree<char>();
    std::string str1 ="";
    std::string str2 = "";
    if (str[1] != '\0') {
       symb = new BinaryTree<char>(split(str, str1, str2));
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

char split(std::string str, std::string &left_data, std::string &right_data)
{
    unsigned int ind_now = 0;
    bool open_bracket = false, symval = false;;
    for(size_t i = 0; i < str.length(); i++) {
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
    for(size_t i = 0; i < str.length(); i++) {
        if (i < ind_now)
            left_data += str[i];
        if (i > ind_now)
            right_data += str[i];
    }
    if (left_data[0] == '(' && left_data[left_data.length()-1] == ')'){
        left_data.erase(0,1);
        left_data.erase(left_data.length()-1);
    }
    if (right_data[0] == '(' && right_data[right_data.length()-1] == ')'){
        right_data.erase(0,1);
        right_data.erase(right_data.length()-1);
    }
    return str[ind_now];
}

void printTree(BinaryTree<char> *symb, std::string &output, int offset)
{
    if(symb != nullptr){
        printTree(symb->left, output, offset);
        printTree(symb->right, output, offset);
        output+= symb->data;
    }
}

void calcTree(BinaryTree<char> *tr)
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
            tr->left = nullptr;
            tr->right = nullptr;
            return;
        }
            calcTree(tr->left);
            calcTree(tr->right);
    }
}

std::string createLRC(std::string str)
{
  std::string temp = "";
  std::stack<char> h1;
  char c;
  std::list<std::string> stack;
  for (size_t i = 0; i < str.length(); i++)
  {
      c = str[i];
      if (c == '+' || c == '-' || c == '*'){
          if (stack.size() < 2)
              throw "Wrong formula";
          std::string b = stack.back();
          stack.pop_back();
          std::string a = stack.back();
          stack.pop_back();
          stack.push_back( std::string("(") + a + c + b + ")");
      }
      else if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))
      {
        stack.push_back(std::string("") + c);
      }
      else
          throw "Wrong symbols";
  }
  temp +=  *stack.rbegin();
  std::cout << temp << std::endl;
  return temp;
}

void stringchecker(std::string &str)
{
    if (str.length() == 1) return;
    if (str[0] == '(' && str[str.size()-1] == ')')
    {
        str.erase(0,1);
        str.erase(str.size()-1);
    }
    else
        throw "No brackets";
    size_t open = std::count(str.begin(), str.end(), '(');
    size_t closed = std::count(str.begin(), str.end(), ')');
    if (open != closed)
        throw "Missing brackets";
    std::string symb = "qwertyuiopasdfghjklzxcvbnm123456789";
    for (size_t i = 0; i < str.length()-1; i++)
    {
        if ((symb.find(str[i]) != std::string::npos) && (symb.find(str[i+1]) != std::string::npos))
            throw "Wrong formula";
    }
}
