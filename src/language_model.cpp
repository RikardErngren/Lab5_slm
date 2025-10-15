#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <deque>


class LanguageModel {
private: //should probably add getters for all these private variables
    int k;
    std::string filename; // not strictly necessary but it makes sense to have a language model know the name of the "language" (filename) it's trained on.
    std::map<std::string, float> k_gram_freqs;
    std::map<std::string, std::map<char, int>> transition_freqs;

public:
    LanguageModel(int k, std::string filename) : k(k), filename(filename) {}


    /* fairly hard to read code I admit... could perhaps be divided into smaller methods.
    the idea is to use a queue to "slide" over the contents of the file  and always just 
    remove the first letter of the k-gram so that you, in the next iteration when you ad
    the next character, will have another k-gram that you add to the map. */ 
    void find_k_gram_frequencies(std::string language) {
        int k_gram_count = language.length() - k + 1;
        std::deque<char> q;
        for (char c : language) {
            q.push_back(c);
            if (q.size() == k) {
                std::string k_gram(q.begin(), q.end());

                // count returns 1 or 0 so this just checks 
                // if there's already a key with that name in the map 
                if (k_gram_freqs.count(k_gram)) {
                    k_gram_freqs[k_gram] += 1.0f / k_gram_count; //normalizes immediately
                } else {
                    k_gram_freqs.insert({k_gram, 1.0f / k_gram_count});
                }
                q.pop_front(); // removes first element of the queue
            }

        }
    }
    
    void get_transition_freqs() {}


    void print_kgram_freqs() {
        for (const auto& [kgram, freq] : k_gram_freqs) {
            std::cout << kgram << ": " << freq << std::endl;
        }
    }

};

int main() {
    int k = 3;
    std::string filename = "test_text.txt";
    LanguageModel slm(k, filename);
    std::ifstream datafile(filename);

    // The following reads a whole file into a string. It essentially specifies a range
    // from which to begin reading (which starts at datafile) and end.
    // the second part is the end-of-stream iterator (hence why it's empty).
    std::string language((std::istreambuf_iterator<char>(datafile)),
                 std::istreambuf_iterator<char>()); 

    if (language.length() < k) {
        std::cerr << "the size of k needs to be less than the size of the whole text in the provided file." << std::endl;
        return 1;
    }

    slm.find_k_gram_frequencies(language);
    slm.print_kgram_freqs();
}
