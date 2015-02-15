#include "movAve.h"

movAvData_t *initMovAveData(unsigned int size){ //size is # samples to keep
	movAvData_t data;
	data.size = size;
	int i;
	for(i = 0; i < size; i++){
		data.samples[i] = 0;
	}
	data.currentIndex = 0;
	movAvData_t *dataPtr = &data;
	return dataPtr;
}

void addDataPoint(movAvData_t* data, int point){
	data->samples[data->currentIndex] = point;
	data->currentIndex++;
	if(data->currentIndex >= data->size){ //overflow cases
		data->currentIndex = 0;
	}
}

int currentAve(movAvData_t* data, unsigned int sizeAverage){
	int countIndex = data->currentIndex;
	int sum = 0;
	int i;
	for(i = 0; i < sizeAverage; i++){
		sum += data->samples[countIndex];
		countIndex--;
		if(countIndex < 0){
			countIndex = (data->size) - 1; //wrap around array
		}
	}
	return (sum/ sizeAverage);
}

int arrayAv(int* array, int length){
	int ave = 0;
	unsigned int i;
	for(i = 0; i < length; i++){
		ave += array[i];
	}

	return (ave/length);
}

int arrayMax(int* array, int length){
	int max = 0x8000; //lowest signed number
	unsigned int i;
	for(i = 0; i < length; i++){
		if(array[i] > max){
			max = array[i];
		}
	}
	return max;
}

int arrayMin(int* array, int length){
	int min = 0x7FFF; //highest signed number
	unsigned int i;
	for(i = 0; i < length; i++){
		if(array[i] < min){
			min = array[i];
		}
	}
	return min;
}
