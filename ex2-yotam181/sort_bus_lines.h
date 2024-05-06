#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif //EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21
/**
Struct representing a bus line with 3 field
 name as array of chars
 distance and duration as int
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

/**
 * Enumeration representing sorting types for bus lines
 */
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;


/**
Sorts an array of BusLine structs in ascending order based on
the name field using bubble sort algorithm.
@param start Pointer to the first element of the array.
@param end Pointer to the last element of the array.
@return This function does not return a value.
*/
void bubble_sort (BusLine *start, BusLine *end);

/**
This function implements the quicksort algorithm to sort an array of bus lines.
It takes as input a pointer to the start of the array, a pointer to the end of
the array, and a SortType enum to specify whether to sort by distance or duration.
The function first partitions the array into two parts, one with elements smaller than
the pivot and one with elements larger than the pivot. Then it recursively sorts
each part of the array.
@param start A pointer to the start of the array of bus lines
@param end A pointer to the end of the array of bus lines
@param sort_type The SortType enum specifying whether to sort by distance or duration
 @return This function does not return a value.
*/
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
This function partitions the array of bus lines into two parts, one with elements smaller
than the pivot and one with elements larger than the pivot. It takes as input a pointer to
the start of the array, a pointer to the end of the array, and a SortType enum to specify
whether to sort by distance or duration. The function chooses the last element in the array
as the pivot and swaps elements to partition the array.
@param start A pointer to the start of the array of bus lines
@param end A pointer to the end of the array of bus lines
@param sort_type The SortType enum specifying whether to sort by distance or duration
@return A pointer to the partitioned element in the array
*/
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif //EX2_REPO_SORTBUSLINES_H
#endif //EX2_REPO_SORTBUSLINES_H
