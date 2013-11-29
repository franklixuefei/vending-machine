#ifndef WATCARD_CC_CS343
#define WATCARD_CC_CS343 

#include "watcard.h"

WATCard::WATCard( const WATCard & w) : balance(w.balance) {}            // prevent copying

WATCard & WATCard::operator=( const WATCard & w) {
	this->balance = w.balance;
	return *this;
}

WATCard::WATCard() : balance(0) {}


void WATCard::deposit( unsigned int amount ){
	this->balance += amount;
}

void WATCard::withdraw( unsigned int amount ){
	this->balance -= amount;
	assert(this->balance >= 0);
}

unsigned int getBalance() {
	return this->balance;
}

#endif
