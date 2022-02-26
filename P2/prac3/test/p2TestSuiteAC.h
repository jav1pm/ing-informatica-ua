#include <cxxtest/TestSuite.h>
#include "Auxiliar.h"

#include <iostream>
using namespace std;

#include "Chatbot.h"
#include "Intent.h"
#include "Example.h"
#include "Util.h"

#include <iostream>

using namespace std;

// Tests for Util ----------------------------------------------------------

class UtilTestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  void testUtil() {
    string str1 = Util::welcome();
    string str2 = Util::welcome();
    TS_ASSERT_EQUALS(str1, "Buenas");
    TS_ASSERT_EQUALS(str2, "¡Hola! Soy Megabot 3000. ¿En qué puedo ayudarte?");

    vector<string> tokens = Util::extractTokens("Hola cómo estás;..");
    TS_ASSERT_EQUALS(tokens.size(), 3);
    TS_ASSERT_EQUALS(tokens[0], "hola");
    TS_ASSERT_EQUALS(tokens[1], "como");
    TS_ASSERT_EQUALS(tokens[2], "esta");
  }

};

// Tests for Example ----------------------------------------------------------

class ExampleTestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  void testExample() {

    // ResetNextId    
    Example::resetNextId();

    // Constructor
    const Example e1("Hola cómo estás?");
        
    // Getters
    TS_ASSERT_EQUALS(e1.getId(),1);
    TS_ASSERT_EQUALS(e1.getText(),"Hola cómo estás?");

    vector<string> tke1 = e1.getTokens();
    TS_ASSERT_EQUALS(tke1[0],"hola");
    TS_ASSERT_EQUALS(tke1[1],"como");
    TS_ASSERT_EQUALS(tke1[2],"esta");
    
    // << operator
    stringstream ss;
    ss << e1;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Example 1: Hola cómo estás?\nTokens 1:<hola> <como> <esta>"));
    
    // similarity
    float j = e1.jaccardSimilarity("Cómo estás, afirmo");
    TS_ASSERT_DELTA(j,0.50,0.001);
    

    float ng = e1.ngramSimilarity("Cómo estás, afirmo");
    TS_ASSERT_DELTA(ng,0.40,0.001);

    // Constructor with exception
    TS_ASSERT_THROWS_ASSERT(new Example(" "), const Error &e, TS_ASSERT_EQUALS(e, ERR_EMPTY));
  }

};

// Tests for Intent ----------------------------------------------------------

class IntentTestSuiteAC : public CxxTest::TestSuite, public Auxiliar {
  
 public:
  
  void testIntent() {
    string name = "vacaciones";
    string response = "Con el coronavirus no hay vacaciones";
    
    // Constructor
    Intent intent(name);

    intent.addResponse(response);

    // Getters
    TS_ASSERT_EQUALS(intent.getName(), name);
    TS_ASSERT_EQUALS(intent.getResponse(), response);

    Example::resetNextId();   // nextId=1
    Example ex1("Cuándo son las vacaciones de navidad?");
    Example ex2("Qué día nos damos el piro en Navidad?");

    intent.addExample(ex1);
    intent.addExample(ex2);
    TS_ASSERT_EQUALS(intent.getExamples().size(), 2);

    float s_jc = intent.calculateSimilarity("Cuándo empiezan las vacaciones navideñas?", "jc");
    float s_ng = intent.calculateSimilarity("Cuándo empiezan las vacaciones navideñas?", "ng");

    TS_ASSERT_DELTA(s_jc,0.375,0.001);
    TS_ASSERT_DELTA(s_ng,0.538,0.001);

    TS_ASSERT_THROWS_ASSERT(intent.deleteExample(ex1.getId()+42), const Error &e, TS_ASSERT_EQUALS(e, ERR_EXAMPLE));
    TS_ASSERT_EQUALS(intent.getExamples().size(), 2);

    intent.deleteExample(ex1.getId());
    TS_ASSERT_EQUALS(intent.getExamples().size(), 1);


    stringstream ss;
    ss << intent;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Intent: vacaciones\nResponse:Con el coronavirus no hay vacaciones\nExample 2:Qué día nos damos el piro en Navidad?\nTokens 2:<que> <dia> <no> <damo> <el> <piro> <en> <navidad>"));
  }
};

// Tests for Chatbot -----------------------------------------------------------

// class for accessing Chatbot protected methods

class ChatbotCo: public Chatbot {

  public:
  
    ChatbotCo():Chatbot()
    {
    }
    
    ChatbotCo(float threshold,const char similarity[]):Chatbot(threshold,similarity)
    {
    }
    
    int srchIntent(string name) const  { return searchIntent(name); }
    
    string bstResponse(string query,bool debug) const
    {
      return bestResponse(query,debug);
    }
    
  friend ostream& operator<< (ostream& os,const ChatbotCo &cb)
  {
    Chatbot c=cb;
    return os << c ;
  }
};


class ChatbotTestSuiteAC : public CxxTest::TestSuite, public Auxiliar {

 public:

  void testChatbot() {

    // Default constructor
    ChatbotCo megabot;
    TS_ASSERT_DELTA(megabot.getThreshold(),0.25,0.001);
    TS_ASSERT_EQUALS(megabot.getSimilarity(),"jc");
    
    
    // Constructor with parameters
    ChatbotCo ultrabot(0.15,"ng");
    
    // Constructor with parameters (exceptions)
    TS_ASSERT_THROWS_ASSERT(new Chatbot(0.25,"jjjjjj"), const Error &e, TS_ASSERT_EQUALS(e, ERR_SIMILARITY));
    TS_ASSERT_THROWS_ASSERT(new Chatbot(1.5,"jc"), const Error &e, TS_ASSERT_EQUALS(e, ERR_THRESHOLD));
    
    
    // addIntent
    Intent vacaciones("vacaciones"), cordial("cordial");
    
    TS_ASSERT_EQUALS(megabot.addIntent(&vacaciones),true);
    TS_ASSERT_EQUALS(megabot.addIntent(&cordial),true);

    TS_ASSERT_EQUALS(megabot.srchIntent("vacaciones"),0);
    TS_ASSERT_EQUALS(megabot.srchIntent("cordial"),1);
    TS_ASSERT_EQUALS(megabot.srchIntent("esta intent no existe"),-1);
    
    // deleteIntent
    TS_ASSERT_EQUALS(megabot.deleteIntent("vacaciones",false),true);
    
    
    // addResponse + operator<<
    TS_ASSERT_EQUALS(megabot.addResponse("cordial","No tan bien como tú"),true);

    stringstream ss;
    ss << megabot;
    TS_ASSERT_EQUALS(rmb(convertSS(ss)),rmb("Similarity: Jaccard\nThreshold: 0.25\nIntent: cordial\nResponse: No tan bien como tú\nTotal intents: 1\nTotal examples: 0\nExamples per intent: 0"));

        
    // addExample
    Example::resetNextId();   // nextId=1

    istringstream in_stream;
    ostringstream out_stream;
    
    in_stream.str("¿Qué tal estás, Megabot?\n¿Estás bien?\nq\n");
    out_stream.str("");
    redirectStreams(in_stream,out_stream);
    
    TS_ASSERT_EQUALS(megabot.addExample("cordial"),true);
    
    restoreStreams();
    stringstream ssaE;
    ssaE << megabot;
    TS_ASSERT_EQUALS(rmb(convertSS(ssaE)),rmb("Similarity: Jaccard\nThreshold: 0.25\nIntent: cordial\nResponse: No tan bien como tú\nExample 1: ¿Qué tal estás, Megabot?\nTokens 1:<que> <tal> <esta> <megabot>\nExample 2: ¿Estás bien?\nTokens 2:<esta> <bien>\nTotal intents: 1\nTotal examples: 2\nExamples per intent: 2"));

    // bestResponse
    TS_ASSERT_EQUALS(megabot.bstResponse("¿Cómo estás?",false),"No tan bien como tú");
    TS_ASSERT_THROWS_ASSERT(megabot.bstResponse("Estoy fatal, tío",false), const Error &e, TS_ASSERT_EQUALS(e, ERR_RESPONSE));
    
    // test
    in_stream.str("¿Qué tal vas?\nq\n");
    out_stream.str("");
    redirectStreams(in_stream,out_stream);
    
    megabot.test(true);
    
    restoreStreams();
    string outTest = out_stream.str();

    size_t open = outTest.find("(");
    size_t close = outTest.find(")");
    string leftstr=outTest.substr(0, open+1);
    string rightstr=outTest.substr(close);
    float sim = stof(outTest.substr(open+1, close-open));

    TS_ASSERT_EQUALS(rmb(leftstr),rmb(">>Bonito día para ser Megabot 3000\n<<\n\n>>("));
    TS_ASSERT_EQUALS(rmb(rightstr),rmb(") No tan bien como tú\n<<\n"));
    TS_ASSERT_DELTA(sim,0.4,0.01);
    //TS_ASSERT_EQUALS(rmb(outTest),rmb(">>Bonito día para ser Megabot 3000\n<<\n\n>>(0.4) No tan bien como tú\n<<\n"));

    // deleteExample
    TS_ASSERT_EQUALS(megabot.deleteExample(2),true);
    
    stringstream ssdE;
    ssdE << megabot;
    TS_ASSERT_EQUALS(rmb(convertSS(ssdE)),rmb("Similarity: Jaccard\nThreshold: 0.25\nIntent: cordial\nResponse: No tan bien como tú\nExample 1: ¿Qué tal estás, Megabot?\nTokens 1:<que> <tal> <esta> <megabot>\nTotal intents: 1\nTotal examples: 1\nExamples per intent: 1"));

    
    // configure
    in_stream.str("¿Qué tal vas?\nq\n");
    out_stream.str("");
    redirectStreams(in_stream,out_stream);
    
    megabot.configure(1.1,"jg");
    
    restoreStreams();
    string cfgTest = out_stream.str();
    TS_ASSERT_EQUALS(rmb(cfgTest),rmb("ERROR: the threshold value must be between 0 and 1\nERROR: valid values are \"jc\" (Jaccard) and \"ng\" (n-grams)\n"));
  }

};
