#include "globals.h"
#include "structs.h"
#include "defs.h"
#include <stdlib.h>


struct Constant * Op_plus(struct Constant * a, struct Constant * b)
{
    struct Constant * result = NULL;
    long int int_a = 0;
    long int int_b = 0;
    double float_a = 0.0;
    double float_b = 0.0;
    result = (struct Constant *)malloc(sizeof(struct Constant));
    result->type =0;
    result->value = NULL;
    if(a->type == VAL_TYPE_INT && b->type == VAL_TYPE_INT)
    {
        int_a = *((long int *)(a->value));
        int_b = *((long int *)(b->value));

        if((int_b > 0 &&  int_a <= LIM_INT_MAX - int_b) || (int_b < 0 && int_a >= LIM_INT_MIN - int_a) || (int_b == 0))
        {
            result->type = VAL_TYPE_INT;
            result->value = malloc(sizeof(long int));
            *((long int *)(result->value)) = int_a + int_b;
        }else
        {
            printf("ERR:INT OVERFLOW!\n");

        }
    }
    else if(a->type == VAL_TYPE_INT && b->type == VAL_TYPE_FLOAT)
    {
        int_a = *((long int *)(a->value));
        float_a = (double)int_a;
        float_b = *((double*)(b->value));

        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a + float_b;
        }
    }
    else if(b->type == VAL_TYPE_INT && a->type == VAL_TYPE_FLOAT)
    {
        int_b = *((long int *)(b->value));
        float_b = (double)int_b;
        float_a = *((double *)(a->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a + float_b;
        }
    }
    else if(a->type == VAL_TYPE_FLOAT && b->type == VAL_TYPE_FLOAT)
    {
        float_b = *((double *)(b->value));
        float_a = *((double *)(a->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a + float_b;
        }
    }
    else
    {
        printf("ERR:Not supported type in plus operation.\n");
    }
    
    return result;
}


struct Constant * Op_minus(struct Constant * a, struct Constant * b)
{
    struct Constant * result = NULL;
    long int int_a = 0;
    long int int_b = 0;
    double float_a = 0.0;
    double float_b = 0.0;
    result = (struct Constant *)malloc(sizeof(struct Constant));
    result->type =0;
    result->value = NULL;
    if(a->type == VAL_TYPE_INT && b->type == VAL_TYPE_INT)
    {
        int_a = *((long int *)(a->value));
        int_b = *((long int *)(b->value));

        if((int_b > 0 && int_a >= LIM_INT_MIN + int_b ) || (int_b < 0 && int_a <= LIM_INT_MAX + int_b) || (int_b == 0))
        {
            result->type = VAL_TYPE_INT;
            result->value = malloc(sizeof(long int));
            *((long int *)(result->value)) = int_a - int_b;
        }else
        {
            printf("ERR:INT OVERFLOW!\n");

        }
    }
    else if(a->type == VAL_TYPE_INT && b->type == VAL_TYPE_FLOAT)
    {
        int_a = *((long int *)(a->value));
        float_a = (double)int_a;
        float_b = *((double *)(b->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a - float_b;
        }
    }
    else if(b->type == VAL_TYPE_INT && a->type == VAL_TYPE_FLOAT)
    {
        int_b = *((long int *)(b->value));
        float_b = (double)int_b;
        float_a = *((double *)(a->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a - float_b;
        }
    }
    else if(a->type == VAL_TYPE_FLOAT && b->type == VAL_TYPE_FLOAT)
    {
        float_b = *((double *)(b->value));
        float_a = *((double *)(a->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a - float_b;
        }
    }
    else
    {
        printf("ERR:Not supported type in minus operation.\n");
    }
    return result;

}


struct Constant * Op_multiplied_by(struct Constant * a, struct Constant * b)
{
    struct Constant * result = NULL;
    long int int_a = 0;
    long int int_b = 0;
    double float_a = 0.0;
    double float_b = 0.0;
    result = (struct Constant *)malloc(sizeof(struct Constant));
    result->type =0;
    result->value = NULL;
    
    if(a->type == VAL_TYPE_INT && b->type == VAL_TYPE_INT)
    {
        int_a = *((long int *)(a->value));
        int_b = *((long int *)(b->value));
        

        result->type = VAL_TYPE_INT;
        result->value = malloc(sizeof(long int));
        *((long int *)(result->value)) = int_a * int_b;

    }
    else if(a->type == VAL_TYPE_INT && b->type == VAL_TYPE_FLOAT)
    {
        int_a = *((long int *)(a->value));
        float_a = (double)int_a;
        float_b = *((double *)(b->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a * float_b;
        }
    }
    else if(b->type == VAL_TYPE_INT && a->type == VAL_TYPE_FLOAT)
    {
        int_b = *((long int *)(b->value));
        float_b = (double)int_b;
        float_a = *((double *)(a->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a * float_b;
        }
    }
    else if(a->type == VAL_TYPE_FLOAT && b->type == VAL_TYPE_FLOAT)
    {
        float_b = *((double *)(b->value));
        float_a = *((double *)(a->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a * float_b;
        }
    }
    else
    {
        printf("ERR:Not supported type in multiple operation.\n");
        
    }
    return result;

}

struct Constant * Op_divided_by(struct Constant * a, struct Constant * b)
{
    struct Constant * result = NULL;
    long int int_a = 0;
    long int int_b = 0;
    double float_a = 0.0;
    double float_b = 0.0;
    result = (struct Constant *)malloc(sizeof(struct Constant));
    result->type =0;
    result->value = NULL;

    if(a->type == VAL_TYPE_INT && b->type == VAL_TYPE_INT)
    {
        int_a = *((long int *)(a->value));
        int_b = *((long int *)(b->value));
        
        
        result->type = VAL_TYPE_INT;
        result->value = malloc(sizeof(long int));
        *((long int *)(result->value)) = int_a / int_b;
        
    }
    else if(a->type == VAL_TYPE_INT && b->type == VAL_TYPE_FLOAT)
    {
        int_a = *((long int *)(a->value));
        float_a = (double)int_a;
        float_b = *((double *)(b->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a / float_b;
        }
    }
    else if(b->type == VAL_TYPE_INT && a->type == VAL_TYPE_FLOAT)
    {
        int_b = *((long int *)(b->value));
        float_b = (double)int_b;
        float_a = *((double *)(a->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a / float_b;
        }
    }
    else if(a->type == VAL_TYPE_FLOAT && b->type == VAL_TYPE_FLOAT)
    {
        float_b = *((double *)(b->value));
        float_a = *((double *)(a->value));
        if(1)
        {
            result->type = VAL_TYPE_FLOAT;
            result->value = malloc(sizeof(double));
            *((double *)(result->value)) = float_a / float_b;
        }
    }
    else
    {
        printf("ERR:Not supported type in divide operation.\n");
        
    }
    return result;
}








