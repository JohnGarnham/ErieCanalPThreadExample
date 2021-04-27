/**
 * Car.cpp
 *
 * Implementation for the Car class
 *
 * @version: $Id: Car.cpp,v 1.3 2007/10/28 22:38:15 jeg3600 Exp jeg3600 $
 *
 * @author: John Garnham
 *
 * Revisions:
 *     $Log: Car.cpp,v $
 *     Revision 1.3  2007/10/28 22:38:15  jeg3600
 *     Now passes in Monitor correctly.
 *
 *     Revision 1.2  2007/10/16 17:58:41  jeg3600
 *     Linked to monitor now
 *
 *     Revision 1.1  2007/10/16 15:41:05  jeg3600
 *     Initial revision
 *
 *
 */

#include <pthread.h>
#include <iostream>
#include "Car.h"

using namespace erie;

// The run method for the car's thread
void* drive(void* theCar);

/**
 * constructor
 * @param id    -- (license) number of car trying to cross
 * @param numTrips    -- number of trips across car will take
 * @param dir   -- the initial direction of the car
 * @param monitor -- a pointer to the erie canal monitor
 */
Car::Car(int id, int numTrips, int dir, ErieCanalMonitor* monitor) {

  // Set the license plate number
  license = id;

  // Set the number of trips that the car will take
  trips = numTrips;

  // Set the direction
  direction = dir;

  // Set up the monitor pointer
  bridgeMonitor = monitor;

}
 
 /**
  * start the car
  */
void Car::start() {

  // the thread return val
  int thd = 0;

  // Start the thread
  thd = pthread_create(&mainThread, NULL, drive, (void*) this);

}


/**
 * @return The license plate number
 */
int Car::getId() {
  return license;
}
  
void* drive(void* theCar) {

  // Grab the car
  Car* thisCar = (Car*) theCar;

  // Randomize the starting up of the cars
  usleep(rand() / 100);

  while(thisCar->getTrips() > 0) {
    
    // Cross the bridge
    thisCar->changeDirections();
    
    // Sleep 
    usleep(TURNAROUND_TIME);
    
    std::cout << "Car " << thisCar->getId() << " is now changing directions."
	      << std::endl;
  }

  std::cout << "Car " << thisCar->getId() << " has finished." << std::endl;

}

/**
 * change directions
 *
 */
void Car::changeDirections() {

  // Change directions
  if (direction == 0) {
    bridgeMonitor->crossToNorth(license);
    direction = 1;
  } else {
    bridgeMonitor->crossToSouth(license);
    direction = 0;
  }

  // Decrement the number of trips the car needs to take
  trips--;

}

/**
 * @return The number of trips left
 *
 */
int Car::getTrips() {
  return trips;
}

pthread_t Car::getMainThread() {
  return mainThread;
}

/**
 * Deconstructor
 *
 */
Car::~Car() { 

}
