namespace h_list{
    typedef char base;

    struct exp;
    struct ptrs{
        exp *head;
        exp *tail;
    };
    struct exp{
        bool tag;
        union{
            base atom;
            ptrs pair;
        }node;
    };

    typedef exp *list;

    list head(const list s);
    list tail(const list s);
    list cons(const list h, const list t);
    list makeAtom(const base x);
    bool isAtom(const list s);
    bool isNull(const list s);
    void destroy(list s);

    void read_list(list& y);
    void read_exp(base prev, list& y);
    void read_seq(list& y);
    void write_list(const list x);
    void write_seq(const list x);
    
    void error_type(int err);
}
