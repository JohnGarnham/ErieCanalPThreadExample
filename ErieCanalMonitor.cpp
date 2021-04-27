/*
 * ErieCanalMonitor.cpp
 *
 * Version:
 *     $Id: ErieCanalMonitor.cpp,v 1.2 2007/10/28 22:38:43 jeg3600 Exp jeg3600 $
 *
 * Revisions:
 *     $Log: ErieCanalMonitor.cpp,v $
 *     Revision 1.2  2007/10/28 22:38:43  jeg3600
 *     *** empty log message ***
 *
 *     Revision 1.1  2007/10/28 03:30:14  jeg3600
 *     Initial revision
 *
 *
 *
 */

#include "ErieCanalMonitor.h"
#include <errno.h>

using namespace erie;

 /**
   * constructor
   * initialize values
   */
ErieCanalMonitor::ErieCanalMonitor() {
	
      // Initialize the number of cars to 0
      cars = 0;

      // Initialize the mutex
      pthread_mutex_init(&rightDirection, NULL);
      sem_init(maxAllowance, 0, 0);

      // Set direction to NONE
      direction = NONE;

}


/**
 * Cross north across the bridge
 * @param id    -- number of car trying to cross
 */
void ErieCanalMonitor::crossToNorth(int id) {

  // std::cout << cars << " cars currently on bridge" << std::endl;

  std::cout << "Car " << id << " is waiting to cross North." << std::endl;

  // Make sure that the traffic is in the correct direction
  if (direction != NORTH) {

    pthread_mutex_lock(&rightDirection);

    direction = NORTH;

  }

  // Make sure that entering will not exceed the maximum car
  // allowance for the bridge
  if ((cars + 1) >= MAX_CARS) {
  
    sem_post(maxAllowance);
      
  }

  // Add a car to the bridge
  cars++;

  std::cout << "Driver " << id << " begins to cross North." << std::endl;
  
  // Sleep for the trip
  usleep(TRIP_TIME);
  
  reachedTheNorth(id);
  
}

/**
 * Called once the car has completed going north
 * @param id    -- number of car finishing the cross
 */
void ErieCanalMonitor::reachedTheNorth(int id) {

  std::cout << "Driver " << id << " has now crossed North." << std::endl;

  cars--;
  
  if (cars < 3) {
    
    sem_wait(maxAllowance);
    
    // Set the direction to none if not cars
    if(cars == 0) {
      pthread_mutex_unlock(&rightDirection);
      direction = NONE;
    }
    
  }
  
}

 /**
  * Called for a car which wants to cross South across the bridge
  * @param id    -- number of car trying to cross
  */
void ErieCanalMonitor::crossToSouth(int id) {

  std::cout << "Car " << id << " is waiting to cross South." << std::endl;

  // Make sure that the traffic is in the correct direction
  if (direction != SOUTH) {

    pthread_mutex_lock(&rightDirection);

    direction = SOUTH;

  }


  // Make sure that entering will not exceed the maximum car
  // allowance for the bridge
  if ((cars + 1) >= MAX_CARS) {
    
    sem_post(maxAllowance);
  
  }
      
  cars++;
  
  std::cout << "Driver " << id << " begins to cross South." << std::endl;
  
  // Sleep for the trip
  usleep(TRIP_TIME);
  
  reachedTheSouth(id);
  
}

/**
 * Called when a car has completed going south
 * @param id    -- number of car finishing the cross
 */
void ErieCanalMonitor::reachedTheSouth(int id) {


  std::cout << "Driver " << id << " has now crossed South." << std::endl;

  cars--;
  
  if (cars < 3) {
    
    sem_wait(maxAllowance);
    
    // Set the direction to none if not cars
    if(cars == 0) {
      pthread_mutex_unlock(&rightDirection);
      direction = NONE;
    }
    
  }
  
}

/*
 * Deconstructor
 */
ErieCanalMonitor::~ErieCanalMonitor() {

  // Destroy the mutexes
  pthread_mutex_destroy(&rightDirection);
  sem_destroy(maxAllowance);

}
