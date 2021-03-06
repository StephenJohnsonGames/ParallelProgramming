
#include <iostream>
#include <string>
#include <random>
#include "gl_stuff.h"
#include "Array2D.h"
#include <tbb/tbb.h>
#include <chrono>
#include <numeric>

using namespace std;
using namespace tbb;
using namespace std::chrono;

#pragma region Function Prototypes

void initPattern(Array2D<int>& array); // demo function
void clearSecondArray(Array2D<int>& array); // demo function
void update(void); // Main scene update function

#pragma endregion


//
// Example array
//test 4 - test over multiple array sizes
Array2D<int>					myArray = Array2D<int>(128, 128);
Array2D<int>					twoArray = Array2D<int>(128, 128);
UINT memIndex;
UINT value;
bool frameSwitch = true;
int updateCount;
vector<long long>				times;
long long						timesSum;

// Starting point for our program...
int main(int argc, char* argv[])
{
	
	// Initialise OpenGL window...
	gl_init(argc, argv, update, "Game of Life Demo", true);

	// Initialise our Game of Life starting pattern...
	initPattern(myArray);
	clearSecondArray(twoArray);

	// Start the main loop - this calls our update function (below) to update our game of life generations.
	// Note: We never return from glutMainLoop until we quit the application
	glutMainLoop();
		
	return 0;
}

void clearSecondArray(Array2D<int>& array) {

	parallel_for(
		0,
		array.w * array.h,
		[&](int i) {

			int x = i % array.w;
			int y = i / array.h;
			array(x, y) = 0;
		}
	);
}
// Demo function to initialise cells...
void initPattern(Array2D<int>& array) {

	// First clear the array (set all cells to off / dead)
	parallel_for(
		0,
		array.w * array.h,
		[&](int i) {

			int x = i % array.w;
			int y = i / array.h;
			array(x, y) = 0;
		}
	);


	// Setup random number generator and distribution [0, 1] ... just in case we need it
	// NOTE : FEEL FREE TO UPDATE THE RANGE AS NEEDED!!!
	random_device rd;
	mt19937 mt(rd());
	uniform_real_distribution<float> rDist(0.0f, 1.0f);


	// Now set live cells...
#if 1

	// Approach 1 - explicitly set each cell you want to be alive

	/* STILL LIFES (not much to test here but include just in case) */


	//test 1 with oscillators + spaceships

	/* OSCILLATORS  */

	//Blinker
	array(3, 3) = 1;
	array(2, 3) = 1;
	array(4, 3) = 1;

	//Toad
	array(3, 9) = 1;
	array(4, 9) = 1;
	array(5, 9) = 1;
	array(2, 10) = 1;
	array(3, 10) = 1;
	array(4, 10) = 1;

	//Beacon
	array(5, 16) = 1;
	array(5, 17) = 1;
	array(6, 16) = 1;
	array(6, 17) = 1;
	array(7, 18) = 1;
	array(8, 18) = 1;
	array(7, 19) = 1;
	array(8, 19) = 1;

	//Pulsar - goes so fast you can't really recognise it, may need to look into?
	//top left
	array(6, 27) = 1;
	array(7, 27) = 1;
	array(8, 27) = 1;
	array(9, 29) = 1;
	array(9, 30) = 1;
	array(9, 31) = 1;
	array(6, 32) = 1;
	array(7, 32) = 1;
	array(8, 32) = 1;
	array(4, 29) = 1;
	array(4, 30) = 1;
	array(4, 31) = 1;

	//top right
	array(12, 27) = 1;
	array(13, 27) = 1;
	array(14, 27) = 1;
	array(11, 29) = 1;
	array(11, 30) = 1;
	array(11, 31) = 1;
	array(12, 32) = 1;
	array(13, 32) = 1;
	array(14, 32) = 1;
	array(16, 29) = 1;
	array(16, 30) = 1;
	array(16, 31) = 1;

	//bottom left
	array(6, 34) = 1;
	array(7, 34) = 1;
	array(8, 34) = 1;
	array(9, 35) = 1;
	array(9, 36) = 1;
	array(9, 37) = 1;
	array(6, 39) = 1;
	array(7, 39) = 1;
	array(8, 39) = 1;
	array(4, 35) = 1;
	array(4, 36) = 1;
	array(4, 37) = 1;

	//bottom right
	array(12, 34) = 1;
	array(13, 34) = 1;
	array(14, 34) = 1;
	array(11, 35) = 1;
	array(11, 36) = 1;
	array(11, 37) = 1;
	array(12, 39) = 1;
	array(13, 39) = 1;
	array(14, 39) = 1;
	array(16, 35) = 1;
	array(16, 36) = 1;
	array(16, 37) = 1;

	//Penta-decathlon
	array(26, 5) = 1;
	array(25, 6) = 1;
	array(26, 6) = 1;
	array(27, 6) = 1;
	array(24, 7) = 1;
	array(25, 7) = 1;
	array(26, 7) = 1;
	array(27, 7) = 1;
	array(28, 7) = 1;
	array(24, 14) = 1;
	array(25, 14) = 1;
	array(26, 14) = 1;
	array(27, 14) = 1;
	array(28, 14) = 1;
	array(25, 15) = 1;
	array(26, 15) = 1;
	array(27, 15) = 1;
	array(26, 16) = 1;

	/* SPACESHIPS */

	//Glider
	array(25, 30) = 1;
	array(27, 30) = 1;
	array(26, 31) = 1;
	array(27, 31) = 1;
	array(26, 32) = 1;

	//Light-weight spaceship
	array(23, 49) = 1;
	array(24, 49) = 1;
	array(21, 50) = 1;
	array(22, 50) = 1;
	array(24, 50) = 1;
	array(25, 50) = 1;
	array(21, 51) = 1;
	array(22, 51) = 1;
	array(23, 51) = 1;
	array(24, 51) = 1;
	array(22, 52) = 1;
	array(23, 52) = 1;

	//Middle-weight spaceship
	array(23, 69) = 1;
	array(24, 69) = 1;
	array(20, 70) = 1;
	array(21, 70) = 1;
	array(22, 70) = 1;
	array(24, 70) = 1;
	array(25, 70) = 1;
	array(20, 71) = 1;
	array(21, 71) = 1;
	array(22, 71) = 1;
	array(23, 71) = 1;
	array(24, 71) = 1;
	array(21, 72) = 1;
	array(22, 72) = 1;
	array(23, 72) = 1;

	//Heavy-weight spaceship
	array(23, 89) = 1;
	array(24, 89) = 1;
	array(19, 90) = 1;
	array(20, 90) = 1;
	array(21, 90) = 1;
	array(22, 90) = 1;
	array(24, 90) = 1;
	array(25, 90) = 1;
	array(19, 91) = 1;
	array(20, 91) = 1;
	array(21, 91) = 1;
	array(22, 91) = 1;
	array(23, 91) = 1;
	array(24, 91) = 1;
	array(20, 92) = 1;
	array(21, 92) = 1;
	array(22, 92) = 1;
	array(23, 92) = 1;

	/*  INDEFINITE PATTERNS  */

	//test 2 with multiple indefinite patterns

	//Gosper glider gun

	/*array(10, 105) = 1;
	array(10, 106) = 1;
	array(11, 105) = 1;
	array(11, 106) = 1;
	array(20, 105) = 1;
	array(20, 106) = 1;
	array(20, 107) = 1;
	array(21, 104) = 1;
	array(21, 108) = 1;
	array(22, 103) = 1;
	array(23, 103) = 1;
	array(22, 109) = 1;
	array(23, 109) = 1;
	array(24, 106) = 1;
	array(25, 104) = 1;
	array(25, 108) = 1;
	array(26, 105) = 1;
	array(26, 106) = 1;
	array(26, 107) = 1;
	array(27, 106) = 1;
	array(30, 103) = 1;
	array(30, 104) = 1;
	array(30, 105) = 1;
	array(31, 103) = 1;
	array(31, 104) = 1;
	array(31, 105) = 1;
	array(32, 102) = 1;
	array(32, 106) = 1;
	array(34, 101) = 1;
	array(34, 102) = 1;
	array(34, 106) = 1;
	array(34, 107) = 1;
	array(44, 103) = 1;
	array(44, 104) = 1;
	array(45, 103) = 1;
	array(45, 104) = 1;*/

#else
//test 3 random dist
	// Parallel for initialisation of cells...
	// NOTE: Uses 1D array approach, but can map single index to 2D coord if we know the width and height of the 2D array
	parallel_for(
		0,
		array.w * array.h,
		[&](int i) {

			int x = i % array.w;
			int y = i / array.h;

			// Example - checkerboard pattern
			if ((x & 0x01) == (y & 0x01))
				//array(x, y) = 1;
				array(x, y) = round(rDist(mt));
		}
	);

#endif

}

// Main scene update function (called by FreeGLUT's main event loop every frame) - YOU DON'T NEED TO CALL THIS - IT'S CALLED FOR YOU!!!
void update(void) {

	//clock to check total time elapsed
	//auto globalTimer = high_resolution_clock::now;
	tick_count tickGlobal = tick_count::now();
	//time the sequential/parallel

	//chrono version
	auto t0 = high_resolution_clock::now();

	//tbb tick count version
	tick_count tick0 = tick_count::now();

	//sequential version
#	if 0

	//run through our 2D array, processing them and copying them to a second array
	for (int y = 0; y < myArray.h; y++) {
		for (int x = 0; x < myArray.w; x++) {
			//twoArray(x, y) = myArray(x, y);
			int i = myArray(x, y);
			int a = myArray(x - 1, y - 1);
			int b = myArray(x, y -1);
			int c = myArray(x + 1, y - 1);
			int d = myArray(x - 1, y);
			int e = myArray(x + 1, y);
			int f = myArray(x - 1, y + 1);
			int g = myArray(x, y + 1);
			int h = myArray(x + 1, y + 1);
			if (i == 0)
			{
				int nearbyCells = 0;
			
				nearbyCells = a + b + c + d + e + f + g + h;

				if (nearbyCells == 3) {

					//become a live cell
					twoArray(x, y) = 1;
				}

				else {

					twoArray(x, y) = 0;
				}
			}
			if (i == 1)
			{
				//cout << "doing if 1" << endl;
				int nearbyCells = 0;
				nearbyCells = a + b + c + d + e + f + g + h;

				if (nearbyCells < 2) {

					//become a live cell
					twoArray(x, y) = 0;
				}
				else if (nearbyCells == 2) {

					//become a live cell
					twoArray(x, y) = 1;
				}
				else if (nearbyCells > 3)
				{

					twoArray(x, y) = 0;

				}	
				else if (nearbyCells == 3)
				{

					twoArray(x, y) = 1;

				}

			//run through our neighbouring cells
				/*for (int y = myArray.h - 1; y <= myArray.h + 1; y++) {
					for (int x = myArray.w - 1; x <= myArray.w + 1; x++) {*/
					//if (y == myArray.h && x == myArray.w) {
					//	continue;
					//}

					//count up the cells and apply them to nearbyCells
					/*if (y > -1 && y < myArray.h && x > -1 && x < myArray.w) {
						if (myArray(x, y) == 1) {
							nearbyCells++;

						}*/

						/*	if (myArray(x, y) == 0) {

								nearbyCells++;
							}*/


							//}
			}
		}
	}

		//take data from array and put in value array

		for (int y = 0; y < myArray.h; y++) {
			for (int x = 0; x < myArray.w; x++) {

				memIndex = twoArray(x, y);
				
				myArray(x, y) = memIndex;


			}
		}

#else

		//parallel version

		//run through our 2D array, processing them and copying them to a second array
		parallel_for(blocked_range2d<int, int>(0, myArray.h, 0, myArray.w), [&](const blocked_range2d<int, int>& range)  {
			
			int y1 = range.rows().begin();
			int y2 = range.rows().end();
			int x1 = range.cols().begin();
			int x2 = range.cols().end();


			for (int y = y1; y != y2; y++) {
				for (int x = x1; x != x2; x++) {       

			int i = myArray(x, y);
			int a = myArray(x - 1, y - 1);
			int b = myArray(x, y - 1);
			int c = myArray(x + 1, y - 1);
			int d = myArray(x - 1, y);
			int e = myArray(x + 1, y);
			int f = myArray(x - 1, y + 1);
			int g = myArray(x, y + 1);
			int h = myArray(x + 1, y + 1);
			if (i == 0)
			{
				int nearbyCells = 0;

				nearbyCells = a + b + c + d + e + f + g + h;

				if (nearbyCells == 3) {

					//become a live cell
					twoArray(x, y) = 1;
				}

				else {

					twoArray(x, y) = 0;
				}
			}
			if (i == 1)
			{
				//if (i == y2) {

				//	nearbyCells = a + b + d + f + g;
				//}

				int nearbyCells = 0;

				nearbyCells = a + b + c + d + e + f + g + h;

				if (nearbyCells < 2) {

					//become a live cell
					twoArray(x, y) = 0;
				}
				else if (nearbyCells == 2) {

					//become a live cell
					twoArray(x, y) = 1;
				}
				else if (nearbyCells > 3)
				{

					twoArray(x, y) = 0;

				}
				else if (nearbyCells == 3)
				{

					twoArray(x, y) = 1;

				}

			}
			}
			}
		});

		for (int y = 0; y < myArray.h; y++) {
			for (int x = 0; x < myArray.w; x++) {

				memIndex = twoArray(x, y);

				myArray(x, y) = memIndex;


			}
		}
		//parallel_for(blocked_range2d<int, int>(0, myArray.h, 0, myArray.w), [&](const blocked_range2d<int, int>& range) {

		//	int y1 = range.rows().begin();
		//	int y2 = range.rows().end();
		//	int x1 = range.cols().begin();
		//	int x2 = range.cols().end();

		//for (int y = y1; y != y2; y++) {
		//	for (int x = x1; x != x2; x++) {

		//		memIndex = twoArray(x, y);

		//		myArray(x, y) = memIndex;


		//	}
		//}
		//	});
	
#endif
	
	//chrono version
	auto t1 = high_resolution_clock::now();

	//tbb tick count version
	tick_count tick1 = tick_count::now();

	//sum of chrono time
	auto duration = duration_cast<nanoseconds>(t1 - t0);

	updateCount++;

	//times[updateCount] = duration.count();
	//cout << "time taken = " << (t1 - t0).seconds << " seconds\n";
	if (updateCount <= 600) {

		cout << "\nUpdate count = " << updateCount << " + time taken = " << duration.count() << "nanoseconds\n";
		// Redraw the screen to show latest generation

		//for (int t = 0; t < updateCount; t++) {
		times.push_back(duration.count());
		timesSum += duration.count();// times[t];
			//timesSum = timesSum + times[t];
		//}

		renderLatestGeneration(myArray);
		
	}

	if (updateCount == 601) {

		cout << "\ntotal time = " << timesSum << endl;
		cout << "\n average update time = " << (timesSum / 600) << endl;
		
	}

}
