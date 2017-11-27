/*
markov chain text generator/poetry machine, based off of Daniel Schliefman's excellent youtube video
author: codepadawan , 9.03.17
ver. 0.9, moved methods to separate classes
*/

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <map>
#include "textGenerator.h"

int main() {
	textGenerator textgen;	//create textGenerator instance
	std::string str = textgen.readFile("source.txt"); //open the file in same dir as executable

	//create a map with data from the text file, and 4th order ngrams
	std::map<std::string, std::vector<std::string>> table = textgen.createTable(4, str);

	//generate the text and save it in a string
	std::string example = textgen.generateText(4, str, table);	

	//output to a file
	textgen.writeResultToFile(example, "output.txt");
	
	return 0;
}
