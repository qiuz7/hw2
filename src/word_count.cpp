#include "word_count.hpp"
#include <cctype>
#include <iostream>

using namespace std;


void to_lowercase(std::string& str) {
    for (char& c : str) {
        c = std::tolower(static_cast<unsigned char>(c));
    }
}


std::set<std::string> load_stopwords(std::istream& stopwords) {
    set<string> stops;
    string word;
    while (stopwords >> word) {
        to_lowercase(word);
        stops.insert(word);
    }
    return stops;
}


std::map<std::string, int> count_words(std::istream& document, const std::set<std::string>& stopwords) {
    map<string, int> frequencies;
    string word;
    while (document >> word) {
        to_lowercase(word); 
        if (stopwords.find(word) == stopwords.end()) {
            
            frequencies[word]++;
        }
    }
    return frequencies;
}


void output_word_counts(const std::map<std::string, int>& word_counts, std::ostream& output) {
 
    for (const auto& pair : word_counts) {
        output << pair.first << " " << pair.second << "\n";
    }
}