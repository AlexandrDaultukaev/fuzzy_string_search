#include "ngram/ngram.hpp"
//#include "ngram.hpp"
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

const std::size_t BUFSIZE = 50;

void Ngram::install_dict() {
    std::ifstream fin("words_alpha.txt");
    if (fin.fail()) {
        throw std::runtime_error("..");
        exit(EXIT_FAILURE);
    }
    std::string word;
    int i = 0;
    while (!fin.eof()) {
        getline(fin, word);
        set_ngramms(word);
        i++;
    }
    fin.close();
}

Ngram::Ngram(int set_empty_dict) {
    if (set_empty_dict == 0) {
        install_dict();
    }
}

void Ngram::dump_ngrams(std::vector<std::string> &v) {
    for (auto &i : v) {
        std::cout << i << "\n";
    }
}

void Ngram::print_map() {
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

void Ngram::set_ngramms(const std::string &word) {
    if (word.size() < 4) {
        return;
    }
    std::vector<std::string> v = get_ngramms(word);
    for (auto &i : v) {
        mp[i].push_back(word);
    }
}
std::vector<std::string> Ngram::get_ngramms(std::string word) {
    std::vector<std::string> ngramms;
    for (std::size_t i = 2; i < word.size(); i++) {
        ngramms.push_back(std::string(1, word[i - 2]) + word[i - 1] + word[i]);
    }
    return ngramms;
}

int Ngram::exists(std::string &key) {
    auto it = mp.begin();
    for (; it != mp.end(); it++) {
        if (it->first == key) {
            return 1;
        }
    }
    return 0;
}

std::vector<std::string> Ngram::search_ngram(std::string word) {
    std::vector<std::string> ngramms = get_ngramms(std::move(word));
    for (auto &i : ngramms) {
        // std::cout << "i)" << i << "\n";
        if (exists(i) != 0) {
            std::vector<std::string> v = mp[i];
            for (auto &j : v) {
                freq.increment(j);
            }
        }
    }
    std::vector<std::string> candidates = freq.get_best_candidates();
    // std::cout << candidates.size() << "\n";
    // for (auto &i : candidates) {
    //     std::cout << i << "\n";
    // }
    return candidates;
}

void WordFrequency::increment(const std::string &word) { ind[word]++; }
std::vector<std::string> WordFrequency::get_best_candidates() {
    std::vector<std::string> candidates;
    auto it = ind.begin();
    unsigned int max = 0;
    for (; it != ind.end(); it++) {
        if (it->second > max) {
            max = it->second;
        }
    }
    it = ind.begin();
    for (; it != ind.end(); it++) {
        if (it->second == max) {
            candidates.push_back(it->first);
        }
    }
    return candidates;
}