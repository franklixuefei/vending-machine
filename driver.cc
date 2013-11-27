#ifndef DRIVER_CC_CS343
#define DRIVER_CC_CS343

#include <iostream>
#include "global.h"
#include "config.h"

using namespace std;

// This is the exit With usage function
void printUsage (string msg = "Usage: ./phil [ philosophers (> 1) [ noodles (> 0) [ Seed (> 0) ] ] ]"){
  cerr << "Usage: " << msg << endl;
  exit(1);
}

// This is exit with Error Function
void printError(string s = "") {
  cerr << "Error: " << s << endl;
  exit(1);
}

MPRNG RANDOM;


void uMain::main(){
  // creating init values
	string fileName;
	int Seed;
  // reading arguments from argument to program
  switch (argc){
    case 3:
    {
      try{
        // Converting argument into numbers
        Seed = atoi(argv[2]);
        if (Seed <= 0) {
          printUsage();
        }
      }catch(std::exception const & e){
          printUsage();
      }
    }
    case 2:
    {
    	fileName = argv[1];

		// m_fileStream.open(fileName.c_str());
		// if (!m_fileStream.good()){
		// 	printError ("could not open input file " + fileName);
		// }
    }
    break;
    case 1:
    break;
    default:
    break;
  }
  // set a random seed to generator
  RANDOM.seed(Seed);


  // uProcessor p[ numOfPhilosophers + 1 ] __attribute__(( unused ));

  // create printer 

}


#endif