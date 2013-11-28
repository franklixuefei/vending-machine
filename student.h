#ifndef STUDENT_H_CS343
#define STUDENT_H_CS343 

#include "printer.h"
#include "nameserver.h"
#include "watcardoffice.h"

_Task Student {
    void main();
    Printer &prt;
    NameServer &nameServer;
    WATCardOffice &cardOffice;
    unsigned int id;
    unsigned int maxPurchases;
  public:
    Student( Printer &prt, NameServer &nameServer, WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases );
    ~Student();
};

#endif
