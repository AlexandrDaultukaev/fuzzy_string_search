#include "ngram/ngram.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const std::size_t BUFSIZE = 50;

void ngram::install_dict() {
    std::ifstream fin("words_alpha.txt");
    std::string sbuf;
    char cbuf[BUFSIZE]; // NOLINT
    int i = 0;
    // while (i < 20) {
    fin.getline(cbuf, BUFSIZE); // NOLINT
    std::string word(cbuf); // NOLINT
    set_ngramms(word);
    i++;
    //}
    fin.close();
}

void ngram::dump_ngrams(std::vector<std::string> &v) {
    for (auto &i : v) {
        std::cout << i << "\n";
    }
}

void ngram::print_map() {
    auto it = mp.begin();
    for (int i = 0; it != mp.end(); it++, i++) { // выводим их
        std::cout << i << ")"
                  << " Key " << it->first << " [";
        for (std::size_t i = 0; i < mp[it->first].size(); i++) {
            std::cout << it->second[i] << " ";
        }
        std::cout << "]\n";
    }
}

// void ngram::sort_ngrams()
// {
//     size_t max = -1;
//             std::map<std::string,
//             std::vector<std::string>>:: iterator it
//             = mp.begin();
//     for (int i = 0; it != mp.end(); it++, i++) {  //
//     выводим их
//         if(mp[it->first] > max)
//             max = mp[it->first];
//     }
// }

void ngram::set_ngramms(const std::string &word) {
    if (word.size() < 4) {
        return;
    }
    std::vector<std::string> v = get_ngramms(word);
    for (auto &i : v) {
        mp[i].push_back(word);
    }
}
std::vector<std::string> ngram::get_ngramms(std::string word) {
    std::vector<std::string> ngramms;
    for (std::size_t i = 2; i < word.size() - 1; i++) {
        ngramms.push_back(std::string(1, word[i - 2]) + word[i - 1] + word[i]);
    }
    return ngramms;
}

int ngram::is_exists(std::string &key) {
    auto it = mp.begin();
    for (int i = 0; it != mp.end(); it++, i++) { // выводим их
        if (it->first == key) {
            return 1;
        }
    }
    return 0;
}

// int main() {

//     ngram ng;
//     ng.set_ngramms("longitude");
//     ng.set_ngramms("latitude");
//     ng.print_map();
//     // std::string word = get_word();
//     return 0;
// }