#ifndef __PRINTER_H__
#define __PRINTER_H__

#include "global.h"
#include <iostream>
#include <cassert>

_Cormonitor Printer {
	void main();
public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    ~Printer();
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
private:

  void _printHeader();
  void _flashMap(bool isDotFlash = false);
  void _insertData();
  bool _canInsertData();
  unsigned int _upperRangTranslation(unsigned int k);

	unsigned int mNumStudents;
	unsigned int mNumVendingMachines;
	unsigned int mNumCouriers;
	unsigned int mKind;
	unsigned int mLid;
	char mState;
	int mValue1;
	int mValue2;

  std::map<unsigned int , 
            std::map< unsigned int , 
                      pair<char, 
                            pair<unsigned int , unsigned int > 
                          > 
                    > 
          > mDataMap;
};

#endif /* __PRINTER_H__ */