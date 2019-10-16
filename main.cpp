#include "functions.h"

int main()
  {
    int option;
  	Data f;

    f.header();				//header
    f.get_thesaurus();			//get thesaurus file and store in ajancency list  
    //f.Print();        //prints node list
  
    while (option != 0)       //cancels if choice = 0
    { 
      cout << "\nPick an option.\n"
           << "1. Paragraph Replace\n" 
           << "2. Paragraph Analysis\n";           //prompt choice

      cout << "\nEnter your Selection: ";    //read in option
      cin >> option;
      
      switch (option)
      {
        case 1: 
          cout << "Paragraph Replace.\n\n"; 
	        f.get_para();					//get paragraph file and replace synonymns
          return 0;
          
        case 2: 
          cout << "Paragraph Analysis.\n\n";
          f.Analysis();   //check if paragraph is posible
          return 0;;

        default:
          cout << "Invalid selection, try again.\n";
          break;
      }
    }

  return 0;
  }