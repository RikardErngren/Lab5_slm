#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <deque>



class LanguageModel {
private:
    int k;
    std::string filename; // not strictly necessary but it makes sense to have a language model know the name of the "language" (filename) it's trained on.
    std::map<std::string, float> k_gram_freqs;
    std::map<std::string, std::map<char, float>> transition_freqs;

public:
    LanguageModel(int k, std::string filename) : k(k), filename(filename) {}

    /* The following is fairly hard to read code I admit... could perhaps be divided into smaller methods.
    The idea is to use a queue to "slide" over the contents of the file and always just 
    remove the first letter of the k-gram so that you, in the next iteration when you add
    the next character, will have another k-gram that you add to the map. */ 
    void find_k_gram_freqs(std::string language) {
        int k_gram_count = language.length() - k + 1;
        std::deque<char> q;
        // using '&' avoids using copies (which is more expensive) and instead just iterates by reference
        for (char& c : language) {
            q.push_back(c);
            if (q.size() == k) {
                std::string k_gram(q.begin(), q.end());

                // don't have to check whether the key exists because C++ apparently default-constructs it automatically if it doesn't
                k_gram_freqs[k_gram] += 1.0f / k_gram_count; // normalizes immediately

                q.pop_front();
            }
        }
    }
    
    /* There is some redundancy here. We use the same basic idea as in find_k_gram_freqs, where
    we slide over the text and check what comes next for each occurence of a key. But I learned 
    about the existence of substr which seems like a far superior way of doing this.*/
    void find_transition_freqs(std::string language) {
        int n = language.length();
        int k_gram_count = language.length() - k + 1;
        
        for (int i=0; i < n-k; i++) {
            std::string k_gram = language.substr(i, k); // substr(index, length)
            char next_char = language[i+k];
            transition_freqs[k_gram][next_char] += 1.0f / k_gram_count; // normalizes immediately
        }
    }

    void print_kgram_freqs() {
        for (const auto& [kgram, freq] : k_gram_freqs) {
            std::cout << kgram << ": " << freq << std::endl;
        }
    }

    void print_transition_freqs() {
        for (const auto& [kgram, char_and_freq] : transition_freqs) {
            for (const auto& [next_char, freq] : char_and_freq) {
            std::cout << kgram << " : " << next_char << " : " << freq << std::endl;
            }
        }
    }

    void print_filename() {
        std::cout << filename << std::endl;
    }

    void print_k() {
        std::cout << k << std::endl;
    }
};


int main() {
    int k = 6;
    std::string filename = "a_modest_proposal.txt";
    LanguageModel slm(k, filename);
    std::ifstream datafile(filename);

    // The following reads a whole file into a string. It essentially specifies a range
    // from which to begin reading (which starts at datafile) and end.
    // the second part is the end-of-stream iterator (hence why it's empty).
    std::string language((std::istreambuf_iterator<char>(datafile)),
                 std::istreambuf_iterator<char>()); 

    if (language.length() <= k) {
        std::cerr << "the size of k needs to be less than or equal to the size of the whole text in the provided file." << std::endl;
        return 1;
    }

    slm.find_k_gram_freqs(language);
    //slm.print_kgram_freqs();
    slm.find_transition_freqs(language);
    slm.print_transition_freqs();
}
