#include "language_model.h"
#include "text_generator.h"

#include <fstream>
#include <string>
#include <iostream>



int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage <k-gram filename output_text_length>" << std::endl;
        exit(1);
    }

    int k = std::stoi(argv[1]);
    std::string filename = argv[2];
    int text_length = std::stoi(argv[3]);

    //Output text length is not relevant to the language model, that's handled by the text_generator
    LanguageModel slm(k, filename);
    std::ifstream datafile(filename);

    // The following reads a whole file into a string. It essentially specifies a range
    // from which to begin reading (which starts at datafile) and end.
    // the second part is the end-of-stream iterator (hence why it's empty).
    std::string language((std::istreambuf_iterator<char>(datafile)),
                        std::istreambuf_iterator<char>());

    if (language.length() < k) {
        std::cerr << "The size of k needs to be less than or equal to the size of the whole text in the provided file." << std::endl;
        exit(1);
    }

    slm.find_k_gram_freqs(language);
    slm.find_transition_freqs(language);
    TextGenerator generator(slm, text_length);
    generator.generate_text();

}