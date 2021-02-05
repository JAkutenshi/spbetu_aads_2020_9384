#include "huffmantree.h"
#include "cmath"
#include <QDebug>
void HuffmanTree::buildHuffmanTree(std::string text, QtCharts::QScatterSeries *series1, QtCharts::QScatterSeries *series2,
                                   std::vector< std::pair <int,double> > &vect, std::vector< std::pair <int,double> > &vect2, std::vector<int> &unique){
    if (text == EMPTY_STRING) {
        return;
    }

    std::unordered_map<char, int> freq;
    for (char ch: text) {
        freq[ch]++;
    }

    unique.push_back(freq.size());

    std::priority_queue<Node*, std::vector<Node*>, comp> pq;

    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));

    }

    while (pq.size() != 1){
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        int sum = left->frequency + right->frequency;
        pq.push(getNode('\0', sum, left, right));

    }

    root = pq.top();

    auto start1 = std::chrono::steady_clock::now();
    encode(root,EMPTY_STRING);
    auto end1 = std::chrono::steady_clock::now();
    auto diff1 = end1 - start1;

    series1->append(text.size(), std::chrono::duration <double, std::nano> (diff1).count());
    vect.push_back(std::make_pair(text.size(),std::chrono::duration <double, std::nano> (diff1).count()));

    srand(time(NULL));
    std::string stringNew;
    for(int i = 0;i<huffmanCode.size();i++){
        auto it = huffmanCode.begin();
        std::advance(it, rand()% huffmanCode.size());
        stringNew+=huffmanCode[it->first];
    }

    auto start2 = std::chrono::steady_clock::now();
    int index = -1;
    while(index < (int)stringNew.size()-1){
        decode(root,index,stringNew);
    }
    auto end2 = std::chrono::steady_clock::now();
    auto diff2 = end2 - start2;
    series2->append(text.size(), std::chrono::duration <double, std::nano> (diff2).count());
    vect2.push_back(std::make_pair(text.size(),std::chrono::duration <double, std::nano> (diff2).count()));

    int bitsCount = 0;
    for (auto it = huffmanCode.begin(); it != huffmanCode.end(); ++it){
        bitsCount+=it->second.size();
    }

    qDebug()<<"number of bits for Huffman encode: "<<bitsCount<<'\n';
}

void HuffmanTree::encode(HuffmanTree::Node *root, std::string str) {
    if (root == nullptr) {
        return;
    }

    if (isLeaf(root)) {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }

    encode(root->left, str + "0");
    encode(root->right, str + "1");
}

HuffmanTree::Node *HuffmanTree::getNode(char ch, int freq, HuffmanTree::Node *left, HuffmanTree::Node *right) {
    Node* node = new Node();

    node->ch = ch;
    node->frequency = freq;
    node->left = left;
    node->right = right;

    return node;
}

bool HuffmanTree::isLeaf(HuffmanTree::Node *root) {
    return root->left == nullptr && root->right == nullptr;
}

void HuffmanTree::decode(HuffmanTree::Node *root, int &index, std::string str) {
    if(index == -1 && isLeaf(root)){
        index++;
        return;
    }
  
    if (root == nullptr) {
        return;
    }

    if (isLeaf(root)) {
        return;
    }

    index++;

    if (str[index] == '0') {
        decode(root->left, index, str);
    } else {
        decode(root->right, index, str);
    }
}

