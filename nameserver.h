#ifndef __NAMESERVER_H__
#define __NAMESERVER_H__

#include "global.h"
#include "printer.h"

_Task VendingMachine;

_Task NameServer {
    void main();
  public:
    NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents );
    ~NameServer();
    void VMregister( VendingMachine *vendingmachine );
    VendingMachine *getMachine( unsigned int id );
    VendingMachine **getMachineList();

private:
    Printer &mPrt;
    unsigned int mNumVendingMachines;
    unsigned int mNumStudents;

    unsigned int mCycleCount;
    VendingMachine ** mMachineList;
    unsigned int * mStudentVendingMachineID;
    unsigned int mCurrentVendingMachineCounter;

    unsigned int mLastVisitedStudent;

};

#endif /* __NAMESERVER_H__ */