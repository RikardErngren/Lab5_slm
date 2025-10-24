program: main.o text_generator.o language_model.o
	g++ main.o text_generator.o language_model.o -o slm

main.o: main.cpp language_model.h text_generator.h
	g++ -c main.cpp

text_generator.o: text_generator.cpp language_model.h text_generator.h
	g++ -c text_generator.cpp

language_model.o: language_model.cpp language_model.h
	g++ -c language_model.cpp

clean:
	rm -f *.o slm
