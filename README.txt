John Garnham


Classes:

Car: Represents individual cars. Variables associated with each car
include a license plate number, the number of trips left that the car
wishes to take, the direction that the car is currently in, and a
thread handling the actual driving of the car. To make the car start
its trip, the start method is called. The start method then creates a
new thread of the non-member "drive" method, passing a reference of
the Car object into it. Once in the "drive" method, the car
continuously alternates between going north and south across the
bridge, depending on how many trips it is scheduled to take.

Erie Control Monitor: Controls traffic on the bridge. Variables
associated with the bridge include the number of cars currently on the
bridge, the current direction of traffic flow, and two mutexes that
control access to the bridge itself, one for checking to ensure that
no more than three cars are allowed on the bridge itself, and one to
prevent head-on collisions. The monitor has four methods:
crossToNorth, reachedTheNorth, crossToSouth, and reachedToSouth. Each
method takes in the license plate number of the car that they are
referencing. crossToNoth and crossToSouth are used to allow cars to
cross across the bridge to the north or the south
respectively. reachedTheNorth and reachedTheSouth are called onced the
cars have completed going across. The deconstructor cleans up all of
the mutexes.

simulation.cpp - The actual executable code of the bridge
simulation. The simulation creates a user-specified number of cars
each taking a user-specified number of trips. It then starts each
car. It is then the responsibility of the car driver to properly use
the Erie Control monitor.
