#include "adaptive_encode.h"
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

