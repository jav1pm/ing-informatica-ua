#include "Intent.h"
#include <string.h>

Intent::Intent(string name){
    
    if(name == ""){
        throw ERR_EMPTY;
    }
    else{
        this->name = name;
    }
}

void Intent::addExample(const Example &example){

    if(getNumExamples() > KMAXEXAMPLES){
        throw ERR_MAXEXAMPLES;
    }
    else{
        examples.push_back(example);
    }
}

void Intent::deleteExample(int id){

    bool findIntent = false;
    int posIntent = 0;

    for(unsigned int i=0;i<examples.size();i++){
        if(examples[i].getId() == id){
            posIntent = i;
            findIntent = true;
        }
    }
    if(!findIntent){
        throw ERR_EXAMPLE;
    }
    else{
        examples.erase(examples.begin() + posIntent);
    }
}

void Intent::addResponse(string response){

    this->response = response;
}

float Intent::calculateSimilarity(string text, const char similarity[]) const{

    float sim = 0.0;
    float maxValue = 0.0;

    if(examples.size() != 0){
        if(strcmp("jc",similarity) == 0){
            for(unsigned int i=0;i<examples.size();i++){
                sim = examples[i].jaccardSimilarity(text);
                if(sim > maxValue){
                    maxValue = sim;
                }
            }
        }
        else if(strcmp("ng",similarity) == 0){
            for(unsigned int i=0;i<examples.size();i++){
                sim = examples[i].ngramSimilarity(text);
                if(sim > maxValue){
                    maxValue = sim;
                }
            }
        }
        else{
            throw ERR_SIMILARITY;
        }
    }
    return maxValue;
}

ostream& operator<<(ostream &os, const Intent &intent){

    os << "Intent: " << intent.getName() << endl;
    os << "Response: " << intent.getResponse() << endl;

    for(unsigned int i=0;i<intent.getNumExamples();i++){
        operator<<(os,intent.examples[i]);
    }
    return os;
}

