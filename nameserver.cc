#include "nameserver.h"



void NameServer::main() {

/*  
  The NameServer is an administrator task used to manage the vending-machine names. 
  The name server is passed the number of vending machines, NumVendingMachines, and the number of students, NumStudents.
  It begins by logically distributing the students evenly across the vending machines in a round-robin fashion.
  That is, student id 0 is assigned to the first registered vending-machine, student id 1 is assigned to the second
  registered vending-machine, etc., 
  until there are no more registered vending-machines, and then start again with the first registered vending-machine. 
  Vending machines call VMregister to register themselves so students can subsequently locate them. 
  A student calls getMachine to find a vending machine, and the name server must
  cycle through the vending machines separately for each student starting from the initial position via modulo
  incrementing to ensure a student has a chance to visit every machine. The truck calls getMachineList to obtain
  an array of pointers to vending machines so it can visit each machine to deliver new soda.
  */
  for(;;){
    _Accept (~NameServer) {
      break;
    } _Accept (VMregister) {
      mCurrentVendingMachineCounter ++;

    } _Accept (getMachine) {
      mStudentVendingMachineID[mLastVisitedStudent] = (mStudentVendingMachineID[mLastVisitedStudent]+1) % mNumVendingMachines;

    } _Accept (getMachineList) {

    }

  }

}

NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents )
  :mPrt(prt),
  mNumVendingMachines(numVendingMachines),
  mNumStudents(numStudents), 
  mCycleCount(0),
  mMachineList(new VendingMachine*[numVendingMachines]), 
  mStudentVendingMachineID(new unsigned int[mNumStudents]),
  mCurrentVendingMachineCounter(0) {

    mPrt.print(Printer::NameServer, 'S' );
    for (unsigned int i = 0; i < mNumStudents; ++i) {
      mStudentVendingMachineID[i] = (i)%mNumVendingMachines;
    }

}


NameServer::~NameServer(){
  delete[] mMachineList;
  delete[] mStudentVendingMachineID;
}

void NameServer::VMregister( VendingMachine *vendingmachine ) {
  mPrt.print(Printer::NameServer, 'R', mCurrentVendingMachineCounter );
  mMachineList[mCurrentVendingMachineCounter] = vendingmachine;
}


VendingMachine *NameServer::getMachine( unsigned int id ) {
  mPrt.print(Printer::NameServer, 'N', id, mStudentVendingMachineID[id]);
  mLastVisitedStudent = id;
  return mMachineList[mStudentVendingMachineID[id]];
}


VendingMachine **NameServer::getMachineList() {
  return mMachineList;
}


