#ifndef TEXT_GENERATOR
#define TEXT_GENERATOR

class textGenerator {
	public:
		/*
			opens a file 'source.txt' and returns its contents as a c++ string
		*/
		std::string readFile(std::string fname);

		/*
			order=nth order ngrams will be extracted out of the source text;
			txt=a string obj containing the source text;
			returns a map with ngrams as keys and a weighted vector of one-char strings that can follow;
		*/
		std::map<std::string, std::vector<std::string>> createTable(int order, std::string txt);

		/*
			order = order of ngrams to be processed; txt= the target text; ngrams= data structure holding the stats;
			we need for generating the final result (a map with key=ngram, val=array of chars that can follow ngram);
		*/
		std::string generateText(int order, std::string txt, std::map<std::string, std::vector<std::string>> ngrams);

		/*
			txt = string containing the generated text to be output to file;
		*/
		void writeResultToFile(std::string txt, std::string fname);
};

#endif