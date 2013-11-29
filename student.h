#ifndef STUDENT_H_CS343
#define STUDENT_H_CS343 

#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"
#include "vendingmachine.h"

_Task Student {
    void main();
    Printer &mPrinter;
    NameServer &mNameServer;
    WATCardOffice &mCardOffice;
    unsigned int mId;
    unsigned int mMaxPurchases;
    WATCard *mCard;
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases );
    ~Student();
};

#endif
