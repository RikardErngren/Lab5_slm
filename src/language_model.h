// prevents stuff from being declared several times. For example if #include <string> is
// declared in this file and main.cpp
#pragma once

#include <map>
#include <string>



class LanguageModel {
private:
    int k;
    std::string filename;
    std::map<std::string, float> k_gram_freqs;
    std::map<std::string, std::map<char, float>> transition_freqs;

public:
    LanguageModel(int k, std::string filename) : k(k), filename(filename) {}

    void find_k_gram_freqs(std::string language) {}
 
    void find_transition_freqs(std::string language) {}

    void print_kgram_freqs() {}

    void print_transition_freqs() {}

    void print_filename() {}

    void print_k() {}

};