#ifndef WATCARD_CC_CS343
#define WATCARD_CC_CS343 

#include "watcard.h"


/***************** WATCard::WATCard ****************
 Purpose:   copy constructor 
 ***************************************************/
WATCard::WATCard( const WATCard & w) : mBalance(w.mBalance) {}            
// prevent copying


/***************** WATCard::operator= ****************
 Purpose:   constructor 

 Return:	WATCard &
 *****************************************************/
WATCard & WATCard::operator=( const WATCard & w) {
	this->mBalance = w.mBalance;
	return *this;
} // operator=

/***************** WATCard::WATCard ****************
 Purpose:   constructor 
 **************************************************/
WATCard::WATCard() : mBalance(0) {}


/******************** WATCard::deposit **********************
 Purpose:   The courier calls deposit after a funds transfer. 
 Return:	void
 ***********************************************************/
void WATCard::deposit( unsigned int amount ){
	this->mBalance += amount;
} // WATCard::deposit

/************************** WATCard::withdraw *************************
 Purpose:   A vending machine calls withdraw when a soda is purchased. 
 Return:	void
 **********************************************************************/
void WATCard::withdraw( unsigned int amount ){
	this->mBalance -= amount;
	assert(this->mBalance >= 0);
} // WATCard::withdraw

/******************* WATCard::getBalance ******************
 Purpose:   A student and a vending machine call getBalance 
 			to determine the balance.
 Return:	unsigned int
 *********************************************************/
unsigned int WATCard::getBalance() {
	return this->mBalance;
} // WATCard::getBalance

#endif
