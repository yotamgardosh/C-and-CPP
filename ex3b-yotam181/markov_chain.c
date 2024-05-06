#include "markov_chain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// max for word is 100, max words per tweet is 20
#define MAX_TWEET_LENGTH 2000


int count_words_in_tweet(char* tweet);

/**
 generates a new tweet using the given MarkovChain and starting from the
 given or a random MarkovNode, with the maximum length specified.
 - for full documentation see header file

    *updated*
 */


void generate_tweet(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
  int count = 1;
  MarkovNode* word_node = NULL;
  if(first_node == NULL)
  {
    word_node = get_first_random_node (markov_chain);
  }
  else
  {
    word_node = first_node;
  }
  markov_chain->print_func(word_node->data);
  while ((!(markov_chain->is_last(word_node->data))) && count < max_length)
  {
    word_node = get_next_random_node(word_node);
    if(!word_node)
    {
      return;
    }
    markov_chain->print_func(word_node->data);
    count++;
  }
  printf ("\n");
}

/**
   randomly selects a next MarkovNode based on the given MarkovNode's
   frequencies list.
 - for full documentation see header file

    *updated (? didnt change anything so not sure if its ok ?) *
 */
MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr)
{
  unsigned int count = 0;
  for (unsigned int i = 0; i < state_struct_ptr->f_list_size; i++)
  {
    count += state_struct_ptr->frequencies_list[i].frequency;
  }
  int random_num = get_random_number (count);
  MarkovNode** words_arr = malloc (count * sizeof(*words_arr));
  if(!words_arr)
  {
    printf (ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  unsigned int k = 0;
  for (unsigned int i = 0; i < state_struct_ptr->f_list_size; i++)
  {
    for(unsigned int j = 0; j < state_struct_ptr->frequencies_list[i]
    .frequency; j++)
    {
        words_arr[k+j] = state_struct_ptr->frequencies_list[i]
            .markov_node;
    }
    k += state_struct_ptr->frequencies_list[i].frequency;
  }
  MarkovNode* selected_node = words_arr[random_num];
  free(words_arr);
  return selected_node;
}


/**
 randomly selects the first MarkovNode of a new tweet based on the
 given MarkovChain's database.
 - for full documentation see header file

    *updated*
 */
MarkovNode* get_first_random_node(MarkovChain *markov_chain)
{
  LinkedList* data_base_p = markov_chain->database;
  Node* trav = data_base_p->first;
  unsigned int count = 0;
  unsigned int random_num = get_random_number (data_base_p->size);
  while (true)
  {
    if(count == random_num)
    {
      if(markov_chain->is_last(trav->data->data))
      {
        random_num = get_random_number (data_base_p->size);
        count = 0;
        trav = data_base_p->first;
      }
      else
      {
        return trav->data;
      }
    }
    else
    {
    trav = trav->next;
    count++;
    }
  }
}

/**
* Get random number between 0 and max number [0, max number).
* @param max number maximal number to return (not including)
* @return Random number
*/
int get_random_number(int max_number)
{
  return rand () % max_number;
}

/**
   creates a new empty LinkedList.
 - for full documentation see header file
 */
LinkedList* new_linked_list()
{
  LinkedList* linked_list = malloc (sizeof (LinkedList));
  if(!linked_list)
  {
    return NULL;
  }
  linked_list->first = NULL;
  linked_list->last = NULL;
  linked_list->size = 0;
  return linked_list;
}

/**
   creates a new MarkovChain with the given LinkedList as the database.
 - for full documentation see header file
 */
MarkovChain * new_markov_chain(LinkedList* LL,
                               PrintFunc print_func,
                               CompFunc comp_func,
                               FreeData free_data,
                               CopyFunc copy_func,
                               IsLast is_last)
{
  MarkovChain * chain = malloc (sizeof(MarkovChain));
  if(!chain)
  {
    return NULL;
  }
  *chain = (MarkovChain) {LL, print_func, comp_func, free_data, copy_func,
                           is_last };
  return chain;

}

/**
   creates a new string and copies the content of the given word string to it, with the specified length and maximum length.
 - for full documentation see header file
 */
void* new_data(char** word, int word_length, int max_length)
{
  void* data = malloc (max_length);
  if(!data)
  {
    return NULL;
  }
  memcpy (data,*word,word_length + 1);
  *word = NULL; // added
  return data;
}

/**
 creates a new MarkovNode with the given data string
 - for full documentation see header file

    *updated*
 */
MarkovNode* new_markov_node(void* data, MarkovChain* mc)
{
  MarkovNode* node_ptr = malloc (sizeof (MarkovNode));
  if(!node_ptr)
  {
    return NULL;
  }
  node_ptr->data = mc->copy_func(data);
  if(!node_ptr->data)
  {
    return NULL;
  }
  node_ptr->frequencies_list = NULL;
  node_ptr->f_list_size = 0;
  return node_ptr;
}

/**
   creates a new MarkovNodeFrequency with the given MarkovNode.
 - for full documentation see header file
 */
MarkovNodeFrequency * new_markov_node_frequency(MarkovNode* markov_node)
{
  MarkovNodeFrequency * f_node_ptr = malloc (sizeof (MarkovNodeFrequency)); //2
  if(!f_node_ptr)
  {
    return NULL;
  }
  f_node_ptr->markov_node = markov_node;
  f_node_ptr->frequency = 1;
  return f_node_ptr;
}

/**
 Returns a node from a given chain's database,
 creates a new node if it doesn't exist.
 Returns NULL if memory allocation fails.
 - for full documentation see header file

    *updated*
 */
Node* add_to_database(MarkovChain *markov_chain, void *data_ptr)
{
  Node* ptr_trav = markov_chain->database->first;
  while(ptr_trav != NULL)
  {
    if(markov_chain->comp_func(ptr_trav->data->data,data_ptr) == 0) // changed to mc func
    {
      return ptr_trav;
    }
    ptr_trav = ptr_trav->next;
  }
  MarkovNode* m_node = new_markov_node (data_ptr, markov_chain);
  if(!m_node)
  {
    return NULL;
  }
  // add node to linked list
  int result_bool = add(markov_chain->database,m_node);
  if(result_bool) // 1 if results failed else 0
  {
    markov_chain->free_data(m_node);
    // not sure if need to change to mc func since m_node is not a void*
    // update: changed, have not run test yet
    return NULL;
  }
  return markov_chain->database->last;
}

/**
 Checks if a given state is in the database of a given chain.
 Returns a pointer to the node, or NULL if not in the database.
 - for full documentation see header file

    *updated*
 */
Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr)
{
  Node* ptr_trav = markov_chain->database->first;
  while(ptr_trav != NULL)
  {
    if(markov_chain->comp_func(ptr_trav->data->data,data_ptr) == 0)
    {
      return ptr_trav;
    }
    ptr_trav = ptr_trav->next;
  }
  return NULL;
}

/**
 Adds the second node to the frequency list of the first node,
 or updates the frequency value if it already exists.
 Returns true on success, false on allocation error.
 - for full documentation see header file

    *updated*
 */
bool add_node_to_frequencies_list(MarkovNode *first_node, MarkovNode
*second_node, MarkovChain *markov_chain)
{
  // if word is the end of a sentence
  if(markov_chain->is_last(first_node->data)) // changed to mc func
  {
    return true;
  }
  // if there is no nodes in the list
  if(first_node->frequencies_list == NULL)
  {
    first_node->frequencies_list = new_markov_node_frequency (second_node);
    if(first_node->frequencies_list == NULL)
    {
      return false;
    }
    first_node->f_list_size = 1;
    return true;
  }
  // looking for word in list
  for(unsigned int i = 0; i < first_node->f_list_size; i++)
  {
    if(first_node->frequencies_list[i].markov_node == second_node)
    {
      first_node->frequencies_list[i].frequency += 1;
      return true;
    }
  }
  // resize the list and add to the end new markov node
  MarkovNodeFrequency *temp = realloc (first_node->frequencies_list, sizeof
  (MarkovNodeFrequency)*(first_node->f_list_size+1));
  if(!temp)
  {
    return false;
  }
  first_node->frequencies_list = temp;
  MarkovNodeFrequency* node_to_add = new_markov_node_frequency (second_node);
  if(!node_to_add)
  {
    return false;
  }
  first_node->frequencies_list[first_node->f_list_size] = *node_to_add;
  first_node->f_list_size += 1;
  markov_chain->free_data(node_to_add); // changed to mc func
  // not sure if neede to change since its not a void*
  // maybe return to free()
  return true;
}

/**
   Frees a given markov_chain and all of its content from memory.
 - for full documentation see header file

    *updated*
 */
void free_database(MarkovChain ** ptr_chain)
{
  MarkovChain* chain_to_free = *ptr_chain;
  Node * cur = chain_to_free->database->first;
  Node * next = NULL;
  while (cur != NULL)
  {
    next = cur->next;
    chain_to_free->free_data((cur->data->frequencies_list));
    chain_to_free->free_data(cur->data->data);
    chain_to_free->free_data(cur->data);
    chain_to_free->free_data(cur); // free node
    cur = next;
  }
  chain_to_free->free_data(chain_to_free->database); // free linked list
  free(chain_to_free);  // free markov chain  ##### check if necessary #####

}

void initialize_markov_chain (MarkovChain * markov_chain,
                              PrintFunc print_func,
                              CompFunc comp_func,
                              FreeData free_data,
                              CopyFunc copy_func,
                              IsLast is_last)

{
  markov_chain->print_func = print_func;
  markov_chain->comp_func = comp_func;
  markov_chain->free_data = free_data;
  markov_chain->copy_func = copy_func;
  markov_chain->is_last = is_last;
}
