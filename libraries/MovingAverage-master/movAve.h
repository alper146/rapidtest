/*******************************************
  * Author: C2C William Parks
  * Created: 12 Oct 2013
  * Description: Defines a data structure (movAvData)
  * 	to store data for the moving average. Contains
  * 	methods to initialize, add data to the structure,
  * 	and calculate min,max, and average off of an array
*******************************************/

#ifndef MOVAVE_H_

#define MOVAVE_H_
#define MAXSIZE 16 //number of data points to be stored

//Contains the sample data, the length of the data(size),
//	and an index to the next spot in the structure. When using
//  more data points than the size of array, the structure will
//	replace the oldest value.
struct movAvData{
	int samples[MAXSIZE];
	unsigned int size; //samples to be stored, not averaged
	int currentIndex;
};

typedef struct movAvData movAvData_t;

//initializes the structure to store samples. 0's the array.
//Size is the number of values to store. Max set by MAXSIZE define statement
movAvData_t *initMovAveData(unsigned int size);

//adds a data point to the given structure. Will replace oldest data point
// iff array is full.
void addDataPoint(movAvData_t* data, int point);

//Calculates and returns the current moving average given the data structure
// and the number of points to consider (sizeAverage)
int currentAve(movAvData_t* data, unsigned int sizeAverage);

//Given an array and its length, return either its average, its max value,
// or its min value.
int arrayAv(int* array, int length);
int arrayMax(int* array, int length);
int arrayMin(int* array, int length);

#endif /* MOVAVE_H_ */
