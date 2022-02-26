#include "Chatbot.h"
#include <stdlib.h>
#include <string.h>

Chatbot::Chatbot(){
    
    this->threshold = 0.25;
    strcpy(this->similarity,"jc");
}

Chatbot::Chatbot(float threshold, const char similarity[]){

    if(threshold >= 0 && threshold <= 1){
        this->threshold = threshold;
    }
    else{
        throw ERR_THRESHOLD;
    }

    if(strcmp(similarity,"jc") == 0 || strcmp(similarity,"ng") == 0){
        strcpy(this->similarity,similarity);
    }
    else{
        throw ERR_SIMILARITY;
    }
}

string Chatbot::getSimilarity() const{

    string s(similarity);
    return s;
}

int Chatbot::searchIntent(string name) const{

    int posIntent = -1;

    for(unsigned int i=0;i<intents.size() && posIntent==-1;i++){
        if((*intents[i]).getName() == name){
            posIntent = i;
        }
    }
    return posIntent;
}

bool Chatbot::addIntent(Intent *pIntent){

    bool check = false;
    int posIntent = searchIntent(pIntent->getName());

    if(posIntent != -1){
        Util::error(ERR_INTENT);
    }
    else{
        check = true;
        intents.push_back(pIntent);
    }
    return check;
}

bool Chatbot::deleteIntent(string name, bool askConfirm){

    char option;
    bool check = false;

    if(name == ""){
        cout << "Intent name: ";
        getline(cin, name);
    }

    int posIntent = searchIntent(name);

    if(posIntent == -1){
        Util::error(ERR_INTENT);
    }
    else{
        if(askConfirm){
            do{
                cout << "Confirm [Y/N]?: ";
                cin >> option; cin.get();

                if(option == 'Y' || option == 'y'){
                    intents.erase(intents.begin() + posIntent);
                    check = true;
                }
            } while(option != 'y' && option != 'Y' && option != 'n' && option != 'N');
        }
        else{
            intents.erase(intents.begin() + posIntent);
            check = true;
        }
    }
  return check;
}

bool Chatbot::addExample(string name){

    bool check = false;

    string ejemplos = "";
    vector<string> token;

    if(name == ""){
        cout << "Intent name: ";
        getline(cin, name);
    }

    int posIntent = searchIntent(name);

    if(posIntent == -1){ // Si el nombre del Intent no existe, error.
        Util::error(ERR_INTENT);
    }
    else{
        do{
            cout << "New example: ";
            getline(cin, ejemplos);

            if(ejemplos != "q"){
                try{
                    Example example(ejemplos);
                    (*intents[posIntent]).addExample(example);
                    check = true;
                }
                catch(Error e){
                    Util::error(e);
                }
            }
        } while(ejemplos != "q");
    }
    return check;
}

bool Chatbot::deleteExample(int id){

    bool findID = false;
    vector<Example> examples;

    
    if(id == 0){
        cout << "Example id: ";
        cin >> id;
    }

    for(unsigned int i=0;i<intents.size();i++){
        examples = (*intents[i]).getExamples();
        for(unsigned j=0;j<examples.size();j++){
            if(examples[j].getId() == id){
                (*intents[i]).deleteExample(id);
                findID = true;
            }
        }
    }
    if(!findID){
        Util::error(ERR_EXAMPLE);
    }
    return findID;
}

bool Chatbot::addResponse(string name, string response){

    bool check = false;

    if(name == ""){
        cout << "Intent name: ";
        getline(cin,name);
    }

    int posIntent = searchIntent(name);

    if(posIntent == -1){ // Si el nombre introducido no existe, error.
        Util::error(ERR_INTENT);
    }
    else{
        if(response == ""){
            cout << "New response: ";
            getline(cin,response);
        }
        (*intents[posIntent]).addResponse(response);
        check = true;
    }
    return check;
}

string Chatbot::bestResponse(string query, bool debug) const{

    float value = 0.0, maxValue = 0.0;
    int posIntent = 0;
    bool controlIntent = false;
    string text = "";

    if(getSimilarity() == "jc"){
        for(unsigned int i=0;i<intents.size();i++){
            value = (*intents[i]).calculateSimilarity(query,"jc");
            
            if(value > maxValue && value >= threshold){
                maxValue = value;
                posIntent = i;
                controlIntent = true;
            }
        }
    }

    if(getSimilarity() == "ng"){
        for(unsigned int i=0;i<intents.size();i++){
            value = (*intents[i]).calculateSimilarity(query,"ng");
            
            if(value > maxValue && value >= threshold){
                maxValue = value;
                posIntent = i;
                controlIntent = true;
            }
        }
    }

    if(!controlIntent){
        throw ERR_RESPONSE;
    }

    if(debug){
        text += "(";
        text += to_string(maxValue);
        text += ") ";
    }
    text += (*intents[posIntent]).getResponse();
    return text;
}

void Chatbot::test(bool debug) const{

    string reply = "";
    cout << ">> " << Util::welcome() << endl;

    do{
    cout << "<< "; 
    getline(cin,reply);

    if(reply != "q" && reply != ""){
        try{
            if(bestResponse(reply,debug) != ""){
                cout << ">> " << bestResponse(reply, debug) << endl;
            }
        }
        catch(Error e){
            Util::error(e);
        }
    }
  }while(reply != "q");
}

void Chatbot::configure(float threshold, const char similarity[]){
    
    string alg = similarity;

    if(threshold == -1){
        cout << "Enter threshold: ";
        cin >> threshold;
    }

    if(threshold < 0 || threshold > 1){
        Util::error(ERR_THRESHOLD);
    }
    else{
        this->threshold = threshold;
    }
    if(alg == ""){
        cin.ignore();
        cout << "Enter algorithm: ";
        getline(cin,alg);
    }

    if(alg == "jc" || alg == "ng") {
        strcpy(this->similarity, alg.c_str());
    }
    else{
        Util::error(ERR_SIMILARITY);
    }
}

ostream& operator<<(ostream &os, const Chatbot &Cb){

    int totalExamples = 0;

    if(strcmp(Cb.similarity,"jc") == 0){
        os << "Similarity: Jaccard" << endl;
    }

    if(strcmp(Cb.similarity,"ng") == 0){
        os << "Similarity: N-grams" << endl;
    }

    os << "Threshold: " << Cb.threshold << endl;

    for(unsigned int i=0;i<Cb.intents.size();i++){
        os << (*Cb.intents[i]);
        totalExamples += Cb.intents[i]->getNumExamples();
    }
    os << "Total intents: " << Cb.intents.size() << endl;
    os << "Total examples: " << totalExamples << endl;
    
    if(totalExamples != 0){
        os << "Examples per intent: " << (float) totalExamples/Cb.intents.size();
    }
    else {
        os << "Examples per intent: " << 0;
    }
    return os;
}