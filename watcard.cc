#ifndef WATCARD_CC_CS343
#define WATCARD_CC_CS343 

#include "watcard.h"

WATCard::WATCard( const WATCard & w) : mBalance(w.mBalance) {}            // prevent copying

WATCard & WATCard::operator=( const WATCard & w) {
	this->mBalance = w.mBalance;
	return *this;
}

WATCard::WATCard() : mBalance(0) {}


void WATCard::deposit( unsigned int amount ){
	this->mBalance += amount;
}

void WATCard::withdraw( unsigned int amount ){
	this->mBalance -= amount;
	assert(this->mBalance >= 0);
}

unsigned int WATCard::getBalance() {
	return this->mBalance;
}

#endif
