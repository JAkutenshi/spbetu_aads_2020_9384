#include "hierarchical_list.h"

using namespace std;

namespace H_list {

    Lisp head(const Lisp s) {// PreCondition: not null (s)
        if (s != nullptr)
            if (!isAtom(s)) return s->node.pair.hd;
            else {
                cerr << "Error: Head(atom) \n";
                exit(1);
            }
        else {
            cerr << "Error: Head(nil) \n";
            exit(1);
        }
    }

    bool isAtom(const Lisp s) {
        if (s == nullptr) return false;
        else return (s->tag);
    }

    bool isNull(const Lisp s) {
        return s == nullptr;
    }

    Lisp tail(const Lisp s) {
        // PreCondition: not null (s)
        if (s != nullptr)
            if (!isAtom(s)) return s->node.pair.tl;
            else {
                cerr << "Error: Tail(atom) \n";
                exit(1);
            }
        else {
            cerr << "Error: Tail(nil) \n";
            exit(1);
        }
    }

    Lisp cons(const Lisp h, const Lisp t) {
        // PreCondition: not isAtom (t)
        Lisp p;
        if (isAtom(t)) {
            cerr << "Error: Cons(*, atom)\n";
            exit(1);
        } else {
            p = new S_expr;
            if (p == nullptr) {
                cerr << "Memory not enough\n";
                exit(1);
            } else {
                p->tag = false;
                p->node.pair.hd = h;
                p->node.pair.tl = t;
                return p;
            }
        }
    }

    Lisp makeAtom(const Base x) {
        Lisp s;
        s = new S_expr;
        s->tag = true;
        s->node.atom = x;
        return s;
    }

    void destroy(Lisp s) {
        if (s != nullptr) {
            if (!isAtom(s)) {
                destroy(head(s));
                destroy(tail(s));
            }
            delete s;
            // s = NULL;
        };
    }

    Base getAtom(const Lisp s) {
        if (!isAtom(s)) {
            cerr << "Error: getAtom(s) for !isAtom(s) \n";
            exit(1);
        } else return (s->node.atom);
    }


    // ввод списка с консоли
    void readLisp(Lisp &y) {
        cout << "Enter your List" << endl;
        Base x;
        do cin >> x; while (x == ' ');
        readS_expr(x, y);
    }

    void readS_expr(Base prev, Lisp &y) {
        //prev - ранее прочитанный символ
        if (prev == ')') {
            cerr << " ! List.Error 1 " << endl;
            exit(1);
        } else if (prev != '(') y = makeAtom(prev);
        else readSeq(y);
    }

    void readSeq(Lisp &y) {
        Base x;
        Lisp p1, p2;

        if (!(cin >> x)) {
            cerr << " ! List.Error 2 " << endl;
            exit(1);
        } else {
            while (x == ' ') cin >> x;
            if (x == ')') y = nullptr;
            else {
                readS_expr(x, p1);
                readSeq(p2);
                y = cons(p1, p2);
            }
        }
    }

    // процедура вывода списка с обрамляющими его скобками - printLisp,
    //  а без обрамляющих скобок - printSeq
    void printLisp(const Lisp x) {
        //пустой список выводитс¤ как ()
        if (isNull(x)) cout << " ()";
        else if (isAtom(x)) cout << ' ' << x->node.atom;
        else { //непустой список
            cout << " (";
            printSeq(x);
            cout << " )";
        }
    }

    void printSeq(const Lisp x) {
        //выводит последовательность элементов списка без обрамляющих его скобок
        if (!isNull(x)) {
            printLisp(head(x));
            printSeq(tail(x));
        }
    }

    Lisp copyLisp(const Lisp x) {
        if (isNull(x)) return nullptr;
        else if (isAtom(x)) return makeAtom(x->node.atom);
        else return cons(copyLisp(head(x)), copyLisp(tail(x)));
    }

    Lisp concat(const Lisp y, const Lisp z) {
        if (isNull(y)) return copyLisp(z);
        else return cons(copyLisp(head(y)), concat(tail(y), z));
    }

    void readLispFile(Lisp &y) {
        std::string filePathIn;
        std::cout << "Enter input file:\n";
        std::cin >> filePathIn;
        std::ifstream in;
        in.open(filePathIn);
        if (!in.is_open()) {
            cout << "There is no such file" << endl;
            exit(0);
        }
        Base x;
        do in >> x; while (x == ' ');
        readS_exprFile(x, y, in);
    }

    void readS_exprFile(Base prev, Lisp &y, ifstream &infile) {
        //prev - ранее прочитанный символ
        if (prev == ')') {
            cerr << " ! List.Error 1 " << endl;
            exit(1);
        } else if (prev != '(') y = makeAtom(prev);
        else readSeqFile(y, infile);
    }

    void readSeqFile(Lisp &y, ifstream &infile) {
        Base x;
        Lisp p1, p2;

        if (!(infile >> x)) {
            cerr << " ! List.Error 2 " << endl;
            exit(2);
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
}
