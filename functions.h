#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <ctime>
using namespace std;

class Data
{
	private:
		vector < vector <string> > data;			//adjacency list

	public:
		void header();      //header
		void get_thesaurus();      //function for thesaurus stream
		void get_para();		//function for paragraph file
    void Analysis();    //paragraph analysis
    void Print();       //prints node list
    
    string punc_upper(string para);   //removes punc and uppercases
		string Replace(string para, int swap);			//function to replace root word with synonyms
		vector <string> split(string line, char delimiter);      //function for splitting strings
    vector<string> get(string syn);      //checks ajacency list and returns synonyms
    
    int FindPos(string syn);        //finds pos in list
    bool BFS(string start, string target);     //breadth first search for if synonym is possible
    bool Find(string syn);			//function to check if root word should be replaced
    bool find(string syn, vector<string> visited);			//checks ajacency list if word exists
};