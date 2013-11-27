#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "global.h"
#include "printer.h"
// #include "vendingmachine.h"

_Task VendingMachine;

_Task NameServer {
    void main() {

    }
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents ) {

    }
    void VMregister( VendingMachine *vendingmachine ) {

    }
    VendingMachine *getMachine( unsigned int id ) {
    	return NULL;
    }
    VendingMachine **getMachineList() {
    	return NULL;
    }
};

#endif /* __NAMESERVER_H__ */