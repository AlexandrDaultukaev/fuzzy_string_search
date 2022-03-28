#include "ngram/ngram.hpp"
#include <gtest/gtest.h>
#include <map>
#include <string>
#include <vector>

TEST(NgramSuite, Test1) {
    NgramBuilder ng;
    ng.set_ngramms("longitude");
    std::string str = "git";
    EXPECT_EQ(ng.exists(str), true);
}

TEST(NgramSuite, Test2) {
    NgramBuilder ng("words_alpha.txt");
    NgramSearcher ns(&ng);
    std::vector<std::string> word = ns.get_best_match("ltitde");
    EXPECT_EQ(std::vector<std::string>({"multititular"}), word);
}

TEST(NgramSuite, Test3) {
    NgramBuilder ng("words_alpha.txt");
    NgramSearcher ns(&ng);
    std::vector<std::string> word = ns.get_best_match("latitude");
    EXPECT_EQ(
        word,
        std::vector<std::string>(
            {"colatitude",
             "latitude",
             "latitudes",
             "midlatitude",
             "platitude",
             "platitudes",
             "platitudinisation",
             "platitudinization"}));
    word = ns.get_best_match("ltitde");
    EXPECT_EQ(word, std::vector<std::string>(
            {"multititular"}));
}


TEST(NgramSuite, Test4) {
    NgramBuilder ng("words_alpha.txt");
    NgramSearcher ns(&ng);
    std::vector<std::string> word = ns.get_best_match("la");
    std::vector<std::string> empty_v;
    EXPECT_EQ(word, empty_v);
}

TEST(NgramSuite, Test5) {
    NgramBuilder ng("words_alpha.txt");
    NgramSearcher ns(&ng);
    std::vector<std::string> word = ns.get_best_match("latitude");

    NgramBuilder ng_empty;
    ng_empty.set_ngramms("longitude");
    ng_empty.set_ngramms("latitude");

    ns.change_ngram_builder(&ng_empty);
    word = ns.get_best_match("atitud");
    EXPECT_EQ(std::vector<std::string>(
            {"latitude"}), word);
}

TEST(NgramSuite, NegativeTest1) {
    NgramBuilder ng("words_alpha.txt");
    NgramSearcher ns(&ng);
    std::vector<std::string> word = ns.get_best_match("latitude");
    EXPECT_NE(
        word,
        std::vector<std::string>(
            {"colatitude",
             "latitude",
             "latitudes",
             "midlatitude",
             "platitude",
             "platitudes",
             "platitudinisation",
             "platitudinization",
             "hello"})); // extra word "hello"
}