#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"

#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))

#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20

#define THREE 3
#define USAGE "Usage: the number of args was invalid"
#define BASE 10
#define ALOC "Allocation failure: unable to properly allocate memory "
#define NUM_T0_GENERATE 2
#define MEA 100


// function declaration
static int valid_num_of_args(int argc);
static bool is_last(const void* data);
static void* copy_func(const void* data);
static int comp_func(const void* data1, const void* data2);
static void print_func(void* data);
static int valid_num_of_args(int argc);



/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder in case there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
static int handle_error(char *error_msg, MarkovChain **database)
{
    printf("%s", error_msg);
    if (database != NULL)
    {
        free_database(database);
    }
    return EXIT_FAILURE;
}


static int create_board(Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            handle_error(ALLOCATION_ERROR_MASSAGE,NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }
    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
static int fill_database(MarkovChain *markov_chain)
{
    Cell* cells[BOARD_SIZE];
    if(create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        add_to_database(markov_chain, cells[i]);
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain,cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain, cells[index_to])
                    ->data;
            add_node_to_frequencies_list (from_node, to_node, markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell*) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(markov_chain, cells[index_to])
                        ->data;
                add_node_to_frequencies_list (from_node, to_node, markov_chain);
            }
        }
    }
    // free temp arr
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        free(cells[i]);
    }
    return EXIT_SUCCESS;
}

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc, char *argv[])
{
  if(valid_num_of_args (argc))
  {
    return EXIT_FAILURE;
  }
  srand (strtol (argv[1], NULL, BASE));
  LinkedList* ll = new_linked_list ();
  if(ll == NULL)
  {
    printf(ALOC);
    return EXIT_FAILURE;
  }
  MarkovChain* mc = new_markov_chain (ll, print_func, comp_func, free,
                                      copy_func, is_last);
  if(mc == NULL)
  {
    free(ll);
    printf(ALOC);
    return EXIT_FAILURE;
  }
  int filled_bool = fill_database (mc);
  if(filled_bool == EXIT_FAILURE)
  {
    printf(ALOC);
    free_database(&mc);
    return EXIT_FAILURE;
  }
  for(int i = 1; i <= strtol (argv[NUM_T0_GENERATE], NULL, BASE); i++)
  {
    MarkovNode * node_one = mc->database->first->data;
    printf ("Random Walk %d: ", i);
    generate_tweet(mc, node_one, MAX_GENERATION_LENGTH);
  }
  free_database (&mc);
  return EXIT_SUCCESS;

}



static int valid_num_of_args(int argc)
{
  if(argc != THREE)
  {
    printf(USAGE);
    return 1;
  }
  return 0;
}


static void print_func(void* data)
{
  Cell* cell_to_print = data;
  if(cell_to_print->ladder_to != EMPTY)
  {
      printf("[%d]-ladder to %d -> ", cell_to_print->number,cell_to_print->ladder_to);
      return;
  }
  if(cell_to_print->snake_to != EMPTY)
  {
      printf("[%d]-snake to %d -> ", cell_to_print->number,cell_to_print->snake_to);
      return;
  }
  if(cell_to_print->number == MEA)
  {
      printf ("[%d]",cell_to_print->number);
      return;
  }
  printf("[%d] -> ", cell_to_print->number);
}

static int comp_func(const void* data1, const void* data2)
{
  const Cell* word1 = data1;
  const Cell* word2 = data2;
  return word1->number - word2->number;
}


static void* copy_func(const void* data)
{
  const Cell* cell_to_copy = data;
  Cell* copy_to = malloc (sizeof (Cell));
  if(!copy_to)
  {
    return NULL;
  }
  memcpy(copy_to, cell_to_copy, sizeof (Cell));
  void* return_data = (void*) copy_to;
  return return_data;
}

static bool is_last(const void* data)
{
    const Cell* cell = data;
    bool res = (cell->number == MEA);
    return res;
}
