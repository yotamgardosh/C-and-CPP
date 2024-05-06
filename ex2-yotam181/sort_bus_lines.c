#include "sort_bus_lines.h"
#include <string.h>


void swap(BusLine *line1, BusLine *line2);
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);

/**
@brief Sorts an array of BusLine by name using bubble sort.
 -See full documentation in header file
*/
void bubble_sort (BusLine *start, BusLine *end)
{
    long n = end - start;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp((start+j)->name,(start+j+1)->name) > 0)
            {
                swap(start+j, start+j+1);
            }
        }
    }
}

/**
Swaps two BusLine objects
@param line1 Pointer to the first BusLine object
@param line2 Pointer to the second BusLine object
*/
void swap(BusLine *line1, BusLine *line2)
{
  BusLine temp = *line1;
  *line1 = *line2;
  *line2 = temp;
}

/**
@brief Sorts the array of bus lines using the quicksort algorithm
  -See full documentation in header file
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
  if(start < end)
  {
    BusLine* partition_pointer = partition (start, end, sort_type);
    quick_sort (start, partition_pointer, sort_type);
    quick_sort (partition_pointer + 1, end, sort_type);
  }
}
/**
@brief Partitions the array of bus lines into two parts
   -See full documentation in header file
 */
BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
  BusLine* pivot = end-1;
  BusLine* i = start-1;
  BusLine* j = start;
  while (j < end - 1)
  {
    if(((sort_type == DISTANCE) && (j->distance < pivot->distance)) ||
    ((sort_type == DURATION) && (j->duration < pivot->duration)))
    {
      i++;
      swap (i,j);
    }
    j++;
  }
  i++;
  swap(i,pivot);
  return i;
}