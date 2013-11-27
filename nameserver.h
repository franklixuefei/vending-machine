#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "global.h"
#include "vendingmachine.h"

_Task NameServer {
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();
};

#endif /* __NAMESERVER_H__ */