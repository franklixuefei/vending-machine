#ifndef __PRINTER_H__
#define __PRINTER_H__

_Cormonitor Printer {
	unsigned int mNumStudents;
	unsigned int mNumVendingMachines;
	unsigned int mNumCouriers;
	
  public:
    enum Kind { Parent, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, int value1 );
    void print( Kind kind, char state, int value1, int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, int value1 );
    void print( Kind kind, unsigned int lid, char state, int value1, int value2 );
};

#endif /* __PRINTER_H__ */