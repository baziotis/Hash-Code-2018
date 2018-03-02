#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <vector>

using namespace std;

typedef struct Ride {
    int startX;
    int startY;
    int endX;
    int endY;
    int startTime;
    int endTime;
    int id;

    int distance(void);
} ride_t;

typedef struct {
	// position of the car
    int x;
    int y;

	// in which step is the car
    int currentStep;
	
	// rides that the car will take
    vector<int> ridesTaken;
} car_t;

// Global variables
size_t rows;
size_t cols;
int carSize;
int steps;
int numRides;
int bonus;

car_t *cars;
ride_t *allRides;

int distance(int a, int b, int x, int y) {
	// distance between two points (a,b), (x,y)
    return abs(a - x) + abs(b - y);
}

int ride_t::distance(void) {
	return ::distance(startX, startY, endX, endY);
}

int cmp(const void *a, const void *b) {

	// sort rides based on the smallest
	// start time (to get the max bonus)
	ride_t *r1 = (ride_t *) a;
	ride_t *r2 = (ride_t *) b;
	int v1 = r1->startTime;
	int v2 = r2->startTime;
	return (v1 - v2);
}

void readGrid(void) {

	// Read initial data
    cin >> rows >> cols >> carSize
        >> numRides >> bonus >> steps;

	// Take memory for each ride.
    allRides = new ride_t[numRides];
    for (int i = 0; i != numRides; ++i) {
        ride_t& ride = allRides[i];
        cin >> ride.startX >> ride.startY >> ride.endX
            >> ride.endY >> ride.startTime >> ride.endTime;
        ride.id = i;
    }
}

void initCars() {
    cars = new car_t[carSize];

    for (int i = 0; i < carSize; i++) {
        cars[i].x = 0;
        cars[i].y = 0;
        cars[i].currentStep = 1;
    }
}

// Input: The ride for which we
// want to find the nearest car.
// Return: The index of the car.
int bestCar(ride_t &r, int *bestScore) {
    int bestCarIndex = -1;

	int maxScore = 0;
    for (int i = 0; i < carSize; i++) {   // for each car
        car_t &car = cars[i];
		
		// arrivalTime = time that the car will arrive to the position
		// that the ride starts.

        int arrivalTime = car.currentStep + distance(r.startX, r.startY, car.x, car.y);

        if (arrivalTime < r.startTime)
            arrivalTime = r.startTime;

		// endTime = time that the ride will be finished
        int endTime = arrivalTime + r.distance();
        if (r.endTime >= endTime) {
			// score is the distance that we will travel
             int score = r.distance();
			
			// if we are exactly on time,
			// we also get the bonus
            if (arrivalTime == r.startTime)
                score += bonus;

            if (score > maxScore) {
                maxScore = score;
                bestCarIndex = i;
            }
        }
    }

	*bestScore = maxScore;
    return bestCarIndex;
}

void run(void) {

	int totalScore = 0;
	
	// sort rides, with rides with smaller
	// start time first.
	qsort(allRides, numRides, sizeof(ride_t), cmp);

    for (int i = 0; i < numRides; ++i) {   // for each ride
		int curr_score;
    	int index = bestCar(allRides[i], &curr_score);

    	if (index != -1) {   // we found a car
    	    car_t& car = cars[index];

			// Recompute arrival and end time.


    	    int arrivalTime = car.currentStep + distance(allRides[i].startX, allRides[i].startY,
													car.x, car.y);

    	    if (arrivalTime < allRides[i].startTime)
    	        arrivalTime = allRides[i].startTime;

    	    int endTime = arrivalTime + allRides[i].distance();

			totalScore += curr_score;
			
			// Add this ride to the rides that this car will take.
    	    car.ridesTaken.push_back(allRides[i].id);
			// Mark that after this ride, the car will be in endTime step.
    	    car.currentStep = endTime;
			// Mark the finish x and y of the ride.
    	    car.x = allRides[i].endX;
    	    car.y = allRides[i].endY;
    	}
    }

	fprintf(stderr, "SCORE: %d\n", totalScore);
}

void printSolution() {
    for (int i = 0; i < carSize; i++) {  // for each car

		int ridesTaken = cars[i].ridesTaken.size();

		// print how many rides it got.
        cout << ridesTaken << " ";

		// print the id of each ride.
        for (int j = 0; j < ridesTaken; ++j) {
            cout << cars[i].ridesTaken[j] << " ";
        }
        cout << endl;
    }
}

int main(void) {
    readGrid();
    initCars();
    run();
    printSolution();

    return 0;
}
