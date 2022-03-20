#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

struct idx {
    std::map<std::string, unsigned int> ind;

    void increment(const std::string &word);
    std::vector<std::string> get_best_candidates();
};

class ngram {
    std::map<std::string, std::vector<std::string>> mp;
    idx ind;
    void install_dict();

  public:
    ngram(int set_empty_dict = 0);
    static void dump_ngrams(std::vector<std::string> &v);
    void print_map();
    void set_ngramms(const std::string &word);
    static std::vector<std::string> get_ngramms(std::string word);
    int is_exists(std::string &key);
    std::vector<std::string> search_ngram(std::string word);
};