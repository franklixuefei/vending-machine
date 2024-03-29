#include <uC++.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "global.h"
#include "config.h"
#include "printer.h"
#include "student.h"
#include "bank.h"
#include "nameserver.h"
#include "bottlingplant.h"
#include "watcardoffice.h"
#include "vendingmachine.h"
#include "parent.h"

using namespace std;

/********************** usage *************************
 Purpose:   prints out the usage message and terminates
      the problem with exit code 1.
 
 Returns:   void
 ******************************************************/
void usage(string s = "./soda [ config-file [ random-seed ] ]") {
  cerr << "Usage: " << s << endl;
  exit(1);
} // usage

/********************** error *************************
 Purpose:   prints out the error message and terminates
      the problem with exit code 1.
 
 Returns:   void
 ******************************************************/
void error(string s = "") {
  cerr << "Error: " << s << endl;
  exit(1);
} // error

/* global variable */
MPRNG RANDOM;


/********************** uMain::main *************************
 Purpose:   the driver for Vending Machine problem. This method
            parses the command line input, process config file,
            handles error input, creates Printer, Bank, Parent,
            WATCardOffice, NameServer, VendingMachines, 
            BottlingPlant, and Students.
 
 Returns:   void
 ************************************************************/
void uMain::main(){
  // creating init values
    string configFile = "soda.config";
    unsigned int seed = getpid();
    // reading arguments from argument to program
    switch (argc) {
        case 3:
          seed = (unsigned int)atol(argv[2]);
        case 2:
        	configFile = argv[1];
        default:
        break;
    } // switch
    if ((int)seed <= 0) {
        usage();
    } // if
    ConfigParms cparms;
    // set a random seed to generator
    RANDOM.seed(seed);          
    processConfigFile(configFile.c_str(), cparms);

    Printer printer(cparms.numStudents, cparms.numVendingMachines, cparms.numCouriers);
    Bank bank(cparms.numStudents);
    Parent parent(printer, bank, cparms.numStudents, cparms.parentalDelay);
    WATCardOffice wco(printer, bank, cparms.numCouriers);
    NameServer ns(printer, cparms.numVendingMachines, cparms.numStudents);
    VendingMachine *vms[cparms.numVendingMachines];
    for (unsigned int i = 0; i < cparms.numVendingMachines; ++i) {
        vms[i] = new VendingMachine(printer, ns, i, cparms.sodaCost, cparms.maxStockPerFlavour);
    }
    BottlingPlant *botPlant = new BottlingPlant(printer, ns, cparms.numVendingMachines, cparms.maxShippedPerFlavour, cparms.maxStockPerFlavour, cparms.timeBetweenShipments);
    Student * students[cparms.numStudents];
    for (unsigned int i = 0; i < cparms.numStudents; ++i) {
        students[i] = new Student(printer, ns, wco, i, cparms.maxPurchases);
    } // for

    for (unsigned int i = 0; i < cparms.numStudents; ++i) {
        delete students[i];
    } // for
    delete botPlant;
    for (unsigned int i = 0; i < cparms.numVendingMachines; ++i) {
        delete vms[i];
    } // for
    
    uRetCode = 0;
} // uMain::main