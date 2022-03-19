#include "ngram.hpp"
#include <iostream>
#include <map>
#include <string>
#include <vector>

void ngram::dump_ngrams(std::vector<std::string> &v) {
    for (auto &i : v) {
        std::cout << i << "\n";
    }
}

void ngram::print_map() {
    auto it = mp.begin();
    for (int i = 0; it != mp.end(); it++, i++) { // выводим их
        std::cout << i << ") Ключ " << it->first << " ";
        std::cout << "[";
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
    std::vector<std::string> v = get_ngramms(word);
    for (auto &i : v) {
        mp[i].push_back(word);
    }
}
std::vector<std::string> ngram::get_ngramms(std::string word) {
    std::vector<std::string> ngramms;
    for (std::size_t i = 2; i < word.size(); i++) {
        ngramms.push_back(std::string(1, word[i - 2]) + word[i - 1] + word[i]);
    }
    return ngramms;
}

int main() {

    ngram ng;
    ng.set_ngramms("longitude");
    ng.set_ngramms("latitude");
    ng.print_map();
    // std::string word = get_word();
    return 0;
}