#include"globals.h"
#include"defs.h"
#include"stdlib.h"
#include"structs.h"
#include <stdio.h>
#include <string.h>

void variable_append(struct Variable ** p_Variables_h, struct Constant * val_Constant,char * name)//name space is current name space
{
    struct Variable * Variables_list = * p_Variables_h;
    struct Variable * p_new_var_node = NULL;
    struct Variable * p_Variable = * p_Variables_h;
    struct Variable ** pp_Variable = p_Variables_h;
    struct Variable * p_last_Variable = NULL;

    p_new_var_node = (struct Variable *)malloc(sizeof(struct Variable));

    p_new_var_node->name = NULL;
    p_new_var_node->name_space = NULL;
    p_new_var_node->next = NULL;

    //////following is wrong !
    p_new_var_node->type = val_Constant->type;

    p_new_var_node->value = val_Constant->value;//the value should not be freed!
    val_Constant->value = NULL;//prevent from freed

    p_new_var_node->name = (char *)malloc(strlen(name)+1);
    strcpy(p_new_var_node->name,name);
    p_new_var_node->name_space = (char * )malloc(strlen(CurrentNameSpace)+1);
    strcpy(p_new_var_node->name_space,CurrentNameSpace);
    //attention! when face strcopy, the called memory should be strlen() +1 !!!!!!!!!!
    //check all !!!!!
    //may overflow!

    while(*pp_Variable != NULL)
    {
            if(!strcmp(p_Variable->name,name) && !strcmp(p_Variable->name_space,CurrentNameSpace));
            {
                printf("ERR:Variable Already Exist!\n");
            }
        pp_Variable = &((* pp_Variable)->next);
    }
    *pp_Variable = p_new_var_node;


}


void print_variables(struct Variable * Variables_h)
{
    struct Variable * p_Variable;
    for(p_Variable = Variables_h;p_Variable!=NULL;p_Variable = p_Variable->next)
    {
        printf("Var: %s\t N_S: %s\t",p_Variable->name,p_Variable->name_space);
        switch(p_Variable->type)
        {
            case VAL_TYPE_FLOAT: printf("Type: FLOAT \tValue: %lf\t\n",*(double *)p_Variable->value);break;
            case VAL_TYPE_INT  : printf("Type: INT \tValue: %ld\t\n",*(long int *)p_Variable->value);break;
            case VAL_TYPE_L_FLOAT  : printf("Type: LONG_F \tValue: %llf\t\n",*(long double *)p_Variable->value);break;
            case VAL_TYPE_STRING :  printf("Type: STRING \tValue: %s\t\n",(char *)p_Variable->value);break;
            default : printf("UNKNOWN TYPE %d\n",p_Variable->type);
        }
    }
}



