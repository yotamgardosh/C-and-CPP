#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and
// #endif //EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"


/**
Checks if an array of BusLine structures is sorted by distance.
@param start Pointer to the first element of the array.
@param end Pointer to the last element of the array.
@return 1 if the array is sorted by distance, 0 otherwise.
*/
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
Checks if an array of BusLine structures is sorted by duration.
@param start Pointer to the first element of the array.
@param end Pointer to the last element of the array.
@return 1 if the array is sorted by duration, 0 otherwise.
*/
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
Checks if an array of BusLine structures is sorted by name.
@param start Pointer to the first element of the array.
@param end Pointer to the last element of the array.
@return 1 if the array is sorted by name, 0 otherwise.
*/
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
Checks if two arrays of BusLine structures are equal first by comparing the number
of values and then by comparing their names.
@param start_sorted Pointer to the first element of the sorted array.
@param end_sorted Pointer to the last element of the sorted array.
@param start_original Pointer to the first element of the original array.
@param end_original Pointer to the last element of the original array.
@return 1 if the arrays are equal, 0 otherwise.
*/
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif //EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
