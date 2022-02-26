#ifndef _AUXILIAR_H_
#define _AUXILIAR_H_

#include <iostream>

using namespace std;

class Auxiliar {

protected:

  streambuf *cout_backup, *cin_backup;

  void redirectStreams(istringstream &in_stream,ostringstream &out_stream) {

    cin_backup = std::cin.rdbuf();    // back up streambuf
    cin.rdbuf(in_stream.rdbuf());  // assign streambuf to cin

    cout_backup = std::cout.rdbuf();  // back up streambuf
    cout.rdbuf(out_stream.rdbuf());  // assign streambuf to cout
  }

  void restoreStreams() {
    cin.rdbuf(cin_backup);        // restore original streambuf
        cout.rdbuf(cout_backup);      // restore original streambuf
  }

  static string rmb(const string &sorg) {  // remove all blanks
    string cleanString(string);
    string s = cleanString(sorg);
    string output;
    for (unsigned int i=0; i<s.length(); i++)
      if (s[i]!=' ' && s[i]!='\n' && s[i]!='\t')
        output+=s[i];
    return output;
  }
  
  static string convertSS(stringstream &ss) {    
    string s= ss.str();
    ss.str("");
    ss.clear();
    return s;
  }
  
};

#endif
