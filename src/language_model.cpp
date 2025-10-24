#include "language_model.h"



LanguageModel::LanguageModel(int k, std::string filename) : k(k), filename(filename) {}

/* The idea is to use a queue to "slide" over the contents of the file and always just 
remove the first letter of the k-gram so that you, in the next iteration when you add
the next character, will have another k-gram that you add to the map. */ 
void LanguageModel::find_k_gram_freqs(std::string language) {
    int k_gram_count = language.length() - k + 1;
    std::deque<char> q;
    // using '&' avoids using copies (which is more expensive) and instead just iterates by reference
    for (char& c : language) {
        q.push_back(c);
        if (q.size() == k) {
            std::string k_gram(q.begin(), q.end());
            k_gram_freqs[k_gram] += 1.0f / k_gram_count; // normalizes immediately
            q.pop_front();
        }
    }
}

/* There is some redundancy here. We use the same basic idea as in find_k_gram_freqs, where
we slide over the text and check what comes next for each occurence of a key. But I learned 
about the existence of substr which seems like a superior way of doing this.

The reason it's not normalized immediately is because you have to keep track and divide
by the right number as each k gram has a different number of next characters, i.e. a
different normalizer. */
void LanguageModel::find_transition_freqs(std::string language) {
    int n = language.length();
    std::map<std::string, std::map<char, float>> transition_counts; // temporary variable for absolute frequency
    
    for (int i=0; i < n-k; i++) {
        std::string k_gram = language.substr(i, k); // substr(index, length)
        char next_char = language[i+k];
        transition_counts[k_gram][next_char] += 1.0f;
    }
    
    // normalizes
    for (const auto& [k_gram, char_and_count] : transition_counts) {
        int total = 0;
        for (const auto& [next_char, count] : char_and_count) {
            total += count;
        }
        for (const auto& [next_char, count] : char_and_count) {
            transition_freqs[k_gram][next_char] = count / total;
        }
    }
}

void LanguageModel::print_kgram_freqs() {
    for (const auto& [kgram, freq] : k_gram_freqs) {
        std::cout << kgram << ": " << freq << std::endl;
    }
}

void LanguageModel::print_transition_freqs() {
    for (const auto& [kgram, char_and_freq] : transition_freqs) {
        for (const auto& [next_char, freq] : char_and_freq) {
        std::cout << kgram << " : " << next_char << " : " << freq << std::endl;
        }
    }
}

void LanguageModel::print_filename() {
    std::cout << filename << std::endl;
}

void LanguageModel::print_k() {
    std::cout << k << std::endl;
}

std::map<std::string, float> LanguageModel::get_k_gram_freqs() {
    return k_gram_freqs;
}

std::map<std::string, std::map<char, float>> LanguageModel::get_transition_freqs() {
    return transition_freqs;
}



