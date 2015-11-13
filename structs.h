#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

struct sentence
{
    char type;

    unsigned int indent ;
    unsigned long line_number;
    struct token * tokens_h;
    struct token * expression_h;
    struct sentence *  jump_target;//token value is true, jump to...
    struct sentence * next;//tokens value is false,jump to...

};

struct token
{
    char * token_string;
    int line_number;
    char type;//identifier keyword number...
    struct Constant * revelent_value;
    struct token * prev;//****
    struct token * next;
    struct token * child;
};




struct Function
{
    char type;
    struct Function * next;
};

struct Constant
{
    char type;
    void * value;
};



struct Variable
{
    char type;
    char * name;
    char * name_space;
    void * value;
    struct Variable * next;

};

    struct v_BignNum
    {
        unsigned char signs_posi;
        unsigned char * value;
        unsigned char * e_n;
    };

    struct v_Table
    {
        int clums;
        long int rows;
        char * name;

        long row_pointer;
    };

        struct table_Column_header
        {
            char * header;
            struct table_Column_header * next;
        };

    struct v_Array
    {
        char distinct;

    };

    struct v_Chain
    {

    };

    struct v_Dict_node
    {

    };



#endif // STRUCTS_H_INCLUDED



