#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

struct s_expr
{
    bool isAtom;
    s_expr *ptr_next;
    union
    {
        char atom;
        s_expr *ptr_child;
    } node;
};

s_expr *CreateList(std::string &str, int &pos)
{
    s_expr *hd = nullptr;
    s_expr *tl = nullptr;
    s_expr *st = nullptr;
    do
    {
        if (str[pos] == '(')
        {
            st = new s_expr;
            if (!hd)
            {
                hd = st;
                tl = st;
            }
            else
            {
                tl->ptr_next = st;
                tl = st;
            }
            st->isAtom = false;
            st->ptr_next = nullptr;
            pos++;
            st->node.ptr_child = CreateList(str, pos);
        }
        else if (str[pos] == ')')
        {
            pos++;
            return hd;
        }
        else
        {
            if (!hd)
            {
                hd = new s_expr;
                hd->isAtom = true;
                hd->ptr_next = nullptr;
                hd->node.atom = str[pos];
                tl = hd;
                pos++;
            }
            else
            {
                st = new s_expr;
                tl->ptr_next = st;
                st->isAtom = true;
                st->ptr_next = nullptr;
                st->node.atom = str[pos];
                tl = st;
                pos++;
            }
        }
    } while (str[pos]);
    return hd;
}

void Depth(s_expr *pos, int count, int &answer)
{
    if (pos)
    {
        if (!pos->isAtom && pos->node.ptr_child)
        {
            count++;
            Depth(pos->node.ptr_child, count, answer);
        }
        if (pos->isAtom)
        {
            if (answer < count)
                answer = count;
        }
        if (!pos->isAtom && pos->node.ptr_child)
        {
            Depth(pos->ptr_next, --count, answer);
        }
        else
            Depth(pos->ptr_next, count, answer);
        return;
    }
    return;
}

// Очистка иерархического списка
void FreeList(s_expr *pos)
{
    if (pos)
    {
        if (!pos->isAtom)
            FreeList(pos->node.ptr_child);
        FreeList(pos->ptr_next);
        delete pos;
    }
}

bool CheckBrackets(const std::string str)
{
    string.erase(std::remove_if(string.begin(), string.end(), isspace), string.end());
    size_t open = std::count(str.begin(), str.end(), '(');
    size_t closed = std::count(str.begin(), str.end(), ')');
    if (open > closed)
    {
        std::cout << "Missing closed bracket" << std::endl;
        return false;
    }
    else if (closed > open)
    {
        std::cout << "Missing open bracket" << std::endl;
        return false;
    }
    return true;
}

char read_type()
{
    std::cout << "Введите 1 для считывания из файла\n\
 Введите 2 для считывания из консоли"
              << std::endl;
    char key = getchar();
    return key;
}

//Считывание с файла
void ReadF()
{
    std::ifstream in_file("input.txt");
    std::ofstream out_file("output.txt");
    std::string line;
    int i = 0;
    int line_number = 1;
    while (std::getline(in_file, line))
    {

        int count = 0, answer = 0;
        line.pop_back();
        out_file << line_number++ << ": ";
        if (!CheckBrackets(line))
            out_file << "Brackets error, check terminal for more information\n"
                     << std::endl;
        else
        {
            out_file << "Depth of ( " << line << " )";
            s_expr *head = CreateList(line, count);
            Depth(head, 0, answer);
            out_file << " is  " << answer << " \n"
                     << std::endl;
            FreeList(head);
        }
    }
}

// Считывание с консоли
void ReadT()
{
    std::string str;
    int count = 0, answer = 0;
    std::cout << "Введите значение" << std::endl;
    std::cin >> str;
    CheckBrackets(str);
    std::cout << "Depth of ( " << str << " )";
    s_expr *head = CreateList(str, count);
    Depth(head, 0, answer);
    std::cout << " is  " << answer << " " << std::endl;
    FreeList(head);
}

int main()
{
    switch (read_type())
    {
    case '1':
        ReadF();
        break;
    case '2':
        ReadT();
        break;
    default:
        std::cout << "Числа нет в списке команд" << std::endl;
        break;
    }
}