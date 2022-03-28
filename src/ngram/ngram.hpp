#pragma once

#include <map>
#include <string>
#include <vector>

struct WordFrequency {
    std::map<std::string, unsigned int> ind;
    void reset();
    void increment(const std::string &word);
    std::vector<std::string> get_best_candidates();
};

class Ngram {
    std::map<std::string, std::vector<std::string>> ngrams;
    WordFrequency freq;
    void install_dict(const char *path);
    static std::vector<std::string> get_ngramms(std::string word);

  public:
    Ngram(const char *path = "");
    static void dump_ngrams(std::vector<std::string> &v);
    void print_map();
    void set_ngramms(const std::string &word);
    int exists(std::string &key);
    std::vector<std::string> search_ngram(std::string word);
};

// class NgramSearcher {
//   Ngram* ng = nullptr;

//   NgramSearcher()
// };