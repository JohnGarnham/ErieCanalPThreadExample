/*
 * Car.h is the car trying to cross the canal.
 *
 * Version:
 *     $Id: Car.h,v 1.3 2007/10/28 22:38:26 jeg3600 Exp jeg3600 $
 *
 * Revisions:
 *     $Log: Car.h,v $
 *     Revision 1.3  2007/10/28 22:38:26  jeg3600
 *     Now passes in Monitor correctly.
 *
 *     Revision 1.2  2007/10/16 17:58:24  jeg3600
 *     Linked to monitor now
 *
 *     Revision 1.1  2007/10/16 03:31:43  jeg3600
 *     Initial revision
 *
 *
 */

#ifndef CAR_H
#define CAR_H

#include "ErieCanalMonitor.h"

using namespace std;

namespace erie {

/**
 * constants for seconds and minutes based on millisecond base.
 */
static const int ONE_SECOND( 1000 );
static const int ONE_MINUTE( 60 * ONE_SECOND );

/**
 * constant
 * turnaround is the range of delay before and after trips (in minutes)
 * Before a car tries to cross, it waits a random amount of time
 * between 0 and the TURNAROUND_TIME (maximum).
 * After a car crosses, it waits a random amount of time
 * between 0 and the TURNAROUND_TIME (maximum) before it tries to
 * cross in the opposite direction.
 */
static const long TURNAROUND_TIME( 15 * 1000 * 10 ); // minutes


/**
 * Car encapsulates a thread that simulates a car
 * trying to cross back and forth.
 *
 * @author bksteele
 * @author John Garnham
 */
class Car {

    /** identifier of this car */
    int license;

    /** trips this car will take */
    int trips;

    /** the direction that the car is currently in */
    int  direction;

    /** the thread */
    pthread_t mainThread;

    /** a pointer to the canal monitor **/
    ErieCanalMonitor* bridgeMonitor;

public:

    /**
     * constructor
     * @param id    -- (license) number of car trying to cross
     * @param numTrips    -- number of trips across car will take
     * @param dir   -- the initial direction of the car
     * @param monitor -- a pointer to the erie canal monitor
     */
    Car(int id, int numTrips, int dir, ErieCanalMonitor* monitor);

    /**
     * start the car
     */
    void start();

    /**
     * @return The license plate number
     */
    int getId();

    /**
     * change directions
     *
     */
    void changeDirections();

    /**
     * @return The number of trips left
     *
     */
    int getTrips();

    /**
     * @return The thread handler
     */
    pthread_t getMainThread();

    /**
     * Deconstructor
     */
    ~Car();

};

}; // namespace

#endif // CAR_H
