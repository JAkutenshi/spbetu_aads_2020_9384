#include "priority_queue.h"
#include "code_tree.h"
#include <functional>
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

CodeTree* haffman(const Symbol* symbols, int len)
{
	PriorityQueue<CodeTree*>* queue = create_pq<CodeTree*>(len);
	for (int i = 0; i < len; ++i)
		push(queue, symbols[i].weight, make_leaf(symbols[i]));
	while (size(queue) > 1) {
		CodeTree* ltree = pop(queue);
		CodeTree* rtree = pop(queue);
		int weight = ltree->s.weight + rtree->s.weight;
		CodeTree* node = make_node(weight, ltree, rtree);
		ltree->parent = node;
		rtree->parent = node;
		push(queue, weight, node);
	}
	CodeTree* result = pop(queue);
	destroy_pq(queue);
	return result;
}

CodeTree* haffman(const char* message) {
	Symbol symbols[UCHAR_MAX];
	for (int i = 0; i < UCHAR_MAX; ++i) {
		symbols[i].c = i + CHAR_MIN;
		symbols[i].weight = 0;
	}
	int size = strlen(message);
	for (int i = 0; i < size; ++i)
		symbols[message[i] - CHAR_MIN].weight++;
	std::sort(symbols, symbols + UCHAR_MAX, symbol_greater);
	int len = 0;
	while (symbols[len].weight > 0 && len < UCHAR_MAX) len++;
	return haffman(symbols, len);
}

char* decode(const CodeTree* tree, const char* code) {
	char* message = new char[MAX_CODE_LEN];
	int index = 0;
	int len = strlen(code);
	const CodeTree* v = tree;
	for (int i = 0; i < len; ++i) {
		if (code[i] == '0')
			v = v->left;
		else
			v = v->right;
		if (is_leaf(v)) {
			message[index++] = v->s.c;
			v = tree;
		}
	}
	message[index] = '\0';
	return message;
}

int main()
{
    string text;
	cout << "Input from file 1.\nInput from console 2.\n";
	int x;
	cin >> x;
	if (x == 1) {
		fstream file;
		cin >> text;
		file.open(text);
		if (!file) {
			cout << "File not open" << endl;
			return 1;
		}
		text.clear();
		file >> text;
		file.close();
	}
	else if (x == 2) {
		cin >> text;
	}
	else {
		cout << "Error input" << endl;
		return 1;
	}
    CodeTree* tree = haffman(text.c_str());
    
    char* code = encode(tree, text.c_str());
    cout << code << endl;

    cout << decode(tree, code) << endl;
    destroy(tree);

    return 0;
}

