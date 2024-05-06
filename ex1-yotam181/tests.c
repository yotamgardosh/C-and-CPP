#include "tests.h"
#include <string.h>

#define K_1 3
#define NEG_K_1 -3



// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = "x#y";
    char out[] = "a#b";
    encode (in, K_1);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "d&gj";
    char out[] = "a&dg";
    encode (in, NEG_K_1);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
    char in[] = "ab";
    char out[] = "xy";
    encode (in, NEG_K_1);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
    char in[] = "ABC";
    char out[] = "DEF";
    encode (in, K_1);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
    char in[] = "def";
    char out[] = "abc";
    decode (in, K_1);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
    {
        char in[] = "a#b";
        char out[] = "x#y";
        decode (in, K_1);
        return strcmp (in, out) != 0;
    }
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "a&bc";
    char out[] = "d&ef";
    decode (in, NEG_K_1);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{
    char in[] = "xy";
    char out[] = "ab";
    encode (in, NEG_K_1);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{
    char in[] = "DEF";
    char out[] = "ABC";
    encode (in, K_1);
    return strcmp (in, out) != 0;
}
