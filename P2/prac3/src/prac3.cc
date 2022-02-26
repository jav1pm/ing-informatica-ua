#include <iostream>
#include <vector>
#include <cstdlib>
#include "Chatbot.h"
#include "Intent.h"
#include "Util.h"

using namespace std;

void showTrainMenu(){
  cout << "1- Add intent" << endl
       << "2- Delete intent" << endl
       << "3- Add example" << endl
       << "4- Delete example" << endl
       << "5- Add response" << endl
       << "b- Back to main menu" << endl
       << "Option: ";
}

void train(Chatbot &megabot,vector<Intent*> &intents){
  char option;
    
  do{
    showTrainMenu();
    cin >> option;
    cin.get();
        
    switch (option){ 
      case '1': // Add intent
        try{
          string name;
          cout << "Intent name: ";
          getline(cin,name);
          Intent *newIntent=new Intent(name);
          // Añadimos el nuevo Intent al vector "intents" pasado como parámetro
          // De esta manera, aunque se destruya el "Chatbot" las intenciones seguirán existiendo en este vector
          // Esto se hace porque existe una relación de "agregación" entre Intent y Chatbot
          intents.push_back(newIntent);
          megabot.addIntent(newIntent);
        }
        catch(Error e){
          Util::error(e);
        }
        break;
      case '2': // Delete intent
        megabot.deleteIntent();
        break;
      case '3': // Add example
        megabot.addExample();
        break;
      case '4': // Delete example
        megabot.deleteExample();
        break;
      case '5': // Add response
        megabot.addResponse();
        break;
      case 'b': // Back to main menu
        break;
      default: // Error
        Util::error(ERR_OPTION); 
        break;
    }
  }while(option!='b');  
}

void showMainMenu(){
    cout << "1- Train" << endl
         << "2- Test" << endl
         << "3- Report" << endl
         << "4- Configure" << endl
         << "q- Quit" << endl
         << "Option: " ;
}

int main(int argc,char *argv[]){
  // Hay una relación de agregación entre "Chatbot" e "Intent"
  // Por esta razón definimos un vector "intents" aquí, para que las intenciones no se destruyan si se destruye el chatbot
  vector<Intent*> intents;
  Chatbot megabot;
  
  srand(666);
  char option;

  do{
    showMainMenu();
    cin >> option;
    cin.get();
        
    switch(option){ 
      case '1': // Train
        train(megabot,intents);
        break;
      case '2': // Test
        megabot.test();
        break;
      case '3': // Report
        cout << megabot << endl;
        break;
      case '4': // Configure
        megabot.configure();
        break;
      case 'q': // Quit
        break;
      default: // Error
        Util::error(ERR_OPTION);
    }
  }while(option!='q');
  
  return 0;
}
