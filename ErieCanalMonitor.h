/*
 * ErieCanalMonitor.h is the monitor
 *
 * Version:
 *     $Id: ErieCanalMonitor.h,v 1.2 2007/10/28 22:38:38 jeg3600 Exp jeg3600 $
 *
 * Revisions:
 *     $Log: ErieCanalMonitor.h,v $
 *     Revision 1.2  2007/10/28 22:38:38  jeg3600
 *     *** empty log message ***
 *
 *     Revision 1.1  2007/10/16 04:19:35  jeg3600
 *     Initial revision
 *
 *
 */

#ifndef ERIE_CANAL_MONITOR_H
#define ERIE_CANAL_MONITOR_H

#include <iostream>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

namespace erie {

/**
 * ErieCanalMonitor is a monitor controlling access and
 * use of the single lane bridge crossing the Erie Canal.
 * trying to cross back and forth.
 *
 * @author bksteele
 * @author John Garnham
 */

 /**
  * TRIP_TIME is the range of simulated trip time spent crossing bridge
  * (in seconds).
  * As a car crosses, it 'waits' a random amount of time
  * between 0 and the TRIP_TIME (maximum) to simulate the crossing time.
  * Different cars cross at different speeds.
  * For example, Granpa might drive really slowly across, while
  * AJ Foyt would be expected to go fast.
  */
  
  static const long TRIP_TIME( 45 * 1000 * 10 ); // minutes
  
  /* The maximum number of cars allowed on the bridge at a time */
  static const long MAX_CARS ( 3 );

class ErieCanalMonitor {

  // The number of cars currently on the bridge
  int cars;

  // the current direction of traggic
  enum{NONE = 0, NORTH = 1, SOUTH = 2} direction;

  // a mutex for max car allowance
  sem_t* maxAllowance;

  // a mutex for direction
  pthread_mutex_t rightDirection;

public:

  /**
   * constructor
   */
  ErieCanalMonitor();

  /**
   * @param id    -- number of car trying to cross
   */
  void crossToNorth( int id );

  /**
   * @param id    -- number of car finishing the cross
   */
  void reachedTheNorth( int id );

  /**
   * @param id    -- number of car trying to cross
   */
  void crossToSouth( int id );

  /**
   * @param id    -- number of car finishing the cross
   */
  void reachedTheSouth( int id );
    
  /**
   * Deconstructor
   */
  ~ErieCanalMonitor();

}; // ErieCanalMonitor

}; // namespace

#endif // ERIE_CANAL_MONITOR_H

