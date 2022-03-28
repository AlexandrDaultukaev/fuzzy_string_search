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

class NgramBuilder {
    std::map<std::string, std::vector<std::string>> ngrams;
    WordFrequency freq;
    void install_dict(const char *path);
    static std::vector<std::string> get_ngramms(std::string word);

  public:
    NgramBuilder(const char *path = "");
    static void dump_ngrams(std::vector<std::string> &v);
    void print_map();
    void set_ngramms(const std::string &word);
    int exists(std::string &key);
    void search_best_ngram(std::string word);
    std::vector<std::string> get_best_candidates();
};

class NgramSearcher {
  NgramBuilder* ngram_builder = nullptr;
public:
  NgramSearcher(NgramBuilder* new_builder)
  {
    ngram_builder = new_builder;
  }

  std::vector<std::string> get_best_match(std::string word)
  {
    std::vector<std::string> result;
    ngram_builder->search_best_ngram(word);
    result = ngram_builder->get_best_candidates();
    return result;
  }

  void change_ngram_builder(NgramBuilder* new_builder)
  {
    ngram_builder = new_builder;
  }



};