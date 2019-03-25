/* list contents of a directory */
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <assert.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "dirent.h"

using namespace std;
string itos(int i) // convert int to string
{
    stringstream s;
    s << i;
    return s.str();
}
int main (int argc, char *argv[]) {

  vector<string> results;
  /* print contents of directories listed in command line */
  DIR *dir;
  struct dirent *ent;
    
    /* open directory stream */
  dir = opendir (".");
  string extension = "wmv";
  
  // decode arguments
  if(argc > 1) {
      extension = argv[1];
  }
  
  if (dir != NULL) {
  
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      switch (ent->d_type) {
      case DT_REG: //entry is regular file
        string fname = ent->d_name;
        if(fname.find(extension,(fname.length() - extension.length())) != string::npos)
        {
            printf ("%*.*s\n", ent->d_namlen, ent->d_namlen, ent->d_name);
            results.push_back(fname);
        }
        break;
      }
    }
  
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }
  
  
  ifstream fin("courselist.txt");
    
  if (fin.is_open() == false) {
    exit(0);
  }  
    
  string line;
  vector<string> lines ;
  
  while (getline(fin, line)) {   
     lines.push_back( line );
  }
  
  char buffer[100] = "";
  string index = "";
  for(int counter = 0;counter<lines.size();counter++)
  {
    sprintf(buffer,"%02d",counter+1);
    index = buffer;
    rename(results.at(counter).c_str(),(index + " - " + lines.at(counter) + "." + extension).c_str());
  }
  
  
  return EXIT_SUCCESS;
}


