#ifndef _CHATBOT_
#define _CHATBOT_

#include "Intent.h"

using namespace std;

class Chatbot{

    friend ostream& operator<<(ostream &os, const Chatbot &Cb);

    protected:

        float threshold;
        char similarity[3];
        vector<Intent*>intents;

        int searchIntent(string name) const;
        string bestResponse(string query, bool debug) const;

    public:

        Chatbot();
        Chatbot(float threshold, const char similarity[]);
        float getThreshold() const { return threshold; }
        string getSimilarity() const;
        bool addIntent(Intent *pIntent);
        bool deleteIntent(string name = "", bool askConfirm = true);
        bool addExample(string name = "");
        bool deleteExample(int id = 0);
        bool addResponse(string name = "", string response = "");
        void test(bool debug = false) const;
        void configure(float threshold = -1, const char similarity[] = "");
};

#endif