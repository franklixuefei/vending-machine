#ifndef WATCARDOFFICE_H_CS343
#define WATCARDOFFICE_H_CS343 


#include "bank.h"
#include "printer.h"
#include "watcard.h"


_Task WATCardOffice {
    struct Job {                           // marshalled arguments and return future
        // Args args;                         // call arguments (YOU DEFINE "Args")
        int args; // FIXME
        WATCard::FWATCard result;                   // return future
        // Job( Args args ) : args( args ) {}
        Job( int args ) : args( args ) {} // FIXME
    };
    _Task Courier { /*...*/ };                 // communicates with bank

    void main();
  public:
    _Event Lost {};                        // uC++ exception type, like "struct"
    WATCardOffice( Printer &prt, Bank &bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount );
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard *card );
    Job *requestWork();
};

#endif
