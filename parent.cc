#include "parent.h"


/******************************************** Parent::main ********************************************
 Purpose:   
  - The Parent task periodically gives a random amount of money [$1, $3] to a random student.

  • yield for parentalDelay times
  • start message
  • loop
    – The parent must check for a call to its destructor to know when to terminate. 
    – ince it must not block on this call, it is necessary to use a terminating
      Else on the accept statement.
  • finished message
 
 Returns:   void
 ******************************************************************************************************/
void Parent::main() {
    mPrt.print(Printer::Parent, 'S');
    for (;;) {
        // The parent must check for a call to its destructor to know when to terminate
        _Accept(~Parent) {
            break;
        } _Else {
            // Before each gift is transfered, the parent yields for parentalDelay times (not random). 
            yield( mParentalDelay );
            unsigned int studentID = RANDOM(mNumStudents-1);
            unsigned int amount = RANDOM(1,3);
            // The Parent task periodically gives a random amount of money [$1, $3] to a random student. 
            mBank.deposit(studentID, amount);
            mPrt.print( Printer::Parent, 'D', studentID, amount );
        } // _Accept
        // Since it must not block on this call, it is necessary to use a terminating
        // Else on the accept statement. (Hence, the parent is busy waiting for the
        // call to its destructor.)    
    } // for
    mPrt.print(Printer::Parent, 'F');
} // Parent::main


/****************** Parent::Parent ********************
 Purpose:   the constructor 
 ******************************************************/
Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay )
: mPrt(prt), mBank(bank), mNumStudents(numStudents), mParentalDelay(parentalDelay) {}

/******************* Parent::~Parent ******************
 Purpose:   the destructor
 ******************************************************/
Parent::~Parent() {}
