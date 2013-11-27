#include "parent.h"

void Parent::main() {

}

Parent::Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay )
	: mPrt(prt), mBank(bank), mNumStudents(numStudents), mParentalDelay(parentalDelay) {}

Parent::~Parent() {

}
