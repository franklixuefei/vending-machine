#include "nameserver.h"



/***************** NameServer::main ********************
 Purpose:   The execution body of Administrator NameServer.
 ******************************************************/
void NameServer::main() {
  for(;;){
    _Accept (~NameServer) {
      break;
    } or _Accept (VMregister) {
      // after it has been registered it will increase the current counter
      mCurrentVendingMachineCounter ++;

    } or _Accept (getMachineList) {
    } or _Accept (getMachine) {
      // shift the student to the next machine
      mStudentVendingMachineID[mLastVisitedStudent] = 
      (mStudentVendingMachineID[mLastVisitedStudent]+1) % mNumVendingMachines;

    } 

  }

}


/***************** NameServer::NameServer ****************
 Purpose:   the constructor 
 ******************************************************/
NameServer::NameServer( Printer &prt, unsigned int numVendingMachines, unsigned int numStudents )
  :mPrt(prt),
  mNumVendingMachines(numVendingMachines),
  mNumStudents(numStudents), 
  mMachineList(new VendingMachine*[numVendingMachines]), 
  mStudentVendingMachineID(new unsigned int[mNumStudents]),
  mCurrentVendingMachineCounter(0) {

    mPrt.print(Printer::NameServer, 'S' );
    // assign each student to a machine
    for (unsigned int i = 0; i < mNumStudents; ++i) {
      mStudentVendingMachineID[i] = (i)%mNumVendingMachines;
    }
    // clear the array for placing vending machine
    for (unsigned int i = 0; i < numVendingMachines; ++i) {
        mMachineList[i] = NULL;
    }

}

/***************** NameServer::~NameServer ****************
 Purpose:   the destructor
 ******************************************************/
NameServer::~NameServer(){
  mPrt.print(Printer::NameServer, 'F' );
  delete[] mMachineList;
  delete[] mStudentVendingMachineID;
}


/***************** NameServer::VMregister ****************
 Purpose:   register the vending machine for student purchase
 return:    void
 ******************************************************/
void NameServer::VMregister( VendingMachine *vendingmachine ) {
  mPrt.print(Printer::NameServer, 'R', mCurrentVendingMachineCounter );
  mMachineList[mCurrentVendingMachineCounter] = vendingmachine;
}

/***************** NameServer::getMachine ******************
 Purpose:   get the vending machine a student should be using
 return:    the vending machine (VendingMachine *)
 **********************************************************/
VendingMachine *NameServer::getMachine( unsigned int id ) {
  mPrt.print(Printer::NameServer, 'N', id, mStudentVendingMachineID[id]);
  mLastVisitedStudent = id;
  VendingMachine * vm = mMachineList[mStudentVendingMachineID[id]];
  assert(vm != NULL);
  return vm;
}

/***************** NameServer::getMachineList ****************
 Purpose:   get a list of vending machines
 return:    the list of machine (VendingMachine *)
 ************************************************************/
VendingMachine **NameServer::getMachineList() {
  return mMachineList;
}


