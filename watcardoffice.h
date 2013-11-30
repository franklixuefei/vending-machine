#ifndef WATCARDOFFICE_H_CS343
#define WATCARDOFFICE_H_CS343 


#include "bank.h"
#include "printer.h"
#include "watcard.h"
using namespace std;

_Task WATCardOffice {
    struct Args {
        WATCard *mCard;
        unsigned int mId;
        unsigned int mTransAmount;
    };
    struct Job {                           // marshalled arguments and return future
        Args args;                         // call arguments (YOU DEFINE "Args")
        WATCard::FWATCard result;                   // return future
        Job( Args args ) : args( args ) {}
    };
    _Task Courier {
        void main();
        WATCardOffice &mOffice;
        Bank &mBank;
        unsigned int mId;
    public:
        Courier(WATCardOffice &office, Bank &bank, unsigned int id);
     }; // communicates with bank

    void main();
    Printer &mPrinter;
    Bank &mBank;
    unsigned int mNumCouriers;
    Courier **mCouriers;
    uCondition workRequest;
    queue<Job*> jobs;
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
