#include "parent.h"

void Parent::main() {
  for (;;){
    // The parent must check for a call to its destructor to know when to terminate. 
    _Accept(~Parent){
      break;
    } _Else {
      // Before each gift is transfered, the parent yields for parentalDelay times (not random). 
      yield( mParentalDelay );

      unsigned int studentID = RANDOM(mNumStudents-1);
      unsigned int amount = RANDOM(0, 3);
      // The Parent task periodically gives a random amount of money [$1, $3] to a random student. 
      mBank.deposit(studentID, amount);
      // Since it must not block on this call, it is necessary to use a terminating
      // Else on the accept statement. (Hence, the parent is busy waiting for the call to its destructor.)
      mPrt.print( Printer::Parent, 'D', studentID, amount );

    }
  }
}



Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay )
	: mPrt(prt), mBank(bank), mNumStudents(numStudents), mParentalDelay(parentalDelay) {

  mPrt.print(Printer::Parent, 'S');
}

Parent::~Parent() {
    mPrt.print(Printer::Parent, 'F');
}