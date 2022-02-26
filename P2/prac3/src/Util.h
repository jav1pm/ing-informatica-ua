#ifndef _UTIL_
#define _UTIL_

#include <iostream>
#include <vector>

using namespace std;

string cleanString(string);

enum Error{
  ERR_OPTION,
  ERR_INTENT,
  ERR_EXAMPLE,
  ERR_RESPONSE,
  ERR_FILE,
  ERR_THRESHOLD,
  ERR_SIMILARITY,
  ERR_EMPTY,
  ERR_MAXEXAMPLES
}; 

class Util
{
  public:

    static void error(Error e);
    static string welcome();
    static vector<string> extractTokens(string text);
};

#endif
