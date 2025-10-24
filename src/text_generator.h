#pragma once

#include "language_model.h"

#include <string>
#include <random>
#include <iostream>



class TextGenerator {
private: 
    LanguageModel slm;
    int text_length;

public:
    TextGenerator(const LanguageModel& slm, const int text_length);

    void generate_text();

private:
    std::string choose_k_gram();

    char sample_next_character(std::string k_gram);

};