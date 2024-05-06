#include "cipher.h"
#include "stdbool.h"

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.

#define ALPHABET 26
#define UPPER_CASE_START 64
#define UPPER_CASE_END 91
#define LOWER_CASE_START 96
#define LOWER_CASE_END 123



int validChar(char c);

// See full documentation in header file
void encode (char s[], int k)
{
    for(int i = 0; s[i] != '\0'; i++)
    {
        int charType = validChar(s[i]);
        if (charType)
        {
            if(charType == 1)
            {
                s[i] = (((s[i]-'A'+k)%ALPHABET+ALPHABET)%ALPHABET)+'A';
            }
            else
            {
                s[i] = (((s[i]-'a'+k)%ALPHABET+ALPHABET)%ALPHABET)+'a';

            }
        }
    }
}

// See full documentation in header file
void decode (char s[], int k)
{
  int decodeKey = -k;
    encode(s,decodeKey);
}


int validChar(char c)
{
    if ((c > UPPER_CASE_START & c < UPPER_CASE_END) || (c > LOWER_CASE_START  & c < LOWER_CASE_END))
    {
        if (c > UPPER_CASE_START & c < UPPER_CASE_END)  // upercase
        {
            return 1;
        }
        else  // lowercase
        {
            return 2;
        }
    }
    return 0; // invalid
}

