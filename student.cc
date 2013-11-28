#ifndef STUDENT_CC_CS343
#define STUDENT_CC_CS343 

#include "student.h"

void Student::main() {

}

Student::Student( Printer &prt, NameServer &nameServer, 
	WATCardOffice &cardOffice, unsigned int id, unsigned int maxPurchases )
		: prt(prt), nameServer(nameServer), cardOffice(cardOffice), id(id), maxPurchases(maxPurchases) {}

Student::~Student() {
	
}

#endif
