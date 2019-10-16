#include "functions.h"

int ham = 0;

void Data::header() //author header
{ 
  system("clear");   //clears compiler
  cout << setw(115) << "+--------------------------------------------------------+\n";
  cout << setw(115) << "|            Computer Science and Engineering            |\n";
  cout << setw(115) << "|          CSCE 2110 - Computing Foundations II          |\n";
  cout << setw(115) << "|   Patrick Friedman     psf0023    psf0023@my.unt.edu   |\n";
  cout << setw(115) << "+--------------------------------------------------------+\n";
  cout << endl;
}

void Data::get_thesaurus()      //function for input stream
{
	ifstream file;
	vector<string> wordV, syn;
	string word, synonyms;

	char input_file[25];

	cout << "Enter the name of the thesaurus file: ";
	cin >> input_file;     //input

	file.open(input_file);      //check if valid file
  
	if (file.fail()){
	  cout << "Input does not exist.\n\n";
	  exit(EXIT_FAILURE); //if not valid end program
	}

	while(getline(file, word, ':') )					//get word
    {
    	wordV.clear();
    	syn.clear();

    	getline(file, synonyms);				//get synonyms
    	syn = split(synonyms, ',');

    	wordV.push_back(word);			//add words to vector

    	for (int i = 0; i < syn.size(); ++i)
    	{
    		wordV.push_back(syn[i]);				//add synonyms to vector
    	}
    
      if (FindPos(word) == -1)               //check if node exists already
      {
        data.push_back(wordV);          //add to vector of vectors
      }
      else if (FindPos(word) != -1)
      {
        for (int i = 0; i < syn.size(); ++i)
        {
          data[FindPos(word)].push_back(syn[i]); 
        }
      }
    
    wordV.clear();

    	for (int i = 0; i < syn.size(); ++i)
    	{
    		if (FindPos(syn[i]) == -1)
    		{
    			wordV.push_back(syn[i]);			//connect synonyms to root words and vise versa
    			wordV.push_back(word);

    			for (int j = 0; j < syn.size(); ++j)    //connect synonyms to root words and vise versa
    			{
    				if (j != i)
    				{
    					wordV.push_back(syn[j]);
    				}
    			}
    			data.push_back(wordV);
    		}
        else if (FindPos(syn[i]) != -1)
        {
          for (int j = 0; j < syn.size(); ++j)
          {
            if (j != i)
            {
              data[FindPos(syn[i])].push_back(syn[j]);
            }
          }
        }
    		wordV.clear();
    	}
    }
    file.close();
}

void Data::get_para()      //function for input stream
{
	ifstream file;
	string para, punct;
	int swap = 0;
	char input_file[25];

	cout << "Enter the name of the paragraph file: ";
	cin >> input_file;     //input

	file.open(input_file);      //check if valid file
  
	if (file.fail())
	{
	  cout << "Input does not exist.\n\n";
	  exit(EXIT_FAILURE); //if not valid end program
	}

	cout << "Enter the number of times to swap synonyms: ";			//number of hops
	cin >> swap;
	cout << endl;

	while(file >> para)			//read all individual words
	{		
		vector<int> pos;
		bool p = false;			//if punctuation
		bool c = false;			//if uppercase
		bool r = false;			//if replaced

		if (ispunct(para[para.size() - 1]) )
		{
			punct = para[para.size() - 1];
			para.erase(para.size() -1, para.size());			//clear punctuation
			p = true;
		}

		for (int i = 0; i < para.size(); ++i)
		{
			if (isupper(para[i]))			//find pos its uppercase
			{
				para[i] = tolower(para[i]);			//convert to lowercase
				c = true;
				pos.push_back(i);
			}
		}

		for (int i = 0; i < data.size(); ++i)
		{
			for (int j = 0; j < data[i].size(); ++j)
			{
        if (Find(para))					//find if in thesaurus
				{
					para = Replace(para, swap);				//replace word
					r = true;
					break;	
				}
			}
			break;
		}
    
		if (p == true)
		{
			para.append(punct);		//add back the punctuation
		}
		if (c == true && r == false)					//if it was uppercase but not replaced
		{
			for (int i = 0; i < pos.size(); ++i)
			{
				para[pos.at(i)] = toupper(para[pos.at(i)]);
			}
		}
		else if (c == true && r == true)			//if it was uppercase and was replaced
		{
			for (int i = 0; i < pos.size(); ++i)
			{
				para[pos.at(i)] = toupper(para[pos.at(i)]);		//if replaced had a uppercase, change synonym to uppercase
			}
		}
		pos.clear();
		cout << para << " ";			//print
	}
	cout << endl << endl;

	file.close();
}

vector <string> Data::split(string line, char delimiter)      //function for splitting strings
{  
  vector <string> collection;           //string set
  string member;
  
  stringstream ss(line);
  while(getline (ss, member, delimiter) )       //check string via delimiter
  {
    collection.push_back(member);         //add to vector
  }
  
  return collection;          //return string vector
}

string Data::punc_upper(string para)
{  
  if (ispunct(para[para.size() - 1]) )
  {
    para[para.size() - 1];
    para.erase(para.size() -1, para.size());			//clear punctuation
  }
  
  for (int i = 0; i < para.size(); ++i)
  {
    if (isupper(para[i]))			//find pos its uppercase
    {
      para[i] = tolower(para[i]);			//convert to lowercase
    }
  }
  return para;
}

bool Data::Find(string syn)			//checks ajacency list if word should be replaced
{
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i][0] == syn)
		{
			return true;
		}
	}
	return false;
}

int Data::FindPos(string syn)			//checks ajacency list for pos
{
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i][0] == syn)
		{
			return i + 1;
		}
	}
  return -1;
}

string Data::Replace(string para, int swap)				//replaces root word into a synonym per hops
{
  srand(time(NULL));
  int random;
  
	for (int i = 0; i < data.size(); ++i)
	{
    for (int j = 0; j < swap; ++j)
    {
      random = rand() % data[i].size();
    }
    if (data[i][0] == para)
		{
      return data[i][random];			//change to random per hop
		}
	}
}

void Data::Analysis()
{
	char input_file1[25], input_file2[25];
	vector <string> paraV, para2V;
	ifstream file1, file2;
  string para, para2;
  bool sim = true;
  
	cout << "Enter the name of the paragraph one: ";
	cin >> input_file1;     //input

	file1.open(input_file1);      //check if valid file
  
	if (file1.fail())
	{
	  cout << "Input does not exist.\n\n";
	  exit(EXIT_FAILURE); //if not valid end program
	}
  
	cout << "Enter the name of the paragraph two: ";
	cin >> input_file2;     //input

	file2.open(input_file2);      //check if valid file
  
	if (file2.fail())
	{
	  cout << "Input does not exist.\n\n";
	  exit(EXIT_FAILURE); //if not valid end program
	}  
  cout << endl;
  
	while(file1 >> para)			//read all individual words and clear punc/uppercase
	{
    para = punc_upper(para);      //fix
    paraV.push_back(para);
    //cout << para << " ";
  }
//cout << endl << endl;
  while(file2 >> para2)			//read all individual words and clear punc/uppercase
	{
    para2 = punc_upper(para2);
    para2V.push_back(para2);
    //cout << para2 << " ";
  }
//cout << endl << endl;
  
  for (int i = 0; i < paraV.size(); ++i)
  {
    if (paraV[i].compare(para2V[i]) != 0 && !ispunct(para2V[i][para2V[i].size() -2]))       //compares if files contain the same words
    {
      if (Find(paraV[i]) && Find(para2V[i]) )     //if word is in the thesaurus do test
      {
        if (!BFS(paraV[i], para2V[i]) )             //if word cant be found in bfs
        {
          sim = false;
          //cout << paraV[i] << " " << para2V[i] << endl;
          cout << "Paragraphs are dissimilar.\n\n";          
          return;           //end
        }
        else if (BFS(paraV[i], para2V[i]))       //if word can be found via bfs
        {
          //cout << paraV[i] << " " << para2V[i];
          //cout << "\nHamming distance: " << ham << endl;          //haming distance per word
          //cout << "Similar.\n" << endl;                       //found
        }
      }
      else
      {
        sim = false;
        //cout << paraV[i] << " " << para2V[i] << endl;
        cout << "Dissimilar, tests are different.\n\n";         //words are different and are not in the thesaurus
        return;           //end
      }
    }
  }
  if (sim)            //if all words are found
  {
    cout << "Paragraphs are similar.\n\n";

  }

  file1.close();
  file2.close();
}

bool Data::BFS(string start, string target)       //breadth first search
{
  vector <string> visited;        //queue
  ham = 0;
  
  visited.push_back(start);         //if start node == target node
  if (start == target)
  {
    return true;
  }
  for (int i = 0; i < visited.size(); ++i)
  {
    for(int j = 0; j < get(visited.at(i)).size(); ++j)
    {
      if (!find(get(visited.at(i)).at(j), visited) )
      {        
        if (get(visited[i]).at(j) == target)          //if found return true
        {
          return true;
        }
        else
        {
          visited.push_back(get(visited[i]).at(j));     //if not found add to visited 
          ham++;                  //increment hamming distance
        }
      }
    }
  }
  return false;
}

vector<string> Data::get(string syn)			//checks ajacency list and returns synonyms
{
	for (int i = 0; i < data.size(); ++i)
	{
		if (data[i][0] == syn)
		{
			return data[i];
		}
	}
}

bool Data::find(string syn, vector<string> visited)			//checks ajacency list if word exists
{
	for (int i = 0; i < visited.size(); ++i)
	{
		if (visited[i] == syn)
		{
			return true;
		}
	}
	return false;
}

void Data::Print()          //prints nodes and connecting synonyms
{
  ofstream out;
  out.open("LongList.txt");
  
  for (int i = 0; i < data.size(); ++i)
  {
    for (int j = 0; j < data[i].size(); ++j)
    {
      if (j == 0)
      {
        out << data[i][j] << ": ";
      }
      else if (data[i].size() == j + 1)
      {
        out << data[i][j];
      }
      else
      {
        out << data[i][j] << ", ";
      }
    }
    out << endl;
  }
}