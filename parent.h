#ifndef __PARENT_H__
#define __PARENT_H__

#include "global.h"
#include "printer.h"
#include "bank.h"

_Task Parent {
    void main();
  public:
    Parent( Printer &prt, Bank &bank, unsigned int numStudents, unsigned int parentalDelay );
};

#endif /* __PARENT_H__ */
