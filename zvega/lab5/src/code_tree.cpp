#include "code_tree.h"
#include "iostream"
#include <climits>
#include <cstring>
#include <string>


bool symbol_less(const Symbol& l, const Symbol& r){
	return l.weight < r.weight;
}


bool symbol_greater(const Symbol& l, const Symbol& r){
	return l.weight > r.weight;
}


CodeTree* make_leaf(const Symbol& s){
	return new CodeTree{ s, nullptr, nullptr, nullptr };
}


CodeTree* make_node(int weight, CodeTree* left, CodeTree* right){
	Symbol s{ 0, weight };
	return new CodeTree{ s, nullptr, left, right };
}


bool is_leaf(const CodeTree* node){
	return node->left == nullptr && node->right == nullptr;
}


bool is_root(const CodeTree* node){
	return node->parent == nullptr;
}


void fill_symbols_map(const CodeTree* node, const CodeTree** symbols_map){
	if (is_leaf(node))
		symbols_map[node->s.c - CHAR_MIN] = node;
	else {
		fill_symbols_map(node->left, symbols_map);
		fill_symbols_map(node->right, symbols_map);
	}
}


char* encode(const CodeTree* tree, const char* message){
	char* code = new char[MAX_CODE_LEN];
	const CodeTree** symbols_map = new const CodeTree * [UCHAR_MAX];
	for (int i = 0; i < UCHAR_MAX; ++i) {
		symbols_map[i] = nullptr;
	}
	fill_symbols_map(tree, symbols_map);
	int len = strlen(message);
	int index = 0;
	char path[UCHAR_MAX];
	std::string check;
	for (int i = 0; i < len; ++i) {
		const CodeTree* node = symbols_map[message[i] - CHAR_MIN];
		int j = 0;
		while (!is_root(node)) {
			if (node->parent->left == node)
				path[j++] = '0';
			else
				path[j++] = '1';
			node = node->parent;
		}
		path[j] = '\0';		
		while (j > 0) {
			code[index++] = path[--j];
			if (-1 == check.find(symbols_map[message[i] - CHAR_MIN]->s.c))
				std::cout << path[j];
		}
		if (-1 == check.find(symbols_map[message[i] - CHAR_MIN]->s.c)) {
			check.push_back(symbols_map[message[i] - CHAR_MIN]->s.c);
			std::cout << " - " << symbols_map[message[i] - CHAR_MIN]->s.c << std::endl;
		}
	}
	code[index] = 0;
	delete[] symbols_map;
	return code;
}


void destroy(CodeTree* tree){
	if (tree == nullptr) return;
	destroy(tree->left);
	destroy(tree->right);
	delete tree;
	tree = nullptr;
}
