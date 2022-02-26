#include "Util.h"
#include <sstream>

using namespace std;

const int KSIZE=10;

const string greetings[KSIZE]={
  "Hola, ¿en qué puedo ayudarte?",
  "¿Qué puedo hacer hoy por ti?",
  "Oh, gran prócer de los bits, ¿cuál es tu deseo?",
  "Buenas",
  "¿Qué quieres?",
  "¿Otra vez necesitas ayuda?",
  "¡Hola! Soy Megabot 3000. ¿En qué puedo ayudarte?",
  "Bonito día para ser Megabot 3000",
  "Pregunta sin miedo",
  "Soy todo oídos"
};

void Util::error(Error e){
  switch(e){
    case ERR_OPTION:
      cout << "ERROR: wrong menu option" << endl;
      break;
    case ERR_INTENT:
      cout << "ERROR: wrong intent name" << endl;
      break;
    case ERR_EXAMPLE:
      cout << "ERROR: wrong example id" << endl;
      break;
    case ERR_RESPONSE:
      cout << "Lo siento, pero no tengo respuesta para eso" << endl;
      break;
    case ERR_FILE:
      cout << "ERROR: cannot open file" << endl;
      break;
    case ERR_THRESHOLD:
      cout << "ERROR: the threshold value must be between 0 and 1" << endl;
      break;
    case ERR_SIMILARITY:
      cout << "ERROR: valid values are \"jc\" (Jaccard) and \"ng\" (n-grams)" << endl;
      break;
    case ERR_EMPTY:
      cout << "ERROR: empty strings are not permited" << endl;
      break;
    case ERR_MAXEXAMPLES:
      cout << "ERROR: cannot add more examples" << endl;
  }
}

string Util::welcome(){
  int position = rand() % KSIZE;
  return greetings[position];
}

vector<string> Util::extractTokens(string text){

  vector<string> token;
  string cadenaAux;
  string cadena;

  string cadenaNormalizada = "";
  cadena = cleanString(text);

  for(unsigned int i=0;i<cadena.size();i++){
    if(isalnum(cadena[i]) || cadena[i] == ' '){
      cadenaNormalizada += tolower(cadena[i]);
    }
  }
  stringstream ss (cadenaNormalizada);

  while(ss >> cadenaAux){
    if(cadenaAux[cadenaAux.size()-1] == 's'){
      cadenaAux.erase(cadenaAux.begin() + cadenaAux.size()-1);
    }
    if(cadenaAux.size() != 0){
      token.push_back(cadenaAux);
    }
  }
  return token;
}
