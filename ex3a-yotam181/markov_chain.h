#ifndef _MARKOV_CHAIN_H_
#define _MARKOV_CHAIN_H_

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool

#define ALLOCATION_ERROR_MASSAGE "Allocation failure: Failed to allocate"\
            "new memory\n"

typedef struct MarkovNodeFrequency{
    struct MarkovNode* markov_node;
    unsigned int frequency;
}MarkovNodeFrequency;


typedef struct MarkovNode{
    char* data;
    MarkovNodeFrequency *frequencies_list;
    unsigned int f_list_size;
}MarkovNode;

typedef struct MarkovChain{
    LinkedList* database;
}MarkovChain;


/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return markov_node wrapping given data_ptr in given chain's database,
 * returns NULL in case of memory allocation failure.
 */
Node* add_to_database(MarkovChain *markov_chain, char *data_ptr);

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping it in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr);

/**
 * Add the second markov_node to the frequency list of the first markov_node.
 * If already in list, update it's occurrence frequency value.
 * @param first_node
 * @param second_node
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_frequencies_list(MarkovNode *first_node, MarkovNode *second_node);

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_database(MarkovChain ** ptr_chain);

/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */
MarkovNode* get_first_random_node(MarkovChain *markov_chain);

/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr);

/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_tweet(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);


/**
 * Create a new MarkovNode with the given data
 *
 * @param data the data for the new MarkovNode
 * @return a pointer to the newly created MarkovNode, or NULL if an error occurred
 */
MarkovNode* new_MarkovNode(char* data);

/**
 * Create a new MarkovNodeFrequency with the given MarkovNode
 *
 * @param markov_node the MarkovNode for the new MarkovNodeFrequency
 * @return a pointer to the newly created MarkovNodeFrequency, or NULL if an error occurred
 */
MarkovNodeFrequency* new_MarkovNodeFrequency(MarkovNode* markov_node);

/**
 * Free the memory allocated for the given MarkovNode
 *
 * @param node_to_free the MarkovNode to free
 */
void free_MarkovNode(MarkovNode* node_to_free);

/**
 * Create a new data string with the given word and length, allocating memory as necessary
 *
 * @param word the word to use as the new data string
 * @param length the length of the word to use as the new data string
 * @param max_length the maximum length of the new data string
 * @return a pointer to the newly created data string, or NULL if an error occurred
 */
char* new_data(char** word, int length, int max_length);

/**
 * Create a new MarkovChain with the given LinkedList
 *
 * @param LL the LinkedList to use as the database for the new MarkovChain
 * @return a pointer to the newly created MarkovChain, or NULL if an error occurred
 */
MarkovChain* new_MarkovChain(LinkedList* LL);

/**
 * Get a random number between 0 and max_number-1
 *
 * @param max_number the maximum number to return (not including)
 * @return a random number between 0 and max_number-1
 */
int get_random_number(int max_number);

/**
 * Check if the given word is the end of a sentence
 *
 * @param word the word to check
 * @return true if the word is the end of a sentence (i.e. ends with a period), false otherwise
 */
bool is_end_of_sentence(char* word);

/**
 * Create a new LinkedList
 *
 * @return a pointer to the newly created LinkedList, or NULL if an error occurred
 */
LinkedList* new_LinkedList(void);

/**
 * Print the data in the given MarkovChain
 *
 * @param markov_chain the MarkovChain to print
 */
void print_data_base(MarkovChain* markov_chain);




#endif /* _MARKOV_CHAIN_H_ */
