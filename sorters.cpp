#include <cstdlib>
#include <stdlib.h> 
#include <iostream>
#include <time.h>

#define ARRAY_SIZE 100
#define RANDOM_RANGE 100


using namespace std;

void printArray ( int * array, int size )
{
    for ( int i = 0; i < size - 1; i++ )
        cout << array [ i ] << ", ";
    
    cout << array [ size - 1 ] << endl; 
}

// -----------------------------------------------------------------------------

void swap ( int * array, int x, int y )
{
    int tmp = array [ y ];
    array [ y ] = array [ x ];
    array [ x ] = tmp;
}

void bubbleSort ( int * array, int size )
{
    for ( int i = 0; i < size - 1; i++ )
    {
        for ( int j = 0; j < size - 1 - i; j++ )
        {
            if ( array [ j + 1 ] < array [ j ] )
                swap (array, j, j + 1 );
        }
    }
}

// -----------------------------------------------------------------------------

void selectionSort ( int * array, int size )
{
    for ( int i = 0; i < size - 1; i++ )
    {
        int currentMin = i;
        
        for ( int j = i + 1; j < size; j++ )
        {
            if ( array [ j ] < array [ currentMin ] )
                currentMin = j;
        }
        
        swap ( array, currentMin, i );
    }
}

// -----------------------------------------------------------------------------

void insertionSort ( int * array, int size )
{
    for ( int i = 0; i < size - 1; i++ )
    {
        int j = i + 1;
        int tmp = array [ j ];
        while ( j > 0 && tmp < array [ j - 1] )
            array [ j-- ] = array [ j - 1 ];
        
        array [ j ] = tmp;
    }
}

// -----------------------------------------------------------------------------

void quickSort ( int * array, int left, int right )
{
    if ( left < right)
    {
        int boundary = left;
        for ( int i = left + 1; i < right; i++ )
        {
            if ( array [ i ] < array [ left ] )
                swap ( array, i, ++boundary );
        }
      
        swap ( array, left, boundary );
        quickSort ( array, left, boundary );
        quickSort ( array, boundary + 1, right );
    }
}

// -----------------------------------------------------------------------------

void mergeSortMerge ( int * array, int * aux, int left, int right)
{
    int middleIndex = ( left + right ) / 2;
    int leftIndex = left;
    int rightIndex = middleIndex + 1;
    int auxIndex = left;
    while ( leftIndex <= middleIndex && rightIndex <= right ) 
    {
        if ( array [ leftIndex ] <= array [ rightIndex ] )
            aux [ auxIndex++ ] = array [ leftIndex++ ];
        else
            aux [ auxIndex++ ] = array [ rightIndex++ ];
        
    }
    
    while ( leftIndex <= middleIndex )
        aux [ auxIndex++ ] = array [ leftIndex++ ];
    

    while ( rightIndex <= right )
        aux [ auxIndex++ ] = array [ rightIndex++ ];
}

void mergeSort ( int * array, int * aux, int left, int right)
{
    if ( left == right ) 
        return;
    
    int middleIndex = ( left + right ) / 2;
    mergeSort ( array, aux, left, middleIndex );
    mergeSort ( array, aux, middleIndex + 1, right );
    mergeSortMerge ( array, aux, left, right );
    
    for ( int i = left; i <= right; i++ )
        array [ i ] = aux [ i ];
}

// -----------------------------------------------------------------------------

void repairHeapSort ( int * array, int bottom, int topIndex )
{
    int tmp = array [ topIndex ];
    int succ = topIndex * 2 + 1;
    if ( succ < bottom && array [ succ ] > array [ succ + 1 ] ) 
        succ++;
    
    while (succ <= bottom && tmp > array [ succ ] )
    {
        array [ topIndex ] = array [ succ ];
        topIndex = succ;
        succ = succ * 2 + 1;
        if ( succ < bottom && array [succ] > array [ succ + 1 ] )
            succ++;
    }
    
    array[topIndex] = tmp;
}

void heapSort(int * array, int size )
{
    for ( int i = size / 2 - 1; i >= 0; i-- ) 
        repairHeapSort ( array, size - 1, i );
    
    for ( int i = size - 1; i > 0; i-- ) 
    {
        swap ( array, 0, i );
        repairHeapSort ( array, i - 1, 0 );
    }
}

// -----------------------------------------------------------------------------

int main ( int argc, char ** argv ) 
{
    int array [ ARRAY_SIZE ];
    srand ( time ( NULL ) );
    
    for ( int i = 0; i < ARRAY_SIZE; i++ )
        array [ i ] = rand() % RANDOM_RANGE;
    
    printArray ( array, ARRAY_SIZE );
    
    int sorter = rand ( ) % 6 + 1;
    
    switch ( /*sorter*/ 5 )
    {
        case 1:
            // Bubble sort
            cout << endl << "Bubble sort" << endl;
            bubbleSort ( array, ARRAY_SIZE );
            break;
        case 2:
            // Selection sort
            cout << endl << "Selection sort" << endl;
            selectionSort ( array, ARRAY_SIZE );
            break;
        case 3:
            // Insertion sort
            cout << endl << "Insertion sort" << endl;
            insertionSort ( array, ARRAY_SIZE );
            break;
        case 4:
            // Quicksort
            cout << endl << "Quicksort" << endl;
            quickSort ( array, 0, ARRAY_SIZE );
            break;
        case 5:
            // Merge sort
            cout << endl << "Merge sort" << endl;
            int aux [ ARRAY_SIZE ];
            mergeSort ( array, aux, 0, ARRAY_SIZE - 1 );
            break;
        case 6:
            // Heapsort
            cout << endl << "Heapsort" << endl;
            heapSort ( array, ARRAY_SIZE );
            break;
            
    }            
            
    printArray ( array, ARRAY_SIZE );
    
    return 0;
}

