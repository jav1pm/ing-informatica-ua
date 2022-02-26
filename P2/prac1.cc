// DNI 74384305M   PEREZ MARTINEZ, FRANCISCO JAVIER
#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <cctype>
#include <sstream>

using namespace std;

string cleanString(string);

enum Error{
  ERR_OPTION,
  ERR_INTENT,
  ERR_EXAMPLE,
  ERR_RESPONSE
};

struct Example{
  int id;
  string text;
  vector<string> tokens;
};

struct Intent{
  string name;
  vector<Example> examples;
  string response;
};

struct Chatbot{
  int nextId;
  float threshold;
  char similarity[3];
  vector<Intent> intents;
};

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

void error(Error n){
  switch(n){
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
  }
}

void showMainMenu(){
  cout << "1- Train" << endl
       << "2- Test" << endl
       << "3- Report" << endl
       << "q- Quit" << endl
       << "Option: ";
}

void showTrainMenu(){
  cout << "1- Add intent" << endl
       << "2- Delete intent" << endl
       << "3- Add example" << endl
       << "4- Delete example" << endl
       << "5- Add response" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

/*
  Funcion auxiliar para buscar el nombre de un intent en el vector de intents.
*/
void findIntent(Chatbot megabot, string intentName, int &pos){
  
  pos = -1; // Si el nombre del Intent no existe devuelve -1.

  for(unsigned int i=0;i<megabot.intents.size();i++){
    if(megabot.intents[i].name == intentName){
      pos = i; // Si el nombre del Intent existe, guardamos su posición.
    }
  }
}

void addIntent(Chatbot &megabot){

  string intentName = "";
  int posIntent = 0;
  Intent intent;

  cout << "Intent name: ";
  getline(cin, intentName);

  findIntent(megabot, intentName, posIntent); // Llamada a la función auxiliar que busca el nombre del Intent introducido.

  if(posIntent != -1){ // Si ya existe un intent con ese nombre, error.
    error(ERR_INTENT);
  }
  else{
    intent.name = intentName; // Asignamos el nombre.
    intent.response = "";
    megabot.intents.push_back(intent); // Añadimos el nombre al final del vector.
  }
}

void deleteIntent(Chatbot &megabot){

  string intentName = "";
  char option;
  int posIntent = 0;

  cout << "Intent name: ";
  getline(cin, intentName);

  findIntent(megabot, intentName, posIntent); // Llamada a la función auxiliar que busca el nombre del Intent introducido.

  if(posIntent == -1){ // Si el nombre introducido no existe, error.
    error(ERR_INTENT);
  }
  else{
    do{
      cout << "Confirm [Y/N]?: ";
      cin >> option; cin.get();

      if(option == 'Y' || option == 'y'){
        megabot.intents.erase(megabot.intents.begin() + posIntent);
      }
    } while(option != 'y' && option != 'Y' && option != 'n' && option != 'N');
  }
}

/*
  Funcion auxiliar que se encarga de normalizar la cadena eliminando carácteres que no sean alfanuméricos y pasar la cadena a minúsuclas.
*/
void normalizarCadena(string &cadena){

  string cadenaNormalizada = "";
  cadena = cleanString(cadena);

  for(unsigned int i=0;i<cadena.size();i++){
    if(isalnum(cadena[i]) || cadena[i] == ' '){
      cadenaNormalizada += tolower(cadena[i]);
    }
  }
  cadena = cadenaNormalizada;
}

/*
  Función auxiliar que se encarga de tokenizar las palabras y eliminar la 's' de final de palabra.
*/
vector<string> separateWords(string cadena){

  vector<string> token;
  string cadenaAux;
  stringstream ss (cadena);

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

void addExample(Chatbot &megabot){

  string intentName = "";
  string ejemplos = "";
  Example example;
  vector<string> token;

  int posIntent=0;

  cout << "Intent name: ";
  getline(cin, intentName);

  findIntent(megabot, intentName, posIntent); // Llamada a la función auxiliar que busca el nombre del Intent introducido.

  if(posIntent == -1){ // Si el nombre del Intent no existe, error.
    error(ERR_INTENT);
  }
  else{
    do{
      cout << "New example: ";
      getline(cin, ejemplos);

      if(ejemplos != "q"){
        example.text = ejemplos;
        example.id = megabot.nextId;
        megabot.nextId++;

        normalizarCadena(ejemplos);
        token = separateWords(ejemplos); // Llamada a la función auxiliar que normaliza y separa en palabras (tokens) la cadena.
        example.tokens = token;

        if(example.tokens.size() != 0){
          megabot.intents[posIntent].examples.push_back(example);
        }
        else {
          megabot.nextId--;
        }
      }
    } while(ejemplos != "q");
  }
}

void deleteExample(Chatbot &megabot){

  int idAux = 0;
  bool findID = false; // Variable booleana para controlar si el ID existe o no.

  int posId = 0; // Variable para guardar la posición del id encontrado.
  int posIntent = 0;
  

  cout << "Example id: ";
  cin >> idAux;

  for(unsigned int i=0;i<megabot.intents.size();i++){
    for(unsigned int j=0;j<megabot.intents[i].examples.size();j++){
      if(idAux == megabot.intents[i].examples[j].id){
        posId = j;
        posIntent = i;
        findID = true;
      }
    }
  }

  if(findID == false){ // Si el ID no existe, error.
    error(ERR_EXAMPLE);
  }
  else{
    megabot.intents[posIntent].examples.erase(megabot.intents[posIntent].examples.begin() + posId);
  }
}

void addResponse(Chatbot &megabot){

  string intentName = "";
  string respuesta = "";
  Intent answer;
  int posIntent = 0;

  cout << "Intent name: ";
  getline(cin,intentName);

  findIntent(megabot, intentName, posIntent); // Llamada a la función auxiliar que normaliza y separa en palabras (tokens) la cadena.

  if(posIntent == -1){ // Si el nombre introducido no existe, error.
    error(ERR_INTENT);
  }
  else{
    cout << "New response: ";
    getline(cin,respuesta);

    megabot.intents[posIntent].response = respuesta;
  }
}

void train(Chatbot &megabot){
    
  char option;

  do{
      showTrainMenu();
      cin >> option;
      cin.get();

      switch(option){
        case '1':
          addIntent(megabot);
          break;
        case '2':
          deleteIntent(megabot);
          break;
        case '3':
          addExample(megabot);
          break;
        case '4':
          deleteExample(megabot);
          break;
        case '5':
          addResponse(megabot);
          break;
        case 'b':
          break;
        default:
          error(ERR_OPTION);
      }
  } while(option != 'b');
}

/*
  Función auxiliar que elimina duplicados de un vector.
*/
vector<string> deleteDuplicates(vector<string> v){

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

/*
  Función auxiliar para realizar los respectivos cálculos del coeficiente de Jaccard.
*/
void calculaJaccard(const Chatbot &megabot, const vector<string> &Atokens){

  vector<string> tokensAux; // Vector auxiliar para almacenar los tokens pero sin duplicados.
  bool controlIntent = false; // Variable booleana para comprobar si se ha superado el umbral de similitud.
  float division = 0.0;
  float maxJacc = 0.0;
  int posIntent = 0;
  int comunes = 0;

  for(unsigned int i=0;i<megabot.intents.size();i++){
    for(unsigned int j=0;j<megabot.intents[i].examples.size();j++){
      tokensAux = deleteDuplicates(megabot.intents[i].examples[j].tokens); // Eliminamos duplicados del vector de tokens y lo guardamos en el auxiliar.    
      
      for(unsigned int k=0;k<tokensAux.size();k++){
        for(unsigned int w=0;w<Atokens.size();w++){
          if(Atokens[w] == tokensAux[k]){ // Si las palabras coinciden...
            comunes++; // Aumentamos el contador de palabras comunes.
          }
        }
      }
      division = (float) comunes / (tokensAux.size() + Atokens.size() - comunes); // Dividimos las palabras comunes entre las palabras diferentes que hay en total.

      if(division > maxJacc && division >= megabot.threshold){ // Comprobamos que supere el mínimo valor de similitud
        maxJacc = division; // Si el siguiente valor es mayor que el anterior, lo guardamos.
        posIntent = i;
        controlIntent = true;
      }
      comunes = 0;
    }
  }

  if(controlIntent == false){ // Si no ha superado el umbral de similitud, error.
    error(ERR_RESPONSE);
  }
  else{
    if(megabot.intents[posIntent].response != ""){
      cout << ">> " << megabot.intents[posIntent].response << endl;
    }
  }
  maxJacc = 0.0;
  controlIntent = false;
}

void test(const Chatbot &megabot){

  string reply = "";
  vector<string> Atokens;
  int position = rand() % KSIZE;

  cout << ">> " << greetings[position] << endl;

  do{
    cout << "<< "; getline(cin,reply);

    if(reply != "q"){
      normalizarCadena(reply);
      Atokens = separateWords(reply); // Vector de la consulta del usuario normalizado.
      Atokens = deleteDuplicates(Atokens); // Eliminamos duplicados.
      calculaJaccard(megabot, Atokens);
    }
  }while(reply != "q");
}

void report(const Chatbot &megabot){

  int totalExamples = 0;

  cout << "Similarity: Jaccard" << endl;
  cout << "Threshold: " << megabot.threshold << endl;
  
  for(unsigned int i=0;i<megabot.intents.size();i++){
    cout << "Intent: " << megabot.intents[i].name << endl;
    cout << "Response: " << megabot.intents[i].response << endl;
    for(unsigned int j=0;j<megabot.intents[i].examples.size();j++){
      cout << "Example " << megabot.intents[i].examples[j].id << ": " << megabot.intents[i].examples[j].text << endl;
      totalExamples++;
      cout << "Tokens " << megabot.intents[i].examples[j].id << ": ";
      for(unsigned int k=0;k<megabot.intents[i].examples[j].tokens.size();k++){
        cout << "<" << megabot.intents[i].examples[j].tokens[k] << "> ";
      }
      cout << endl;
    }
  }
  cout << "Total intents: " << megabot.intents.size() << endl;
  cout << "Total examples: " << totalExamples << endl;

  if(totalExamples != 0){
    cout << "Examples per intent: " << (float) totalExamples/megabot.intents.size() << endl;
  }
  else {
    cout << "Examples per intent: " << 0 << endl;
  }
}

int main(){
  Chatbot megabot;
  megabot.nextId=1;
  megabot.threshold=0.25;
  strcpy(megabot.similarity,"jc");
    
  srand(666);

  char option;
  do{
    showMainMenu();
    cin >> option;
    cin.get();
        
    switch (option){ 
      case '1':
        train(megabot);
        break;
      case '2':
        test(megabot);
        break;
      case '3':
        report(megabot);
        break;
      case 'q':
        break;
      default:
        error(ERR_OPTION);
    }
  }while(option!='q');
    
  return 0;
}