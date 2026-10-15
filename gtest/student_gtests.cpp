#include <gtest/gtest.h>
#include <sstream>
#include "word_count.hpp"

using namespace std;


TEST(WordCount, ToLowercase) {
    string s1 = "APPLE";
    to_lowercase(s1);
    EXPECT_EQ(s1, "apple");

    string s2 = "MiXeD";
    to_lowercase(s2);
    EXPECT_EQ(s2, "mixed");
}


TEST(WordCount, LoadStopWords) {
 
    stringstream ss("THE AND\nIs"); 
    set<string> stops = load_stopwords(ss);
    

    EXPECT_EQ(stops.size(), 3);
    EXPECT_TRUE(stops.find("the") != stops.end());
    EXPECT_TRUE(stops.find("and") != stops.end());
    EXPECT_TRUE(stops.find("is") != stops.end());
}


TEST(WordCount, CountWords) {
    stringstream doc("Apple apple Banana the IS");
    set<string> stops = {"the", "is"}; 
    
    map<string, int> counts = count_words(doc, stops);

    EXPECT_EQ(counts.size(), 2);
    // "Apple" 和 "apple" 应该合并为 2
    EXPECT_EQ(counts["apple"], 2);
    EXPECT_EQ(counts["banana"], 1);
}


TEST(WordCount, OutputWordCounts) {

    map<string, int> counts = {
        {"zebra", 1},
        {"apple", 2}
    };
    
    stringstream ss_out;
    output_word_counts(counts, ss_out);
    
  
    string expected = "apple 2\nzebra 1\n";
    EXPECT_EQ(ss_out.str(), expected);
}