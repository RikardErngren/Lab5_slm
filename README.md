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

The reason I'm using deque instead of a normal queue is because a queue is not iterable and well... I need to iterate over it to set the k-gram consisting of the elements currently in the queue. This could be changed to just using the substr-method I found and used for the find_transition_freqs but it works so I'm not touching it unnecessarily.

Normalizing the frequencies immediately is probably not the greatest idea since small floating point errors will stack up, but I tested it for the whole text of A Modest Proposal and the numbers all added up to 0.999 so I'm OK with it and don't really feel like I have to make another method just to normalize the frequencies since them adding up to something closer to 1 doesn't really matter in the context of this project. For other projects I could definitely see this actually mattering.

<.h-files>
#pragma once
is included to prevent stuff from being declared several times. For example if 
#include <string>
is declared in this file and main.cpp the compiler won't compile it since it won't know which declaration to include and throw an error. Maybe for inclusions it doesn't seem like it would cause a big issue, but if it's instead a function declared twice the program won't know which to choose so that's obviously bad.
pragma once works the same way as
#ifndef FILENAME.H
#define FILENAME.H


<text_generator.cpp>
Takes a LanguageModel object and a requested output length for the text to be created. It has the "main" method generate_text() which follows the output specifications directly. So generate_text() needs the assistance of a method to choose the starting k_gram and a method to sample the next character. They both work in pretty much the same way. A random number generator picks a random number between 0 and 1. We then basically look at whether or not that number is smaller than the frequency, but larger than the previous frequency (or 0) checked.


<main.cpp>
My largest issue with the structure of the program comes to light here. We have to call:
slm.find_k_gram_freqs(language);
slm.find_transition_freqs(language);
to actually update these before sending this slm object to the TextGenerator. This is ugly. An improvement could be to have methods in TextGenerator actually call to find these frequencies. Perhaps the getters themselves in language_model.cpp should be the ones to call the find-methods. Luckily the lab didn't specify that you have to write beautiful code so I don't have to fix stuff that already works.