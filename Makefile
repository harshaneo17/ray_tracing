build:
	g++ -o main -I ./include ./src/ppm_image.cpp
clean:
	$(RM) ./src/main

