#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime>
#include <map>
#include "textGenerator.h"


std::string textGenerator::readFile(std::string fname) {

	//credits @ http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
	std::ifstream inFile;
	inFile.open(fname);//open the input file

	if (!inFile.is_open()) {
		std::cout << "I/O error. Check if file `" << fname << "` exists.";
		std::cin.get(); //make output readable to user
		exit(-1);
	} //if file read successfully we dont need to do anything

	std::stringstream strStream;
	strStream << inFile.rdbuf();//read the file

	std::string txt = strStream.str();//txt holds the content of the file
	inFile.close();

	return txt; //return string object w/ contents of file in it
}


std::map<std::string, std::vector<std::string>> textGenerator::createTable(int order, std::string txt) {

	int i;
	std::string ngram;
	std::map<std::string, std::vector<std::string>> ngrams; //map to hold: key:ngrams; val:a vector of characters that can possibly follow

	for (i = 0; i < (txt.length() - order - 1); i++) {
		ngram = txt.substr(i, order);
		ngrams[ngram].push_back(txt.substr(i + order, 1));//add to inner array characters that appear after the ngram
	}

	return ngrams;
}


std::string textGenerator::generateText(int order, std::string txt, std::map<std::string, std::vector<std::string>> ngrams) {

	int i;
	srand(time(NULL));	//we will need random int later

	std::string currentNgram = txt.substr(0, order);	//initialise to first ngram from text
	std::string result = currentNgram;

	for (i = 0; i < txt.size(); i++) {	//the stop condition exists only for debugging purposes

		std::vector<std::string> poss = ngrams[currentNgram]; //push all possible characters into a vector

		if (poss.size() == 0) {	//if the vector is empty, add an empty string as element to avoid division by 0
			poss.push_back("");
		}

		int randNum = (rand() % (poss.size()));	//pick one at random; note that since we have not handled du-				
		std::string nextChar = poss[randNum];	//plicates, chars are already weighted in the array
		result += nextChar;						//add the new string to the result
		currentNgram = result.substr(result.size() - order, order);	//set new current ngram to the last (order)
	}																//chars of our result
	
	return result;	//return result so it can be written to file
}


void textGenerator::writeResultToFile(std::string txt, std::string fname) {
	std::ofstream outFile;
	outFile.open(fname);
	outFile << txt;
	outFile.close();
}
