#include <iostream>
#include <string.h>
#include <random>
#include <time.h>

#define MAX 10
#define MAX_RAND 20


// MERGESORT
template <typename T>
void merge(T array[], size_t left, size_t middle, size_t right) {
    size_t leftLen = middle - left +1;
    size_t rightLen = right - middle;

    T leftArray[leftLen]; // temp sub arrays
    T rightArray[rightLen]; // temp sub arrays

    // copying left side of array in a temp array
    // copying in leftArray from (array + position) position using pointer arithmetichs
    memcpy(leftArray, array + left, leftLen * sizeof(T));
    memcpy(rightArray, array + middle + 1, rightLen * sizeof(T));

    size_t i = 0; // counter for the first array
    size_t j = 0; // counter for the second array
    size_t k = left; // current position of the starting array

    while(i < leftLen and j < rightLen) {
        // scanning the array and comparing left sub array
        // to right one and choosing which one to insert in the starting array
        if(leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            i++;
        }
        else {
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }

    while(i < leftLen) {
        array[k] = leftArray[i];
        i++;
        k++;
    }

    while(j < rightLen) {
        array[k] = rightArray[j];
        j++;
        k++;
    }
}

template <typename T>
void mergeSort(T array[], size_t left, size_t right) {
    if(left < right) {
        size_t middle = (left+right)/2;
        
        mergeSort<T>(array, left, middle);
        mergeSort<T>(array, middle+1, right);

        merge<T>(array, left, middle, right);
    }
}

template <typename T>
void mergeSort(T array[], size_t dim) { mergeSort<T>(array, 0, dim); }

// QUICKSORT
template <typename T>
void swap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
size_t partition(T array[], size_t low, size_t high) {
    T pivot = array[high]; // pivot element
    size_t lowest = low - 1; // lowest index in the low zone of the array

    for(size_t i = low; i < high; i++) {
        if(array[i] <= pivot) {
            lowest++;
            swap(array[lowest], array[i]);
        }
    }
    swap(array[lowest + 1], array[high]);
    return (lowest + 1);
}

template <typename T>
void quickSort(T array[], size_t low, size_t high) {
    if(low < high) {
        size_t pivot = partition(array, low, high);
        // to avoid pivot - 1 becoming negative
        if(pivot != 0) quickSort(array, low, pivot - 1);
        quickSort(array, pivot + 1, high);
    }
}

template <typename T>
void quickSort(T array[], size_t len) { quickSort<T>(array, 0, len); }


// other functions
template <typename T>
void printArray(T array[], size_t dim) {
    for(size_t i = 0; i < dim; i++) {
        std::cout << array[i] << " ";
    }

    std::cout << std::endl;
}

int main() {
    srand(time(nullptr));
    int array[MAX];

    for(size_t i = 0; i < MAX; i++) {
        array[i] = rand() % MAX_RAND +1;
    }

    printArray<int>(array, MAX);
    quickSort<int>(array, MAX);
    printArray<int>(array, MAX);
    
}
