# Lab5_slm
DA4007 - Lab5 - 'small language model'

<language_model.cpp>
A LanguageModel object consists of:
k - the length of words,
filename - the name of the language,
kgram_freq - the frequencies of which different k-grams occur,
transition_freq - the frequencies of which characters come after the different k-grams.

Note that output text length is not relevant to the language model, that's handled by the TextGenerator (To be continued).


Saving the entire file to a string might not be ideal, but I'm assuming we're not working with huge files here. It's possible to just use a queue directly on the opened file, but then I would have to open the file twice since I want the program to be modular enough that I don't have to find both kgram_freqs and transition_freqs in the same method. But then again, I have to loop through the string twice anyway now.