#ifndef _MARKOV_CHAIN_H
#define _MARKOV_CHAIN_H

#include "linked_list.h"
#include <stdio.h>  // For printf(), sscanf()
#include <stdlib.h> // For exit(), malloc()
#include <stdbool.h> // for bool

#define ALLOCATION_ERROR_MASSAGE "Allocation failure: Failed to allocate new memory\n"


/***************************/
/*   insert typedefs here  */
/***************************/


/***************************/



/***************************/
/*        STRUCTS          */
/***************************/

typedef struct MarkovNodeFrequency{
    struct MarkovNode* markov_node;
    unsigned int frequency;
}MarkovNodeFrequency;


typedef struct MarkovNode {
    void* data;
    MarkovNodeFrequency *frequencies_list;
    unsigned int f_list_size;
} MarkovNode;

typedef struct NextNodeCounter {

} NextNodeCounter;


///
typedef void (*PrintFunc)(void*);
typedef int (*CompFunc)(const void*, const void*);
typedef void (*FreeData)(void*);
typedef void* (*CopyFunc)(const void*);
typedef bool (*IsLast)(const void*);
///

/* DO NOT ADD or CHANGE variable names in this struct */
typedef struct MarkovChain {
    LinkedList *database;

    // pointer to a func that receives data from a generic type and prints it
    // returns void.
    PrintFunc print_func;

    // pointer to a func that gets 2 pointers of generic data type(same one) and compare between them */
    // returns: - a positive value if the first is bigger
    //          - a negative value if the second is bigger
    //          - 0 if equal
    CompFunc comp_func;

    // a pointer to a function that gets a pointer of generic data type and frees it.
    // returns void.
    FreeData free_data;

    // a pointer to a function that  gets a pointer of generic data type and returns a newly allocated copy of it
    // returns a generic pointer.
    CopyFunc copy_func;

    //  a pointer to function that gets a pointer of generic data type and returns:
    //      - true if it's the last state.
    //      - false otherwise.
    IsLast is_last;
} MarkovChain;

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
 * @param first_node markov_node to start with, if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */
void generate_tweet(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length);

/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_database(MarkovChain **markov_chain);

/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @param markov_chain
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */
bool add_node_to_frequencies_list(MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain);

/**
* Check if data_ptr is in database. If so, return the markov_node wrapping it in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr);

/**
* If data_ptr in markov_chain, return it's node. Otherwise, create new
 * node, add to end of markov_chain's database and return it.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return node wrapping given data_ptr in given chain's database
 */
Node* add_to_database(MarkovChain *markov_chain, void *data_ptr);

/**
* Get random number between 0 and max number [0, max number).
* @param max number maximal number to return (not including)
* @return Random number
*/
int get_random_number(int max_number);

///////////////////////////////////
    // functions i added //
//////////////////////////////////

/**
 * Create a new MarkovChain with the given LinkedList and function pointers
 *
 * @param LL the LinkedList to use as the database for the new MarkovChain
 * @return a pointer to the newly created MarkovChain, or NULL if an error occurred
 */
MarkovChain* new_markov_chain(LinkedList* LL,
                              PrintFunc print_func,
                              CompFunc comp_func,
                              FreeData free_data,
                              CopyFunc copy_func,
                              IsLast is_last);

/**
 * Create a new LinkedList
 *
 * @return a pointer to the newly created LinkedList, or NULL if an error occurred
 */
LinkedList* new_linked_list(void);


/**
 * Check if the given word is the end of a sentence
 *
 * @param word the word to check
 * @return true if the word is the end of a sentence (i.e. ends with a period), false otherwise
 */
bool is_end_of_sentence(const void* data);

/**
 * Create a new data string with the given word and length, allocating memory as necessary
 *
 * @param word the word to use as the new data string
 * @param length the length of the word to use as the new data string
 * @param max_length the maximum length of the new data string
 * @return a pointer to the newly created data string, or NULL if an error occurred
 */
void* new_data(char** word, int length, int max_length);





#endif /* _MARKOV_CHAIN_H */