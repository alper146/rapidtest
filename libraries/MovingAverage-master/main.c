/*******************************************
  * Author: C2C William Parks
  * Created: 12 Oct 2013
  * Description: Calulates the moving average for two different data sets
  * 	and number of values considered.
*******************************************/

#include <msp430.h> 
#include "movAve.h"

#define N_AVG_SAMPLES1 2
#define N_AVG_SAMPLES2 4
#define DATA_SIZE 12
#define SAMP_SIZE 10

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer


    int dataSetOne[] = {45, 42, 41, 40, 43, 45, 46, 47, 49, 45};
    int dataSetTwo[] = {174, 162, 149, 85, 130, 149, 153, 164, 169, 173};
    volatile int dataOneSizeOne[SAMP_SIZE], dataOneSizeTwo[SAMP_SIZE], dataTwoSizeOne[SAMP_SIZE], dataTwoSizeTwo[SAMP_SIZE];
    unsigned int i;
    movAvData_t *movAvCalcPtr;

    //First data set with first sample length
    movAvCalcPtr = initMovAveData(DATA_SIZE);
    for(i = 0; i < SAMP_SIZE; i++){
    	addDataPoint(movAvCalcPtr, dataSetOne[i]);
    	dataOneSizeOne[i] = currentAve(movAvCalcPtr, N_AVG_SAMPLES1 );
    }

    //First data set with second sample length
    movAvCalcPtr = initMovAveData(DATA_SIZE);
    for(i = 0; i < SAMP_SIZE; i++){
    	addDataPoint(movAvCalcPtr, dataSetOne[i]);
    	dataOneSizeTwo[i] = currentAve(movAvCalcPtr, N_AVG_SAMPLES2 );
    }

    //Second data set with first sample length
    movAvCalcPtr = initMovAveData(DATA_SIZE);
    for(i = 0; i < SAMP_SIZE; i++){
    	addDataPoint(movAvCalcPtr, dataSetTwo[i]);
    	dataTwoSizeOne[i] = currentAve(movAvCalcPtr, N_AVG_SAMPLES1 );
    }

    //Second data set with second sample length
    movAvCalcPtr = initMovAveData(DATA_SIZE);
    for(i = 0; i < SAMP_SIZE; i++){
    	addDataPoint(movAvCalcPtr, dataSetTwo[i]);
    	dataTwoSizeTwo[i] = currentAve(movAvCalcPtr, N_AVG_SAMPLES2 );
    }

    while(1){};
}
