#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

// main program
int main(int argc,char *argv[]) {
    int i=1;
    string extension = "wmv";
    // decode arguments
    if(argc > 1) {
        //cout << "You must provide at least one argument\n";
        //exit(0);
        extension = argv[1];
    }
    // report settings
    // 1 - max number
    
    //for (;i<argc;i++) 
    //    printf("Argument %d:%s\n",i,argv[i]);
    
    
    char buffer[100] = "";
    /* argument 2
    istringstream ss(argv[1]);
    int max;
    if (!(ss >> max))
        cerr << "Invalid number " << argv[1] << '\n';
    */
    
    //char courselist[100] = argv[2];
    
    ifstream fin("courselist.txt");

    if (fin.is_open() == false) {
      exit(0);
    }


    
    string line;
    vector<string> lines ;
    //int counter = 1;
    while (getline(fin, line)) {   
     lines.push_back( line );
    }
   
    for(int counter = 0;counter<lines.size();counter++)
    {
      printf("%02d - %s.%s\n",counter+1,lines.at(counter).c_str(),extension.c_str());
      sprintf(buffer,"%02d - %s.%s",counter+1,lines.at(counter).c_str(),extension.c_str());
      fstream outfile;
      outfile.open(buffer,ios::out|ios::ate);     
      outfile.close();
    }
    
    return(0);
}
