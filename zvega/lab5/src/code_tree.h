#ifndef CODE_TREE_H
#define CODE_TREE_H
#define MAX_CODE_LEN 1000

struct Symbol {
	char c;
	int weight;
};
bool symbol_less(const Symbol & l, const Symbol & r);
bool symbol_greater(const Symbol& l, const Symbol& r);

struct CodeTree {
	Symbol s;
	CodeTree* parent;
	CodeTree* left;
	CodeTree* right;
};

CodeTree* make_leaf(const Symbol& s);
CodeTree* make_node(int weight, CodeTree* left, CodeTree* right);
bool is_leaf(const CodeTree* node);
bool is_root(const CodeTree* node);
char* encode(const CodeTree* tree, const char* message);
void destroy(CodeTree* tree);
#endif // CODE_TREE_H