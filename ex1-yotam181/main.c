#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#define RUN 5
#define TEST 2
#define MAX_LENGTH 1026
#define INPUT_FILE 3
#define OUTPUT_FILE 4
#define ARG_COMMAND 1
#define ARG_KEY 2
#define NUM_BASE 10
#define ENCODE_STR "encode"
#define DECODE_STR "decode"

// invalid input messages
#define INVALID_NUM_OF_ARGS "The program receives 1 or 4 arguments only.\n"
#define INVALID_TEST_INPUT "Usage: cipher test\n"
#define INVALID_COMMAND_INPUT "The given command is invalid.\n"
#define INDALID_KEY_INPUT "The given shift value is invalid.\n"
#define INVALID_FILE_INPUT "The given file is invalid.\n"





int validKey(char k[]);
void runCipher(char command[], char input[], char output[], int key);
int runTests();


int main (int argc, char *argv[])
{
    if(!(argc == RUN || argc == TEST))
    {
        fprintf(stderr, INVALID_NUM_OF_ARGS );
        return EXIT_FAILURE;
    }
    if(argc == TEST)
    {
        if((strcmp(argv[ARG_COMMAND], "test"))) {
            fprintf(stderr, INVALID_TEST_INPUT);
            return EXIT_FAILURE;
        }
        if (runTests())
        {
            return EXIT_FAILURE;
        }
    }
    if(argc == RUN)
    {
        if (strcmp(argv[ARG_COMMAND], DECODE_STR) && strcmp(argv[ARG_COMMAND], ENCODE_STR)) {
            fprintf(stderr, INVALID_COMMAND_INPUT);
            return EXIT_FAILURE;
        }
        if (!(validKey(argv[ARG_KEY]))) {
            fprintf(stderr, INDALID_KEY_INPUT);
            return EXIT_FAILURE;
        }
        FILE *o = fopen(argv[INPUT_FILE], "r");
        FILE *c = fopen(argv[OUTPUT_FILE], "w");
        if (o == NULL || c == NULL) {
            fprintf(stderr, INVALID_FILE_INPUT);
            return EXIT_FAILURE;
        }

        long key = strtol(argv[ARG_KEY], NULL, NUM_BASE);
        runCipher(argv[ARG_COMMAND], argv[INPUT_FILE], argv[OUTPUT_FILE], key);
    }
    return EXIT_SUCCESS;
}

void runCipher(char command[], char input[], char output[], int key)
{
    FILE *r = fopen(input,"r");
    FILE *w = fopen(output,"w");
    char text[MAX_LENGTH];
    if (!strcmp(command, ENCODE_STR))
    {
        while (fgets(text, MAX_LENGTH, r))
        {
            encode(text, key);
            fputs(text, w);
        }
    }
    else
    {
        while (fgets(text, MAX_LENGTH, r))
        {
            decode(text, key);
            fputs(text, w);
        }
    }
    fclose(r);
    fclose(w);
}

int runTests()
{
    int result =
            test_encode_non_cyclic_lower_case_positive_k() && test_encode_cyclic_lower_case_special_char_positive_k() ||
            test_encode_non_cyclic_lower_case_special_char_negative_k() && test_encode_cyclic_lower_case_negative_k() ||
            test_encode_cyclic_upper_case_positive_k() && test_decode_non_cyclic_lower_case_positive_k() ||
            test_decode_cyclic_lower_case_special_char_positive_k() ||
            test_decode_non_cyclic_lower_case_special_char_negative_k() && test_decode_cyclic_lower_case_negative_k() ||
            test_decode_cyclic_upper_case_positive_k();
    return result;
}

int validKey(char k[])
{
    if ((k[0] == '-') || isdigit(k[0]))
    {
        for (int i = 1; k[i] != '\0'; i++)
        {
            if (isdigit(k[i]) == 0)
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}

