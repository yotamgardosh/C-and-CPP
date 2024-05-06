#include "test_bus_lines.h"

/**
Checks if an array of BusLine structures is sorted by distance.
     -See full documentation in header file
 */
int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  BusLine* traveler = start;
  while (traveler + 1 != end)
  {
    if(traveler->distance > (traveler+1)->distance)
    {
      return 0;
    }
    traveler++;
  }
  return 1;
}

/**
Checks if an array of BusLine structures is sorted by duration.
     -See full documentation in header file
 */
int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  BusLine* traveler = start;
  while (traveler + 1 != end)
  {
    if(traveler->duration > (traveler+1)->duration)
    {
      return 0;
    }
    traveler++;
  }

  return 1;

}
/**
Checks if an array of BusLine structures is sorted by name.
     -See full documentation in header file
 */
int is_sorted_by_name (BusLine *start, BusLine *end)
{
  BusLine* traveler = start;
  while (traveler + 1 != end)
  {
    if (strcmp (traveler->name, (traveler + 1)->name) < 0)
    {
      return 0;
    }
    traveler++;
  }
  return 1;

}

/**
Checks if two arrays of BusLine structures are equal
    -See full documentation in header file
*/
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
  long len_sorted = (end_sorted-start_sorted);
  long len_original = (end_original-start_original);
  if(len_original != len_sorted)
  {
    return 0;
  }
  int flag;
  BusLine* original_trav = start_original;
  BusLine* sorted_trav = start_sorted;
  while(original_trav != end_original)
  {
    flag = 0;
    sorted_trav = start_sorted;
    while(sorted_trav!=end_sorted)
    {
      if(strcmp(original_trav->name,sorted_trav->name) == 0)
      {
        flag = 1;
      }
      sorted_trav++;
    }
    if(flag == 0)
    {
      return 0;
    }
    original_trav++;
  }
  return 1;
}