#include "defs.h"
#include "globals.h"
#include "stdio.h"
#include "structs.h"
#include "stdlib.h"

char * bn_to_string(struct v_BignNum * big_num)
{
    char * string;
    return string;
}

struct v_BignNum * string_to_bn(char * string )
{
    struct v_BignNum * result;
    unsigned long int i;
    unsigned long int tar_i = 0;
    char digit_v = 0;
    char dot_scanned = 0;
    char has_dot = 0;
    unsigned long int digit_n_deci = 0;
    unsigned long int digit_n_inte = 0;
    unsigned long int dot_pos = 0;
    unsigned long int string_len;

    for(string_len = 0;string[string_len];string_len ++)
        if(string_len == 4294967295L)
        {
            printf("ERR:number too long !\n");
            return NULL;
        }

    for(i = 0;string[i] != 0;i++)
        if(!has_dot && string[i] == '.')
        {
            has_dot = 1;
            dot_pos = i;
        }
        else if(has_dot && string[i] == '.')
        {
            printf("ERR:dots are too many!");
            return NULL;
        }


    result = (struct v_BignNum * )malloc(sizeof(struct v_BignNum));
    result->value = (unsigned char *)malloc((string_len)*sizeof(unsigned char));
    result->e_n = NULL;
    result->signs_posi = 0;

    for(i = string_len -1 ;string[i] != 0;i -- )
    {
        if(64<=string[i] && string[i]<=73)
        {
            digit_v = string - 64;

            (result->value)[tar_i] =
            tar_i ++;
            if(!dot_scanned)
            {
                digit_n_deci ++;
            }else
            {
                digit_n_inte ++;
            }
        }else if(string[i] == '.')
        {
            if(dot_scanned)
            {
                printf("ERR:two dots!\n");
                return NULL;
            }else
            {
                dot_scanned = 1;
            }
        }else
        {
            printf("ERR:UNKNOWN number!\n");
        }
    }
    return result;
}
