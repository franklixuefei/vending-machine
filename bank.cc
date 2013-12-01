#ifndef BANK_CC_CS343
#define BANK_CC_CS343 

#include "bank.h"

Bank::Bank( unsigned int numStudents ) 
: mNumStudents(numStudents), mSuffFund(new uCondition[mNumStudents]), mAccountBal(new int[mNumStudents]) {
	for (unsigned int i = 0; i < mNumStudents; ++i) {
		this->mAccountBal[i] = 0;
	}
}


void Bank::deposit( unsigned int id, unsigned int amount ){
	if ((this->mAccountBal[id] += amount) >= 0) {
		this->mSuffFund[id].signal();
	}
}


void Bank::withdraw( unsigned int id, unsigned int amount ){
	if ((this->mAccountBal[id] -= amount) < 0) {
		this->mSuffFund[id].wait();
		if (this->mAccountBal[id] >= 0) {
			this->mSuffFund[id].signal();
		}
	}
}

Bank::~Bank() {
	delete [] this->mAccountBal;
	delete [] this->mSuffFund;
}

#endif
