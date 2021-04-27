/*
 * simulation.cpp is the main program running the simulation.
 *
 * Version:
 *     $Id: simulation.cpp,v 1.1 2007/10/16 15:24:29 jeg3600 Exp jeg3600 $
 *
 * Revisions:
 *     $Log: simulation.cpp,v $
 *     Revision 1.1  2007/10/16 15:24:29  jeg3600
 *     Initial revision
 *
 *
 */

#include <iostream>
#include <vector>
#include <errno.h>

using namespace std;

#include "ErieCanalMonitor.h"    // TODO: the monitor
#include "Car.h"                 // TODO: the threads

using namespace erie;

/**
 * The simulation program uses posix threads (pthreads) to 
 * simulate cars crossing the one-lane bridges on the Erie Canal.
 * <br>
 * This is a project on concurrent threads in C++.
 * <br>
 *
 * @author bksteele
 * @author John Garnham
 *
 * @param argc -- a count of the arguments supplied on the command line
 * @param argv -- should have only the program name and a file with a
 *                configuration of cars trying to cross.
 */
int main( int argc, char** argv ) {

    int numCars = 0;    // how many car threads to start?
    int numTrips = 0;   // how many trips will each make?

    long seed;

    int newId = 0;      // variable for setting new license plate numbers

    // seed the random number generator for car delays
    errno = 0;
    seed = time( 0 );
    if ( errno != 0 ) {
        perror( argv[0] );
        exit( 1 );
    }
    srand48( seed );

    /*
     * design issues:
     *          ? What if the inputs are bad? -- bail out with usage msg
     *
     * create the monitor that represents the shared, single lane bridge.
     *          ? what does the creation? where should it go?
     *
     * create the threads that simulate the cars.
     *          ? How are the cars created? -- one at a time
     *          ? What does that and where? -- here in main
     *          ? What if the threads don't build right? -- need to check!
     *
     * start the simulation
     *          ? what starts everything? -- main again
     *
     * end of program
     *          ? how does a program end under NORMAL conditions?
     *                -- ideally, there are no more cars to cross
     *                -- or, there are cars deadlocked to cross
     *                -- or, are there cars that starved trying to cross?
     *          ? how does main coordinate the end of simulation?
     *                -- 'gather up' the completed threads
     */

    if ( argc != 3 ) {
        fprintf( stderr,
            "Usage: %s numCars numberTrips\n", argv[0] );
        return -1;
    }

    cout << "The Erie Canal Bridge is opening..." << endl;

    ErieCanalMonitor canal;

    numCars = atoi( *++argv );
    numTrips = atoi( *++argv );
    assert( numCars > 0 );
    assert( numTrips > 0 );

    cout << "Simulating " << numCars
         << " cars each taking " << numTrips
         << " trips across the bridge.\n" ;

    // make the cars first
    vector<Car*> traffic;

    for ( int j = 0; j < numCars; j++ ) {

      // creating the car does not initiate its thread of execution.
     
      int direction = j % 2;

      
      Car* newCar = new Car(newId++, numTrips, direction, &canal);
      
      traffic.push_back(newCar);

      cout << "Created car " << j
	   << " arriving at side " << ((direction == 0) ? "North" : "South")
	   << endl;

    }

    // make the cars GO next
    for ( vector<Car*>::iterator iter = traffic.begin() ;
          iter != traffic.end(); iter++ ) {

      // start each car. initiate its thread of execution.

      (*iter)->start();

    }
  
    // wait for the cars to finish
    for ( vector<Car*>::iterator iter = traffic.begin() ;
          iter != traffic.end(); iter++ ) {

      int ret = pthread_join((*iter)->getMainThread(), NULL);

    }

    // Closing message
    cout << "\nClosing time. Say goodbye to the Erie Canal." << endl;

    // delete the cars at the end
    traffic.clear();

    // exiting main invokes all other destructors.
    return( 0 );

}; // main

