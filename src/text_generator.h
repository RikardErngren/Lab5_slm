#pragma once

#include <language_model.h>
#include <string>
#include <random>




class TextGenerator {
private: 
    LanguageModel slm;

public:
    TextGenerator(LanguageModel slm) {}

    std::string generate_text() {}

    std::string choose_starting_k_gram() {}

};