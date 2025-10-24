#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <deque>



class LanguageModel {
private:
    int k;
    std::string filename;
    std::map<std::string, float> k_gram_freqs;
    std::map<std::string, std::map<char, float>> transition_freqs;

public:
    LanguageModel(int k, std::string filename);
    void find_k_gram_freqs(std::string language);
 
    void find_transition_freqs(std::string language);

    void print_kgram_freqs();

    void print_transition_freqs();

    void print_filename();

    void print_k();

    std::map<std::string, float> get_k_gram_freqs();

    std::map<std::string, std::map<char, float>> get_transition_freqs();
};