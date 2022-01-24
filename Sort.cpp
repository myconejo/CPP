#include <stdlib.h>
#include <stdio.h>

#define VERBOSE 0

void line() {
    printf("---------------------------------------------------\n");
}

/* array - array constructor with size */
int* array(int size) {
    int* arr = (int *)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        // random integer generator
        *(arr+i) = i*2 - (size*i + 4)%13 + i%5 + (((int)arr+(int)(&i))>>4 + 7*i)%19;
    }
    return arr;
}

int max(int arr[], int size) {
    if (VERBOSE) printf(">> array is at %p\n", arr);
    if (VERBOSE) printf("length of the given array is %d\n", size);
    int max = *arr;
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

int min(int *arr, int size) {
    int min = *arr;
    for (int i = 1; i < size; i++) {
        if (*(arr+i) < min) min = *(arr+i);
    }
    return min;
}

/* traverse - traversing the list elements */
void traverse(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr+i));
    }
    printf("\n");
}

/* selSort - selection sort with time complexity O(n^2)  */
void selSort(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        int min = *(arr+i);
        int tem = min;
        int ind = i;
        for (int j = i+1; j < size; j++) {
            if (*(arr+j) < min) {
                min = *(arr+j);
                ind = j;
            }
        }
        *(arr+i) = *(arr+ind);
        *(arr+ind) = tem;
    }
}

/* insSort - insertion sort with time complexity O(n^2) */
void insSort(int *arr, int size) {
    int temp = 0;
    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (*(arr+i) < *(arr+j)) {
                temp = *(arr+i);
                *(arr+i) = *(arr+j);
                *(arr+j) = temp;
            }
        }
    }
}

int main() {
    // array allocation
    int *a = array(10);
    int *b = array(5);

    // array a
    line();
    printf("Traversing array 'a': ");
    traverse(a, 10);
    //printf("Max element of the array 'a' is %d\n", max(a, 10));
    //printf("Min element of the array 'a' is %d\n", min(a, 10));

    // insertion sort
    printf("Insertion sort of array 'a'\n");
    insSort(a, 10);
    traverse(a, 10);
    line();

    // deallocate the memory
    free(a);

    // array b
    printf("Traversing array 'b': ");
    traverse(b, 5);

    // selection sort
    printf("Selection sort of array 'b'\n");
    selSort(b, 5);
    traverse(b, 5);
    line();

    // deallocate the memory
    free(b);
    return 0;
}
