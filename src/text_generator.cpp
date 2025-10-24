#include "text_generator.h"
#include "language_model.h"



TextGenerator::TextGenerator(const LanguageModel& slm, const int text_length) : slm(slm), text_length(text_length) {}

void TextGenerator::generate_text() {
    int output_length = 0;

    // Specification "Generating text"
    // 5.
    while (output_length < text_length) {
        // 1.
        std::string k_gram = choose_k_gram();
        // 2.
        char c = sample_next_character(k_gram);
        // 3.
        std::cout << c;
        output_length += 1;
        // 4.
        k_gram = k_gram.substr(1, (k_gram.length()-1)); 
        k_gram += c;
    }
    std::cout << std::endl;
}

std::string TextGenerator::choose_k_gram() {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine -cppreference
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd() -cppreference
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    float random_number = distribution(gen);
    float cumulative_freq = 0.0f;
    std::map<std::string, float> k_gram_freqs = slm.get_k_gram_freqs();
    for (const auto& [k_gram, freq] : k_gram_freqs) {
        if (random_number >= cumulative_freq && random_number <= freq+cumulative_freq) {
            return k_gram;
        }
        cumulative_freq += freq;
    }
    
    // in the unlikely case the random number is like 0.999999 and cumulative_freq only
    // gets to a smaller number, say 0.999, because of floating point errors.
    return std::prev(k_gram_freqs.end())->first; // prev(slm.end()) gives last key-value pair, ->first gives key
}

// works the same way as choose_starting_k_gram, we're just looking for a char instead
// and we're looking inside transition_freqs instead of k_gram_freqs.
char TextGenerator::sample_next_character(std::string k_gram) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    float random_number = distribution(gen);

    std::map<std::string, std::map<char, float>> transition_freqs = slm.get_transition_freqs();
    float cumulative_freq = 0.0f;
    for (const auto& [next_char, freq] : transition_freqs[k_gram]) {
        if (random_number >= cumulative_freq && random_number <= freq) {
            return next_char;
        }
        cumulative_freq += freq;
    }

    // just a safety measure (same thing here as in choosing the k_gram)
    return std::prev(transition_freqs[k_gram].end())->first;
}