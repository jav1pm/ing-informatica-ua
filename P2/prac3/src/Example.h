#ifndef _EXAMPLE_
#define _EXAMPLE_

#include <iostream>
#include <vector>
#include "Util.h"

using namespace std;

class Example{

    friend ostream& operator<<(ostream &os, const Example &e);

    protected:

        int id;
        string text;
        vector<string> tokens;
        static int nextId;
        vector<string> deleteDuplicates(vector<string> v) const;
        vector<string> extraeNGramas(vector<string> v) const;

    public:

        Example(string text);
        static void resetNextId();
        int getId() const { return id; }
        string getText() const { return text; }
        vector<string> getTokens() const { return tokens; }
        float jaccardSimilarity(string text) const;
        float ngramSimilarity(string text) const;
};

#endif