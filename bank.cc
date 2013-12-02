#ifndef BANK_CC_CS343
#define BANK_CC_CS343 

#include "bank.h"

/******************************** Bank::Bank ******************************
 Purpose:   the constructor for Monitor Bank.
 			Each student’s account initially starts with a balance of $0.
 **************************************************************************/
Bank::Bank( unsigned int numStudents ) 
: mNumStudents(numStudents), mSuffFund(new uCondition[mNumStudents]), mAccountBal(new int[mNumStudents]) {
	for (unsigned int i = 0; i < mNumStudents; ++i) {
		this->mAccountBal[i] = 0;
	} // for
} // Bank::Bank


/****************************** Bank::deposit *****************************
 Purpose:   The parent calls deposit to endow gifts to a specific student.
 return:  	void
 **************************************************************************/
void Bank::deposit( unsigned int id, unsigned int amount ){
	if ((this->mAccountBal[id] += amount) >= 0) {
		this->mSuffFund[id].signal();
	} // if
} // Bank::deposit


/********************************** Bank::withdraw ********************************
 Purpose:   A courier calls withdraw to transfer money on behalf of the 
 			WATCard office for a specific student. The courier waits until enough 
 			money has been deposited, which may require multiple deposits.
 return:  	void
 **********************************************************************************/
void Bank::withdraw( unsigned int id, unsigned int amount ){
	if ((this->mAccountBal[id] -= amount) < 0) {
		this->mSuffFund[id].wait();
		if (this->mAccountBal[id] >= 0) {
			this->mSuffFund[id].signal();
		} // if
	} // if
} // Bank::withdraw


/*************************** Bank::~Bank ************************
 Purpose:   the destructor for Monitor Bank
 ****************************************************************/
Bank::~Bank() {
	delete [] this->mAccountBal;
	delete [] this->mSuffFund;
} // Bank::~Bank

#endif
