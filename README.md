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

The reason I'm using deque instead of a normal queue is because a queue is not iterable and well... I need to iterate over it to set the k-gram consisting of the elements currently in the queue.

Normalizing the frequencies immediately is probably not the greatest idea since small floating point errors will stack up, but I tested it for the whole text of A Modest Proposal and the numbers all added up to 0.999 so I'm OK with it and don't really feel like I have to make another method just to normalize the frequencies since them adding up to something closer to 1 doesn't really matter in the context of this project. For other projects I could definitely see this actually mattering. Here it doesn't matter if the percentages are ever so slightly off, if you're lucky it could even make real words appear more often, but it almost certainly won't make them appear less.