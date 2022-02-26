#include <iostream>
#include <string.h>
#include <vector>
#include <stdlib.h>
#include <cctype>
#include <sstream>
#include <fstream>

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
  ERR_ARGS
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

const int KMAXTEXTS = 15;
const int KMAXTEXTL = 1000;

struct BinIntent{
  char name[KMAXTEXTS];
  unsigned numExamples;
  char response [KMAXTEXTL];
};

struct BinChatBot{
  float threshold;
  char similarity[3];
  unsigned numIntents;
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
    case ERR_ARGS:
      cout << "ERROR: invalid arguments" << endl;
  }
}

void showMainMenu(){
  cout << "1- Train" << endl
       << "2- Test" << endl
       << "3- Report" << endl
       << "4- Configure" << endl
       << "5- Import data" << endl
       << "6- Export data" << endl
       << "7- Load chatbot" << endl
       << "8- Save chatbot" << endl
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

vector<string> extraeNGramas(vector<string> v){

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

void calculaNGramas(const Chatbot &megabot, const vector<string> &Atokens){

  vector<string>tokensAux;
  int comunes = 0;
  float division = 0.0;
  float maxJacc = 0.0;
  int posIntent = 0;
  bool controlIntent = false;

  for(unsigned int i=0;i<megabot.intents.size();i++){
    for(unsigned int j=0;j<megabot.intents[i].examples.size();j++){
      tokensAux = separateWords(megabot.intents[i].examples[j].text);
      tokensAux = extraeNGramas(tokensAux);
      tokensAux = deleteDuplicates(tokensAux);

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

    if(reply != "q" && strcmp(megabot.similarity,"jc") == 0){
      normalizarCadena(reply);
      Atokens = separateWords(reply); // Vector de la consulta del usuario normalizado.
      Atokens = deleteDuplicates(Atokens); // Eliminamos duplicados.
      calculaJaccard(megabot, Atokens);
    }
    else if(reply != "q" && strcmp(megabot.similarity,"ng") == 0){
      Atokens = separateWords(reply);
      Atokens = extraeNGramas(Atokens);
      Atokens = deleteDuplicates(Atokens);
      calculaNGramas(megabot,Atokens);
    }
  }while(reply != "q");
}

void report(const Chatbot &megabot){

  int totalExamples = 0;

  if(strcmp("ng",megabot.similarity) == 0){
    cout << "Similarity: N-grams" << endl;
  }
  if(strcmp("jc",megabot.similarity) == 0){
    cout << "Similarity: Jaccard" << endl;
  }
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

void configure(Chatbot &megabot){
  
  float umbral = 0.0;
  string alg;
  char algoritmo[3];

  cout << "Enter threshold: ";
  cin >> umbral;

  if(umbral < 0 || umbral > 1){
    error(ERR_THRESHOLD);
  }
  else{
    megabot.threshold = umbral;
  }

  cin.get();
  cout << "Enter algorithm: ";
  getline(cin,alg);

  if(alg == "jc" || alg == "ng") {
    strcpy(algoritmo, alg.c_str());
    strcpy(megabot.similarity, algoritmo);
  }
  else{
    error(ERR_SIMILARITY);
  }
}

/*
  Función auxiliar para almacenar los intents.
*/
void addIntentForFiles(string &intentName, string &response, vector<Example> &examples, Chatbot &megabot){

  int posIntent = 0;
  Intent intent;

  findIntent(megabot, intentName, posIntent); // Llamada a la función auxiliar que busca el nombre del Intent introducido.

  if(posIntent != -1){ // Si ya existe un intent con ese nombre, error.
    error(ERR_INTENT);
  }
  else{
    intent.name = intentName; // Asignamos el nombre.
    intent.response = response; // Asignamos respuesta.
    intent.examples = examples; // Asignamos examples.
    megabot.intents.push_back(intent); // Añadimos el nombre al final del vector.
  }
  //Limpiar buffer.
  examples.clear();
  intentName = "";
  response = "";
}

/*
  Función auxiliar para almacenar los examples.
*/
void addExampleForFiles(string &ejemplos, vector<Example> &examplesFILES, Chatbot &megabot){

  Example example;
  vector<string>token;

  example.text = ejemplos;
  example.id = megabot.nextId;
  megabot.nextId++;

  normalizarCadena(ejemplos); // Llamada a función que normaliza la cadena.
  token = separateWords(ejemplos); // Llamada a función que tokeniza la cadena.
  example.tokens = token;

  if(example.tokens.size() != 0){
    examplesFILES.push_back(example);
  }
  else {
    megabot.nextId--;
  }
  //Limpiar buffer para siguientes examples.
  ejemplos = "";
}

void readFile(Chatbot &megabot, string input){

  string name, response, examples; // Variables auxiliares.
  vector<Example> examplesFILES; // Vector auxiliar de examples.

  bool checkName = true; // Variable para controlar el nombre del intent.
  bool checkResponse = false; // Variable para controlar la respuesta.
  bool checkExamples = false; // Variable para controlar los examples.

  for(unsigned int i=0;i<input.length();i++){
    if(input[i] == '#' && checkName && !checkResponse && !checkExamples){
      i++;
      name = "";
      while(input[i] != '#') {
        name += input[i];
        i++;
      }
      checkName = false;
      checkResponse = true;
    }
    if(input[i] == '#' && !checkName && checkResponse && !checkExamples){
      i++;
      response = "";
      while(input[i] != '\n') {
        response += input[i];
        i++;
      }
      checkResponse = false;
      checkExamples = true;
    }
    if(checkExamples){
      if(i == input.size()-1){ // Si estamos al final y ya no hay más #intents#.
        examples += input[i];
        addExampleForFiles(examples,examplesFILES,megabot);
        addIntentForFiles(name,response,examplesFILES,megabot);
      }
      else {
        if(input[i] == '\n' && input[i+1] != '#') { // Si en la siguiente posición no hay #, signifca que tenemos que añadir examples.
          addExampleForFiles(examples,examplesFILES,megabot);
        }
        else if(input[i] == '\n' && input[i+1] == '#'){ // Si en la siguiente encontramos un #, añadiriamos intent y sus respectivos examples.
          addExampleForFiles(examples,examplesFILES,megabot);
          addIntentForFiles(name,response,examplesFILES,megabot);
          checkName = true;
          checkExamples = false;
        }
        else{ // En cualquier otro caso, añadimos examples.
          if(input[i] == '\n'){
            addExampleForFiles(examples,examplesFILES,megabot);
          }
          else{
            examples += input[i];
          }
        }
      }
    }
  }
}

void importData(Chatbot &megabot){

  ifstream input;
  string filename, line, fichero;

  cout << "Enter filename: ";
  getline(cin, filename);

  input.open(filename.c_str(), ios::in);
  if(input.is_open()){
    while(getline(input, line)) {
      fichero += line + '\n';
    }
    readFile(megabot, fichero);
    input.close();
  }
  else {
    error(ERR_FILE);
  }
}

void argImport(Chatbot &megabot, string filename){
  
  ifstream input;
  string line, fichero;

  input.open(filename.c_str(), ios::in);
  if(input.is_open()){
    while(getline(input, line)) {
      fichero += line + '\n';
    }
    readFile(megabot, fichero);
    input.close();
  }
  else {
    error(ERR_FILE);
  }
}

void exportAllIntents(ofstream &output, Chatbot &megabot){
  
  for(unsigned int i=0;i<megabot.intents.size();i++){
    output << "#" << megabot.intents[i].name << "#" << megabot.intents[i].response << endl;
    for(unsigned int j=0;j<megabot.intents[i].examples.size();j++){
      output << megabot.intents[i].examples[j].text << endl;
    }
  }
}

void exportOneIntent(ofstream &output, int pos, Chatbot &megabot){

  output << "#" << megabot.intents[pos].name << "#" << megabot.intents[pos].response << endl;
  for(unsigned int j=0;j<megabot.intents[pos].examples.size();j++){
    output << megabot.intents[pos].examples[j].text << endl;
  }
}

void exportData(Chatbot &megabot){

  ofstream output;
  string filename;
  string intentName;
  int pos = 0;
  char option;

  do{
    cout << "Save all intents [Y/N]?: ";
    cin >> option; cin.get();

    if(option == 'y' || option == 'Y'){
      cout << "Enter filename: ";
      getline(cin,filename);

      output.open(filename.c_str(), ios::out);
      if(output.is_open()){
        exportAllIntents(output, megabot);
        output.close();
      }
      else {
        error(ERR_FILE);
      }
    }
    if(option == 'n' || option == 'N'){
      cout << "Intent name: ";
      getline(cin,intentName);

      findIntent(megabot, intentName, pos);

      if(pos == -1){
        error(ERR_INTENT);
      }
      else{
        cout << "Enter filename: ";
        getline(cin,filename);
        output.open(filename.c_str(), ios::out);

        if(output.is_open()){
          exportOneIntent(output, pos, megabot);
          output.close();
        }
        else{
          error(ERR_FILE);
        }
      }
    }
  }while(option != 'y' && option != 'Y' && option != 'n' && option != 'N');
}

void readBin(ifstream &inB, Chatbot &megabot){

  BinChatBot binChat;
  BinIntent binI;
  Intent intent;
  Example e;
  char ejemplos[KMAXTEXTL];
  string exAux = "";

  inB.read((char *)&binChat,sizeof(BinChatBot));
  
  megabot.threshold = binChat.threshold;
  strcpy(megabot.similarity,binChat.similarity);

  for(unsigned int i=0;i<binChat.numIntents;i++){
    inB.read((char *)&binI,sizeof(BinIntent));
    intent.name = binI.name;
    intent.response = binI.response;

    for(unsigned int j=0;j<binI.numExamples;j++){
      inB.read((char*)&ejemplos,sizeof(char[KMAXTEXTL]));
      exAux = ejemplos;
      e.text = exAux;
      e.id = megabot.nextId;
      megabot.nextId++;
      normalizarCadena(exAux);
      e.tokens = separateWords(exAux);
      intent.examples.push_back(e);
      e.tokens.clear(); // Limpiar buffer.
    }
    megabot.intents.push_back(intent);
    intent.examples.clear();
  }
}

void LoadChatbot(Chatbot &megabot){

  ifstream inB;
  string binName;
  char option;

  cout << "Enter filename: ";
  getline(cin, binName);

  inB.open(binName.c_str(), ios::in | ios::binary);
  if(inB.is_open()){
    do{
      cout << "Confirm [Y/N]?: ";
      cin >> option; cin.get();

      if(option == 'y' || option == 'Y'){
        megabot.intents.clear();
        megabot.nextId = 1;
        readBin(inB, megabot);
      } 
    }while(option != 'y' && option != 'Y' && option != 'n' && option != 'N');
    inB.close();
  }
  else{
    error(ERR_FILE);
  }
}

void argLoad(Chatbot &megabot, string binName){

  ifstream inB;

  inB.open(binName.c_str(), ios::in | ios::binary);
  if(inB.is_open()){
    readBin(inB, megabot); 
    inB.close();
  }
  else{
    error(ERR_FILE);
  }
}

void saveInChatbot(ofstream &outB, Chatbot &megabot){

  BinChatBot binChat;
  BinIntent binI;
  char ejemplos[KMAXTEXTL];

  binChat.threshold = megabot.threshold;
  strcpy(binChat.similarity, megabot.similarity);
  binChat.numIntents = megabot.intents.size();
  outB.write((char *)&binChat,sizeof(BinChatBot));

  for(unsigned int i=0;i<megabot.intents.size();i++){
    strncpy(binI.name,megabot.intents[i].name.c_str(),KMAXTEXTS-1);
    binI.name[KMAXTEXTS-1] = '\0';
    strcpy(binI.response,megabot.intents[i].response.c_str());
    binI.numExamples = megabot.intents[i].examples.size();
    outB.write((char *)&binI,sizeof(BinIntent));

    for(unsigned int j=0;j<megabot.intents[i].examples.size();j++){
      strcpy(ejemplos, megabot.intents[i].examples[j].text.c_str());
      outB.write((char *)&ejemplos,sizeof(char[KMAXTEXTL]));
    }
  }
}

void SaveChatbot(Chatbot &megabot){

  ofstream outB;
  string binName;

  cout << "Enter filename: ";
  getline(cin,binName);

  outB.open(binName.c_str(), ios::out | ios::binary);

  if(outB.is_open()){
    saveInChatbot(outB, megabot);
    outB.close();
  }
  else {
    error(ERR_FILE);
  }
}

bool programArguments(Chatbot &megabot, int argc, char * argv[]){

  string sImport, sLoad;
  int contLoad = 0, contImp = 0, contTest = 0;
  string argI = "-i", argL = "-l", argT = "-t";
  bool checkImp = false, checkLoad = false, checkTest = false;

  for(int i=1;i<argc;i++){
    if(argv[i] != argI && argv[i] != argL && argv[i] != argT){
      error(ERR_ARGS);
      return false;
    }
    else{
      if(argv[i] == argI){
        if(i == argc-1){
          return false;
        }
        else{
          sImport = argv[i+1];
          checkImp = true;
          contImp++;
          i++;
        }
      }
      else if(argv[i] == argL){
        if(i == argc-1){
          return false;
        }
        else{
          sLoad = argv[i+1];
          checkLoad = true;
          contLoad++;
          i++;
        }
      }
      else if(argv[i] == argT){
        checkTest = true;
        contTest++;
      }
    }
  }
  if(contImp >= 2 || contLoad >= 2 || contTest >= 2){
    return false;
  }
  if(checkImp){
    argImport(megabot,sImport);
  }
  if(checkLoad){
    argLoad(megabot,sLoad);
  }
  if(checkTest){
    test(megabot);
  }
  return true;
}

int main(int argc, char * argv[]){
  Chatbot megabot;
  megabot.nextId=1;
  megabot.threshold=0.25;
  strcpy(megabot.similarity,"jc");
  srand(666);
  bool control = true;

  if(argc > 1) {
    control = programArguments(megabot, argc, argv);
  }
  if(control == true){
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
        case '4':
          configure(megabot);
          break;
        case '5':
          importData(megabot);
          break;
        case '6':
          exportData(megabot);
          break;
        case '7':
          LoadChatbot(megabot);
          break;
        case '8':
          SaveChatbot(megabot);
          break;
        case 'q':
          break;
        default:
          error(ERR_OPTION);
      }
    }while(option!='q');
  }
  else{
    error(ERR_ARGS);
  }
  return 0;
}