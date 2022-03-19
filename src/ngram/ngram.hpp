#include <iostream>
#include <map>
#include <string>
#include <vector>

class ngram {
    std::map<std::string, std::vector<std::string>> mp;

  public:
    static void dump_ngrams(std::vector<std::string> &v);
    void print_map();
    void set_ngramms(const std::string &word);
    static std::vector<std::string> get_ngramms(std::string word);
};