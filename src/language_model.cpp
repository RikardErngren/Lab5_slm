#include <string>
#include <map>



class LanguageModel {
private: 
    int k;
    std::string filename; 
    std::map<std::string, float> kgram_freqs;
    std::map<std::string, std::map<char, int>> transition_freqs;

public:
    LanguageModel(int k, string filename) : k(k), filename(filename)) {}

    void get_kgram_frequencies() {

    }



};


