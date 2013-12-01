#include <iostream>
#include "q2table.h"
using namespace std;

/***************** Table::getLeftEater ****************
 Purpose:   gets the ID of the philosopher that is to the
 			right of current philosopher.
 return:	Philosopher's ID (unsigned int)
 ******************************************************/
unsigned int Table::getLeftEater(unsigned int id) {
	if (id == 0) return numPhils - 1;
	return id - 1;
}

/***************** Table::getLeftEater ****************
 Purpose:   gets the ID of the philosopher that is to the
 			left of current philosopher.
 return:	Philosopher's ID (unsigned int)
 ******************************************************/
unsigned int Table::getRightEater(unsigned int id) {
	if (id == numPhils - 1) return 0;
	return id + 1;
}
