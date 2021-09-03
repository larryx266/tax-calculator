all: taxCalculator

taxCalculator: taxCalculator.cpp
	g++ -g -Wall taxCalculator.cpp -o tax

clean:
	-@rm taxCalculator