#include "linked_list.h"
#include "markov_chain.h"

#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool
#include <string.h>


#define FILE_ADDRESS 3
#define USAGE "Usage: the number of args was invalid"
#define FILE_ERROR "Error: unable to open text file"
#define ALOC "Allocation failure: unable to properly allocate memory "
#define BUFFER 1000
#define MAX_LENGTH 100
#define MAX_LENGTH_TWEET 20
#define BASE 10
#define NUM_OF_TWEETS 2
#define ARBA 4
#define CHAMSA 5
#define NO_INPUT -1

void print_data_base(MarkovChain *markov_chain);

// function definition
/**
 * Reads words from the text corpus file and adds them to the Markov chain
 * database. The number of words to read can be specified, or if set to -1,
 * reads all words in the file. Returns EXIT_SUCCESS on success, and
 * EXIT_FAILURE on failure.
 *
 * @param fp The file pointer to the text corpus file to read from.
 * @param words_to_read The number of words to read from the file, or -1 to
 *                      read all words.
 * @param markov_chain A pointer to the Markov chain database to add the
 *                     read words to.
 * @return EXIT_SUCCESS on success, and EXIT_FAILURE on failure.
 */
int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain);

/**
 * Validates the number of arguments passed to the program. Prints an error
 * message to stdout and returns 1 if the number of arguments is invalid,
 * otherwise returns 0.
 *
 * @param argc The number of arguments passed to the program.
 * @return 1 if the number of arguments is invalid, 0 otherwise.
 */
int valid_num_of_args(int argc);

/**
 * Validates that the text corpus file at the given file address exists and
 * is readable. Prints an error message to stdout and returns 1 if the file
 * is invalid, otherwise returns 0.
 *
 * @param file_address The file address of the text corpus file to validate.
 * @return 1 if the file is invalid, 0 otherwise.
 */
int valid_text_file(const char* file_address);

/**
 * Reads words from the text corpus file and adds them to the Markov chain
 * database. The number of words to read can be specified, or if set to -1,
 * reads all words in the file. Returns EXIT_SUCCESS on success, and
 * EXIT_FAILURE on failure.
 *
 * @param fp The file pointer to the text corpus file to read from.
 * @param words_to_read The number of words to read from the file, or -1 to
 *                      read all words.
 * @param markov_chain A pointer to the Markov chain database to add the
 *                     read words to.
 * @return EXIT_SUCCESS on success, and EXIT_FAILURE on failure.
 */
int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain);

/**
 * Decrements the given counter, unless it is -1, in which case it does nothing.
 * Returns the updated value of the counter.
 *
 * @param counter The counter to update.
 * @return The updated value of the counter.
 */
int update_words_to_read(int counter);



/*
 * args:
 * 1. seed
 * 2. num of tweets to generate
 * 3. path to text file
 * 4. [optional] num of words to process from file. if missing process all
 *               words to markov_chain
 */


/*
 * TO DO:
 * 1. add implementation in main when max words to read is inputted and not V
 * 2. add message for allocation failure  V
 * 3. add part with seed
 */

int main (int argc, char *argv[])
{
  if(valid_num_of_args (argc))
  {
    return EXIT_FAILURE;
  }
  if(valid_text_file (argv[FILE_ADDRESS]))
  {
    return EXIT_FAILURE;
  }
  srand (strtol (argv[1], NULL, BASE));
  FILE *text_corpus = fopen(argv[FILE_ADDRESS], "r");
  LinkedList* ll = new_LinkedList();
  if(ll == NULL)
  {
    printf(ALOC);
    return EXIT_FAILURE;
  }
  MarkovChain* mc = new_MarkovChain (ll);
  if(mc == NULL)
  {
    printf(ALOC);
    return EXIT_FAILURE;
  }
  int filled_bool = 0; //
  if(argc == 4) // num of words to process was not inputted
  {
    filled_bool = fill_database (text_corpus, NO_INPUT, mc);
  }
  else
  {
    long num_words = strtol (argv[4], NULL, BASE);
    filled_bool = fill_database (text_corpus, num_words , mc);
  }
  fclose (text_corpus);
  if(filled_bool == EXIT_FAILURE)
  {
    printf(ALOC);

    free_database(&mc);
    return EXIT_FAILURE;
  }
  for(int i = 1; i <= strtol (argv[NUM_OF_TWEETS], NULL, BASE); i++)
  {
    printf ("Tweet %d: ", i);
    generate_tweet (mc, NULL, MAX_LENGTH_TWEET);
  }
  free_database (&mc);
  return EXIT_SUCCESS;
}

// handle words_to_read from main, if 3 args are given then summons function
// with words to add as -1
int fill_database(FILE *fp, int words_to_read, MarkovChain *markov_chain)
{
  char line_from_file[BUFFER];
  MarkovNode * word1 = NULL;
  MarkovNode * word2 = NULL;
  bool flag2 = true;
  void* flag = fgets (line_from_file, BUFFER, fp);
  char* parsed_word = strtok (line_from_file, "\n \r");
  char* data = new_data (&parsed_word, strlen(parsed_word) + 1, MAX_LENGTH);
  if(!data)
  {
    return EXIT_FAILURE;
  }
  Node* added1 = add_to_database (markov_chain, data);
  if(!added1)
  {
    return EXIT_FAILURE;
  }
  word1 = added1->data;
  words_to_read = update_words_to_read (words_to_read);
  while(words_to_read && flag)
  {
    while (words_to_read)
    {
      if(flag2)
      {
        parsed_word = strtok (NULL, "\n \r");
      }
      else
      {
        parsed_word = strtok (line_from_file, "\n \r");
        flag2 = true;
      }
      if(parsed_word == NULL)
      {
        break;
      }
      data = new_data (&parsed_word, strlen(parsed_word) + 1, MAX_LENGTH);
      Node* added2 = add_to_database (markov_chain, data);
      if(!added2)
      {
        return EXIT_FAILURE;
      }
      word2 = added2->data;
      add_node_to_frequencies_list (word1, word2);
      word1 = word2;
      words_to_read = update_words_to_read (words_to_read);
    }
    flag = fgets (line_from_file, BUFFER, fp);
    flag2 = false;
  }
  return EXIT_SUCCESS;
}

int update_words_to_read(int counter)
{
  if(counter != -1)
  {
    counter--;
  }
  return counter;
}

int valid_text_file(const char* file_address)
{
  FILE *text_corpus = fopen(file_address, "r");
  if(text_corpus == NULL)
  {
    fclose (text_corpus);
    printf (FILE_ERROR);
    return 1;
  }
  fclose (text_corpus);
  return 0;
}

int valid_num_of_args(int argc)
{
  if(!(argc == CHAMSA || argc == ARBA))
  {
    printf(USAGE);
    return 1;
  }
  return 0;
}


