#include "ngram/ngram.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>

TEST(NgramSuite, Test1) {
    ngram ng;
    ng.set_ngramms("longitude");
    std::string str = "git";
    EXPECT_EQ(ng.is_exists(str), true);
}
