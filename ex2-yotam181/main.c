#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "sort_bus_lines.h"
#include "test_bus_lines.h"

#define DUR "by_duration"
#define DIS "by_distance"
#define NAME "by_name"
#define TEST "test"
#define USAGE "USAGE: valid input is only- 'by_duration', 'by_distance', \
'by_name', 'test'"
#define INPUT_LEN 60
#define BASE 10
#define MAX_DIST 1000
#define MIN_DIST 0
#define MAX_DUR 100
#define MIN_DUR 10
#define TWO 2
#define FOUR 4
#define SIX 6

#define NAME_ERROR "ERROR: bus name should contain only digits and small chars\n"
#define DIST_ERROR "ERROR: distance should be an integer between 0 and 1000 \
(includes)\n"
#define DUR_ERROR "ERROR: duration should be an integer between 10 and 1000 \
(includes)\n"

#define ENTER_NUM_OF_LINE_MSG "Enter number of lines. Then enter\n"

#define NUM_OF_LINES_ERROR "ERROR: number of lines should be a whole number \
larger then zero\n"
#define ENTER_INFO_MSG "Enter line info. Then enter\n"

#define TEST_1_PASSED "TEST 1 PASSED: lines were sorted correctly by distance"
#define TEST_1_FAILED "TEST 1 FAILED: unable to sort lines by distance"
#define TEST_3_PASSED "TEST 3 PASSED: lines were sorted correctly by duration"
#define TEST_3_FAILED "TEST 3 FAILED: unable to sort lines by duration"
#define TEST_5_PASSED "TEST 5 PASSED: lines were sorted correctly by name"
#define TEST_5_FAILED "TEST 5 FAILED: unable to sort lines by name"




bool input_validity(int num_of_args, char* array_of_pointers[]);
long get_num_of_lines();
BusLine* line_list(long num_of_lines);
bool line_info_validity(char *name, int distance, int duration);
bool lowercase_and_digits_check(const char* name);
void print_sorted_lines(BusLine* start,BusLine* end);
int run_tests(BusLine* start,BusLine* end, long n);
void equal_test(BusLine *start_sorted,
                BusLine *end_sorted, BusLine *start_original,
                BusLine *end_original, int i);
void name_test(BusLine* start,BusLine* end);
void duration_test(BusLine* start,BusLine* end);
void distance_test(BusLine* start,BusLine* end);



/**
This function checks the validity of the command line arguments and the number of lines inputted.
It then creates a list of BusLines based on the input file. If the test argument is inputted,
it runs a series of tests on the list. Otherwise, it sorts the list based on the
sorting argument and prints the sorted list to stdout.
@param argc The number of command line arguments passed to the program
@param argv An array of strings containing the command line arguments passed to the program
@return int EXIT_SUCCESS if the program runs successfully, EXIT_FAILURE if an error occurs
 */
int main (int argc, char *argv[])
{
  // check that num and type of args is fine if not (print to stdout "USAGE: ")
  if(!input_validity(argc,argv))
  {
    return EXIT_FAILURE;
  }
  long num_of_lines = get_num_of_lines();
  BusLine* start = line_list(num_of_lines);
  if(start == NULL)
  {
    return EXIT_FAILURE;
  }
  BusLine* end = start + num_of_lines; // pointer to end of memory block
  if(!strcmp(argv[1],TEST))
  {
    if(run_tests(start,end,num_of_lines))
    {
      free(start); // frees entire block allocated to all lines
      return EXIT_FAILURE;
    }
    free(start);
    return EXIT_SUCCESS;
  }
  if(strcmp(argv[1],NAME) == 0)
  {
    bubble_sort (start,end);
  }
  if(strcmp(argv[1],DIS) == 0)
  {
    quick_sort (start,end, DISTANCE);
  }
  if(strcmp(argv[1],DUR) == 0)
  {
    quick_sort (start,end, DURATION);
  }
  print_sorted_lines(start,end);
  free(start); // frees entire block allocated to all lines
  return EXIT_SUCCESS;
}

/**
This function prompts the user to enter the number of
lines and returns it after validating the input.
@return (long) number of lines entered by the user.
*/
long get_num_of_lines()
{
  char num_of_lines_str[INPUT_LEN];
  long num_of_lines;
  while(true)
  {
    printf (ENTER_NUM_OF_LINE_MSG);
    fgets(num_of_lines_str, sizeof(num_of_lines_str), stdin);
    char* after_int = NULL;
    num_of_lines = strtol(num_of_lines_str, &after_int, BASE);
    if(num_of_lines <= 0 || (*after_int != '\0' && *after_int != '\n'))
    {
      printf(NUM_OF_LINES_ERROR);
      continue;
    }
    break;
  }
  return num_of_lines;
}


/**
This function checks whether the number and content of input arguments
are valid or not. The input arguments must be exactly two, and the second
argument must be one of "DUR", "DIS", "NAME", or "TEST".
@param num_of_args The number of input arguments
@param array_of_pointers The array of input arguments
@return true if the input arguments are valid, false otherwise
*/
bool input_validity(int num_of_args, char* array_of_pointers[])
{
  if((num_of_args!=TWO)||((strcmp(array_of_pointers[1],DUR)!=0)&&(strcmp
                        (array_of_pointers[1],DIS)!=0)&&(strcmp(array_of_pointers[1],NAME)!=0)&&
                          (strcmp(array_of_pointers[1],TEST)!=0))){
    printf(USAGE);
    printf ("\n");
    return false;
  }
  return true;
}


/**
this function Allocates memory for a list of BusLine structures and prompts the user to enter
information for each line, then updated one at a time default values of buslines in input is valid.
@param num_of_lines Number of bus lines to create.
@return A pointer to the first element of the allocated list is allocation doesn't fail otherwise NULL.
*/
BusLine* line_list(long num_of_lines)
{
  BusLine* start = malloc (num_of_lines * sizeof(BusLine)); // allocate
  BusLine* curr_line = start;
  if (start == NULL)  // check success of allocation
  {
    return NULL;
  }
  int i = 0;
  while(i < num_of_lines)
  {
    char user_input[INPUT_LEN];
    printf (ENTER_INFO_MSG);
    fgets (user_input, sizeof(user_input), stdin);

    int distance, duration;
    char name[NAME_LEN];
    sscanf(user_input, "%[^,],%d,%d", name, &distance, &duration);
    if(line_info_validity(name, distance,duration))
    {
      continue;
    }
    strcpy(curr_line->name,name);
    curr_line->distance = distance;
    curr_line->duration = duration;
    curr_line++;
    i++;
  }
  return start;
}


/**
This function checks if a bus line information is valid. It checks if the name
contains only lowercase letters and digits, if the distance is within the valid range [0,1000],
and if the duration is within the valid range [10,100].
@param[in] name The name of the bus line
@param[in] distance The distance of the bus line
@param[in] duration The duration of the bus line
@return true if the line information is invalid, false otherwise
*/
bool line_info_validity(char *name, int distance, int duration)
{
  if(lowercase_and_digits_check(name))
  {
    printf (NAME_ERROR);
    return true;
  }
  if(distance > MAX_DIST || distance < MIN_DIST)
  {
    printf(DIST_ERROR);
    return true;
  }
  if(duration > MAX_DUR || duration < MIN_DUR)
  {
    printf(DUR_ERROR);
    return true;
  }

  return false;
}

/**
Checks if a string contains only lowercase letters and digits
@param name The string to be checked
@return true if the string contains characters other than lowercase
letters and digits, false otherwise
*/
bool lowercase_and_digits_check(const char* name)
{
  while (*name != '\0') {
    if (!islower(*name) && !isdigit(*name)) {
      return true;
    }
    name++;
  }
  return false;
}

/**
 * This function iterates over the sorted bus lines from the start to the end
and prints the name, distance, and duration of each bus line in the format
"name, distance, duration". The lines are assumed to be sorted in ascending
order by their name.
@param start Pointer to the first bus line in the sorted list.
@param end Pointer to the last bus line in the sorted list.
 @return This function does not return a value.

 */
void print_sorted_lines(BusLine* start,BusLine* end)
{
  BusLine* traveler = start;
  while (traveler != end)
  {
    printf("%s,%d,%d\n", traveler->name,traveler->distance,traveler->duration);
    traveler++;
  }
}

/**
copies the memory section of given array of BusLine structures,
Runs a series of tests on the given and copied array
@param start Pointer to the first BusLine structure in the array
@param end Pointer to the last BusLine structure in the array
@param n The number of BusLine structures in the array
@return int Returns 0 if all tests pass, otherwise returns 1
*/
int run_tests(BusLine* start,BusLine* end, long n)
{
  BusLine* copied_start = NULL;
  memcpy(copied_start,start,sizeof(BusLine)*n);
  if(copied_start == NULL)
  {
    return 1;
  }
  BusLine* copied_end = copied_start + n;
  distance_test (copied_start,copied_end);
  equal_test (copied_start,copied_end,start,end,TWO);
  duration_test (copied_start,copied_end);
  equal_test (copied_start,copied_end,start,end,FOUR);
  name_test (copied_start,copied_end);
  equal_test (copied_start,copied_end,start,end,SIX);
  free(copied_start);
  return 0;
}

/**
This function uses the quick sort algorithm to sort the
BusLines in the given range by distance, and then checks if the
resulting order is correct using the is_sorted_by_distance() function.
If the BusLines are sorted correctly, the function prints
 TEST_1_PASSED to stdout, otherwise it prints TEST_1_FAILED.
@param start A pointer to the first BusLine in the range.
@param end A pointer to one past the last BusLine in the range.
@return This function does not return a value.
*/
void distance_test(BusLine* start,BusLine* end)
{
  quick_sort(start,end, DISTANCE);
  if(is_sorted_by_distance(start,end))
  {
    printf (TEST_1_PASSED);
  }
  else
  {
    printf (TEST_1_FAILED);
  }
}

/**
This function uses the quick sort algorithm to sort the BusLines in the given range by duration, and then
checks if the resulting order is correct using the is_sorted_by_duration() function. If the BusLines are
sorted correctly, the function prints TEST_3_PASSED to stdout, otherwise it prints TEST_3_FAILED.
@param start A pointer to the first BusLine in the range.
@param end A pointer to one past the last BusLine in the range.
@return This function does not return a value.
*/
void duration_test(BusLine* start,BusLine* end)
{
  quick_sort(start,end, DURATION);
  if(is_sorted_by_duration(start,end))
  {
    printf (TEST_3_PASSED);
  }
  else
  {
    printf (TEST_3_FAILED);
  }
}

/**
This function uses the bubble sort algorithm to sort the BusLines in the given range by name, and then
checks if the resulting order is correct using the is_sorted_by_name() function. If the BusLines are
sorted correctly, the function prints TEST_5_PASSED to stdout, otherwise it prints TEST_5_FAILED.
@param start A pointer to the first BusLine in the range.
@param end A pointer to one past the last BusLine in the range.
@return This function does not return a value.
*/
void name_test(BusLine* start,BusLine* end)
{
  bubble_sort (start,end);
  if(is_sorted_by_name(start,end))
  {
    printf (TEST_5_PASSED);
  }
  else
  {
    printf (TEST_5_FAILED);
  }
}


/**
This function checks whether two arrays of BusLine structs are equal or not.
@param start_sorted - A pointer to the first BusLine struct in the sorted array.
@param end_sorted - A pointer to the last BusLine struct in the sorted array.
@param start_original - A pointer to the first BusLine struct in the original array.
@param end_original - A pointer to the last BusLine struct in the original array.
@param i - An integer representing the current test number.
@return This function does not return a value.
*/
void equal_test(BusLine *start_sorted,
                BusLine *end_sorted, BusLine *start_original,
                BusLine *end_original, int i)
{
  if(is_equal(start_sorted,end_sorted,start_original,end_original))
  {
    printf ("TEST %d PASSED: original and sorted arrays contain the same values", i);
  }
  else
  {
    printf ("TEST %d FAILED: some values are not equal between original and sorted array", i);
  }
}