#include "ngram/ngram.hpp"
//#include "ngram.hpp"
#include <array>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

NgramSearcher::NgramSearcher(NgramBuilder *new_builder) : ngram_builder(new_builder){}

std::vector<std::string> NgramSearcher::get_best_match(std::string word) {
    std::vector<std::string> result;
    ngram_builder->search_best_ngram(std::move(word));
    result = ngram_builder->get_best_candidates();
    ngram_builder->reset_candidates();
    return result;
}

void NgramSearcher::change_ngram_builder(NgramBuilder *new_builder) {
    ngram_builder = new_builder;
}

void NgramBuilder::install_dict(const char *path) {
    std::ifstream fin(path);
    if (fin.fail()) {
        throw std::runtime_error("..");
        exit(EXIT_FAILURE);
    }
    std::string word;
    while (!fin.eof()) {
        getline(fin, word);
        set_ngramms(word);
    }
    fin.close();
}

NgramBuilder::NgramBuilder(const char *path) {
    if (strlen(path) != 0) {
        install_dict(path);
    }
}

void NgramBuilder::dump_ngrams(std::vector<std::string> &v) {
    for (auto &i : v) {
        std::cout << i << "\n";
    }
}

void NgramBuilder::print_map() {
    auto it = ngrams.begin();
    for (int i = 0; it != ngrams.end(); it++, i++) { // выводим их
        std::cout << i << ")"
                  << " Key " << it->first << " [";
        for (std::size_t i = 0; i < ngrams[it->first].size(); i++) {
            std::cout << it->second[i] << " ";
        }
        std::cout << "]\n";
    }
}

void NgramBuilder::set_ngramms(const std::string &word) {
    if (word.size() < 4) {
        return;
    }
    std::vector<std::string> v = get_ngramms(word);
    for (auto &i : v) {
        ngrams[i].push_back(word);
    }
}
std::vector<std::string> NgramBuilder::get_ngramms(std::string word) {
    std::vector<std::string> ngramms;
    for (std::size_t i = 2; i < word.size(); i++) {
        ngramms.push_back(std::string(1, word[i - 2]) + word[i - 1] + word[i]);
    }
    return ngramms;
}

int NgramBuilder::exists(std::string &key) {
    auto it = ngrams.begin();
    for (; it != ngrams.end(); it++) {
        if (it->first == key) {
            return 1;
        }
    }
    return 0;
}

void NgramBuilder::search_best_ngram(std::string word) {
    std::vector<std::string> ngramms = get_ngramms(std::move(word));
    for (auto &i : ngramms) {
        if (exists(i) != 0) {
            std::vector<std::string> v = ngrams[i];
            for (auto &j : v) {
                freq.increment(j);
            }
        }
    }
}

std::vector<std::string> NgramBuilder::get_best_candidates() {
    std::vector<std::string> candidates = freq.get_best_candidates();
    return candidates;
}

void NgramBuilder::reset_candidates() {
    freq.reset();
}

void WordFrequency::increment(const std::string &word) { ind[word]++; }
void WordFrequency::reset() { ind.clear(); }
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