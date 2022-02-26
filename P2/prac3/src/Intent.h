#ifndef _INTENT_
#define _INTENT_

#include "Example.h"

using namespace std;

class Intent{

    friend ostream& operator<<(ostream &os, const Intent &intent);

    protected:

        string name;
        string response;
        vector<Example> examples;

    public:

        static const unsigned KMAXEXAMPLES = 10;
        Intent(string name);
        string getName() const { return name; }
        string getResponse() const { return response; }
        vector<Example> getExamples() const { return examples; }
        unsigned getNumExamples() const { return examples.size(); }
        void addExample(const Example &example);
        void deleteExample(int id);
        void addResponse(string response);
        float calculateSimilarity(string text, const char similarity[]) const;
};

#endif