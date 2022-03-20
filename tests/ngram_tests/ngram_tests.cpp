#include "ngram/ngram.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

TEST(NgramSuite, Test1) {
    ngram ng(1);
    ng.set_ngramms("longitude");
    std::string str = "git";
    EXPECT_EQ(ng.is_exists(str), true);
}

TEST(NgramSuite, Test2) {
    ngram ng;
    std::vector<std::string> word = ng.search_ngram("ltitde");
    std::vector<std::string> word2;
    word2.push_back("multititular");
    EXPECT_EQ(word, word2);
}

TEST(NgramSuite, Test3) {
    ngram ng;
    std::vector<std::string> word = ng.search_ngram("latitude");
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
}

TEST(NgramSuite, Test4) {
    ngram ng;
    std::vector<std::string> word = ng.search_ngram("la");
    std::vector<std::string> empty_v;
    EXPECT_EQ(word, empty_v);
}

TEST(NgramSuite, NegativeTest1) {
    ngram ng;
    std::vector<std::string> word = ng.search_ngram("latitude");
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