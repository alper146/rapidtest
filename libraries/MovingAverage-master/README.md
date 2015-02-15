# Moving Average by William Parks

## Structure Moving Average
Contents:

- an array of samples (set size, currently 0x10)
- integer storing the size of the array
- pointer to next spot in array to be updated

## Methods

### `void initMovAveData(unsigned int size)`
Takes the number of samples to be stored (must be less than the hardcoded value, and limits the data array to that size. Sets all values to 0.

### `void addDataPoint(movAveData_t* data, int point)`
Takes an input in point, and stores it to the appropriate point in the given data structure. Updates internal pointer appropriately.

### `int currentAve(movAveData_t* data, unsigned int sizeAverage)`
Calculates and returns the moving average, of length sizeAverage, from data structure pointer data.

### `int arrayAv(int* array, int length)`
Returns the average of the given array, with given length.

### `int arrayMax(int* array, int length)`
Returns the max value of the given array, with given length.

### `int arrayMin(int* array, int length)`
Returns the min value of the given array, with given length.
