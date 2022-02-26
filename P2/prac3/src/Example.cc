#include <iostream>
#include "Util.h"
#include "Example.h"

using namespace std;

int Example::nextId = 1;

Example::Example(string text){

    if(text == ""){
        throw ERR_EMPTY;
    }
    else{
        this->text = text;
        this->tokens = Util::extractTokens(text);
        if(tokens.empty()){
            throw ERR_EMPTY;
        }
        this->id = nextId;
        nextId++;
    }
}

void Example::resetNextId(){

    nextId = 1;
}

/*
  Función auxiliar que elimina duplicados de un vector.
*/
vector<string> Example::deleteDuplicates(vector<string> v) const{

  for(unsigned int i=0;i<v.size();i++){
    for(unsigned int j=i+1;j<v.size();j++){
      if(v[i] == v[j]){ // Si las palabras son iguales...
        v.erase(v.begin() + j); // Eliminamos la palabra.
        j--; //Ajustamos la posición.
      }
    }
  }  
  return v;
}

float Example::jaccardSimilarity(string text) const{

  int comunes = 0;
  float division = 0.0;
  vector<string> tokensText;
  vector<string> jaccTokens; //Vector auxiliar de los tokens sin duplicados.

  tokensText = Util::extractTokens(text);
  tokensText = deleteDuplicates(tokensText);
  jaccTokens = deleteDuplicates(getTokens());

  for(unsigned int i=0;i<jaccTokens.size();i++){
    for(unsigned int j=0;j<tokensText.size();j++){
      if(jaccTokens[i] == tokensText[j]){
        comunes++;
      }
    }
  }
  division = (float) comunes / (jaccTokens.size() + tokensText.size() - comunes); // Dividimos las palabras comunes entre las palabras diferentes que hay en total.
  return division;
}

/*
    Función auxiliar para extraer ngramas.
*/
vector<string> Example::extraeNGramas(vector<string> v) const{

  vector<string> vAux;
  string sAux;
  string word;

  for(unsigned int i=0;i<v.size();i++){
    word = v[i];
    if(word.size() > 2){
      for(unsigned int j=0;j<word.size()-2;j++){
        for(unsigned int k=j;k<j+3;k++){
          sAux += word[k];
        }
        vAux.push_back(sAux);
        sAux = "";
      }
    }
  }
  return vAux;
}

float Example::ngramSimilarity(string text) const{

  int comunes = 0;
  float division = 0.0;
  vector<string> tokensText;
  vector<string> jaccTokens; //Vector auxiliar de los tokens sin duplicados.

  tokensText = Util::extractTokens(text);
  tokensText = extraeNGramas(tokensText);
  jaccTokens = extraeNGramas(getTokens());

  for(unsigned int i=0;i<jaccTokens.size();i++){
    for(unsigned int j=0;j<tokensText.size();j++){
      if(jaccTokens[i] == tokensText[j]){
        comunes++;
      }
    }
  }
  division = (float) comunes / (jaccTokens.size() + tokensText.size() - comunes); // Dividimos las palabras comunes entre las palabras diferentes que hay en total.
  return division;
}

ostream& operator<<(ostream &os, const Example &e){

    os << "Example " << e.getId() << ": " << e.getText() << endl;

    os << "Tokens " << e.getId() << ": ";
    for(unsigned int i=0;i<e.getTokens().size();i++){
      os << "<";
      operator<<(os,e.tokens[i]);
      os << ">";
    }
    os << endl;
  return os;
}