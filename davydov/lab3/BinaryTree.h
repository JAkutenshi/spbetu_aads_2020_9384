#ifndef TREETEST_BINARYTREE_H
#define TREETEST_BINARYTREE_H
#include <iostream>
#include <fstream>

using namespace std;
template <class T>
class BinaryTree {
public:
    T rootData;
    BinaryTree *leftSubTree;
    BinaryTree *rightSubTree;
    T character = '\0';

    struct S_expr;
    struct  two_ptr
    {
        S_expr *hd;
        S_expr *tl;
    } ;

    struct S_expr {
        bool tag;
        union
        {
            T atom;
            two_ptr pair;
        } node;
    };

    typedef S_expr *Hlist;

    Hlist list;

    BinaryTree(T rootData = NULL, BinaryTree *leftSubTree = nullptr, BinaryTree *rightSubTree = nullptr) {
        this->rootData = rootData;
        this->leftSubTree = leftSubTree;
        this->rightSubTree = rightSubTree;
    }

    //////////////methods binary tree//////////////

    bool isNull(BinaryTree *tree){
        return tree == nullptr;
    }

    Hlist nextTreeMain(Hlist tree){
        if(isNull(tree)) return nullptr;
        if(isAtom(head(tree))) return tree;
        else return nextTreeMain(tail(tree));
    }

    Hlist nextTreeSub(Hlist tree){
        if(isNull(tree)) return nullptr;
        if(isAtom(head(tree))) return nullptr;
        else return tree;
    }

    Hlist isNextAtom(Hlist tree){
        if (!isNull(tree)){
            if (isAtom(head(tree))){
                return nullptr;
            } else return tree;
        } else return nullptr;
    }

    BinaryTree<char>* TreeFromForest(Hlist forest){
        if(isNull(forest)) return nullptr;
        if(isAtom(head(forest))) {
            return new BinaryTree<char>(
                    getAtom(head(forest)),
                    TreeFromForest(isNextAtom(tail(forest))),
                    TreeFromForest(nextTreeMain(tail(forest))));
        } else {
            if(isNull(head(forest))) {
                error(10);
                exit(0);
            }
            else {
                return new BinaryTree<char>(
                        getAtom(head(head(forest))),
                        TreeFromForest(tail(head(forest))),
                        TreeFromForest(nextTreeSub(tail(forest))));
            }
        }
    }

    void printBtDirectOrder(BinaryTree *tree){
        if(isNull(tree)){
            cout<<'^';
        }
        else{
            cout << '(';
            cout<<tree->rootData << ' ';
            printBtDirectOrder(tree->leftSubTree);
            printBtDirectOrder(tree->rightSubTree);
            cout << ')';
        }
    }

    ////////////methods hierarchical list////////////
    Hlist head(const Hlist s) {
        if (s != nullptr)
            if (!isAtom(s)) return s->node.pair.hd;
            else {
                error(1);
                exit(0);
            }
        else {
            error(2);
            exit(0);
        }
    }

    bool isAtom(const Hlist s) {
        if (s == nullptr) return false;
        else return (s->tag);
    }

    bool isNull(const Hlist s) {
        return s == nullptr;
    }

    Hlist tail(const Hlist s) {
        if (s != nullptr)
            if (!isAtom(s)) return s->node.pair.tl;
            else {
                error(3);
                exit(0);
            }
        else {
            error(4);
            exit(0);
        }
    }

    Hlist cons(const Hlist h, const Hlist t) {
        Hlist p;
        if (isAtom(t)) {
            error(5);
            exit(0);
        } else {
                p = new S_expr;
                p->tag = false;
                p->node.pair.hd = h;
                p->node.pair.tl = t;
                return p;
            }
        }


    Hlist makeAtom(const T x) {
        Hlist s;
        s = new S_expr;
        s->tag = true;
        s->node.atom = x;
        return s;
    }

    void destroy(Hlist s) {
        if (s != nullptr) {
            if (!isAtom(s)) {
                destroy(head(s));
                destroy(tail(s));
            }
            delete s;
        }
    }

    T getAtom(const Hlist s) {
        if (!isAtom(s)) {
            error(6);
            exit(0);
        } else return (s->node.atom);
    }


    void readHList (Hlist& y) {
        do character = getchar(); while (character == ' ');
        readS_expr(character,y);
    }

    void readS_expr(T prev, Hlist &y) {
        if (prev == ')') {
            error(7);
            exit(0);
        } else if (prev != '(') y = makeAtom(prev);
        else {readSeq(y);}
    }

    void readSeq(Hlist &y) {
        Hlist p1, p2;
        if (!(character = getchar())) {
            error(8);
            exit(0);
        } else {
            while (character == ' ') character = getchar();
            if (character == ')') y = nullptr;
            else {
                readS_expr(character, p1);
                readSeq(p2);
                y = cons(p1, p2);
            }
        }
    }

    void readHListFile(Hlist &y) {
        std::string filePathIn;
        std::cout << "Enter input file:\n";
        std::cin >> filePathIn;
        std::ifstream in;
        in.open(filePathIn);
        if (!in.is_open()) {
            error(9);
            exit(0);
        }
        T x;
        do in >> x; while (x == ' ');
        readS_exprFile(x, y, in);
    }

    void readS_exprFile(T prev, Hlist &y, ifstream &infile) {
        if (prev == ')') {
            error(7);
            exit(0);
        } else if (prev != '(') y = makeAtom(prev);
        else readSeqFile(y, infile);
    }

    void readSeqFile(Hlist &y, ifstream &infile) {
        T x;
        Hlist p1, p2;

        if (!(infile >> x)) {
            error(8);
            exit(0);
        } else {
            while (x == ' ') infile >> x;
            if (x == ')') y = nullptr;
            else {
                readS_exprFile(x, p1, infile);
                readSeqFile(p2, infile);
                y = cons(p1, p2);
            }
        }
    }

    void printHList(const Hlist x) {
        if (isNull(x)) cout << " ()";
        else if (isAtom(x)) cout << ' ' << x->node.atom;
        else {
            cout << " (";
            printSeq(x);
            cout << " )";
        }
    }

    void printSeq(const Hlist x) {
        if (!isNull(x)) {
            printHList(head(x));
            printSeq(tail(x));
        }
    }


    //////////// errors ////////////

    void error(unsigned int number){
        switch(number){
            case 1: cout << "Error: Head(atom) \n"<< endl; break;
            case 2: cout << "Error: Head(nil) \n"<< endl; break;
            case 3: cout << "Error: Tail(atom) \n"<< endl; break;
            case 4: cout << "Error: Tail(nil) \n"<< endl; break;
            case 5: cout << "Error: Cons(*, atom)\n"<< endl; break;
            case 6: cout << "Error: getAtom(s) for !isAtom(s) \n"<< endl; break;
            case 7: cout << "Error: a character \")\" was entered first into terminal" << endl; break;
            case 8: cout << "Error: a character \"(\" was entered and nothing after it"<<endl; break;
            case 9: cout << "Error: There is no such file" << endl; break;
            case 10: cout << "Error: you can't create new tree from emtpy list"<<endl;break;
            default: exit(0);
        }
    }
};
#endif
