#include "shannoncode.h"
#include <QDebug>

void ShannonCode::encodeDecode(std::string text, QtCharts::QScatterSeries *series1, QtCharts::QScatterSeries *series2, std::vector<std::pair <int,double> > &vect,
                         std::vector< std::pair <int,double> > &vect2){
    if (text == EMPTY_STRING) {
        return;
    }

    std::map<char,int> freq;

    for (char ch: text) {
        freq[ch]++;
    }

    auto start = std::chrono::steady_clock::now();
    buildFunc(freq,EMPTY_STRING, text.size());
    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    series1->append(text.size(),std::chrono::duration <double, std::nano> (diff).count());
    vect.push_back(std::make_pair(text.size(),std::chrono::duration <double, std::nano> (diff).count()));

    srand(time(NULL));
    std::string stringNew;
    for(int i = 0;i<int(shannon_code1.size());i++){
        auto it = shannon_code1.begin();
        std::advance(it, rand()% shannon_code1.size());
        stringNew+=shannon_code1[it->first];
    }

    auto start2 = std::chrono::steady_clock::now();
    decode(stringNew);
    auto end2 = std::chrono::steady_clock::now();
    auto diff2 = end2 - start2;
    series2->append(text.size(),std::chrono::duration <double, std::nano> (diff2).count());
    vect2.push_back(std::make_pair(text.size(),std::chrono::duration <double, std::nano> (diff2).count()));

    int bitsCount = 0;
    for (auto it = shannon_code1.begin(); it != shannon_code1.end(); ++it){
        bitsCount+=it->first.size();
    }

    qDebug()<<"number of bits for Shanon encodeDecode: "<<bitsCount<<'\n';
}

void ShannonCode::buildFunc(const std::map<char, int> map1, std::string code, int W2) {
    if(map1.size() == 2){
        if(map1.begin()->second > map1.rbegin()->second){
            shannon_code1[code + '0'] = map1.begin()->first;
            shannon_code1[code + '1'] = map1.rbegin()->first;
        } else{
            shannon_code1[code + '1'] = map1.begin()->first;
            shannon_code1[code + '0'] = map1.rbegin()->first;
        }
        return;
    }

    if(map1.size() == 1) shannon_code1[code + '1'] = map1.rbegin()->first;

    int W = W2 / 2;
    int K[map1.size() + 1][W + 1];
    for (int i = 0; i < W + 1; i++) {
        K[0][i] = 0;
    }
    int i = 1;
    for (auto it = map1.begin(); it != map1.end(); ++it, i++) {
        for (int w = 0; w <= W; w++) {
            if (it->second <= w) {
                K[i][w] = std::max(it->second +
                              K[i - 1][w - it->second], K[i - 1][w]);
            } else {
                K[i][w] = K[i - 1][w];
            }
        }
    }

    int res = K[map1.size()][W];
    int res1 = res;
    int w = W;
    i = map1.size();

    std::map<char, int> map2;
    std::map<char, int> map3 = map1;

    for (auto it = map1.rbegin(); it != map1.rend() && res > 0; ++it, i--) {
        if (res == K[i - 1][w]) {
            continue;
        } else {
            res = res - it->second;
            w = w - it->second;
            map2.insert(std::pair<char, int>(it->first, it->second));
            map3.erase(it->first);
        }
    }

    if (map2.size() == 1 && map3.size() != 1) {
        shannon_code1[code + '1'] = map2.begin()->first;
        buildFunc(map3, code + '0', W2 - res1);
        return;
    } else if (map3.size() == 1 && map2.size() != 1) {
        shannon_code1[code + '0'] = map3.begin()->first;
        buildFunc(map2, code + '1', res1);
        return;
    } else if (map2.size() == 1 && map3.size() == 1) {
        shannon_code1[code + '1'] =  map2.begin()->first;
        shannon_code1[code + '0'] =  map3.begin()->first;
        return;
    } else {
        buildFunc(map2, code + '1', res1);
        buildFunc(map3, code + '0', W2 - res1);
    }
}

void ShannonCode::decode(std::string text){
    std::string text2;
    std::string text3;
    std::map<std::string, char>::iterator it;
    for(int i = 0;i<int(text.size());i++){
        text2.push_back(text[i]);
        it = shannon_code1.find(text2);
        if(it != shannon_code1.end()){
            text3.push_back(shannon_code1[text2]);
            text2 = "";
        }
    }
}


