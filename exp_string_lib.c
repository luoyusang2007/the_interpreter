#include "globals.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void str_self_trim(char string[])
{
    int start ;
    int end;
    int i;

    for(start = 0; string[start]== ' ';start++); //Attention Linux...
    printf("start:%d\n",start);
    for(end  = strlen(string)-1;( string[end]== ' ' || string[end]== '\n' )&& end  >= start; end--);
    printf("end:%d\n",end);
    for (i = start; i<end + 1 ; i ++ )
        string[i-start] = string[i];
    string[i-start] = '\0';
}

void str_self_release(char string[])
{
    printf("#DEB function str_self_release called !\n");
    //will it work?
    int len = strlen(string);
    string = (char * )realloc(string,sizeof(char)*(len+1));
    string[len] = 0;
}


int get_line_indent_class(int table_len, char * string){
    int i;
    int space_amount = 0;
    int table_amount = 0;
    for(i = 0; string[i] == ' ' || string[i] == '\t';i++){
        if(string[i] == ' '){
            if(space_amount == table_len - 1){
                space_amount = 0;
                table_amount ++;

            }else{
                space_amount ++;
            }
        }else if (string[i] == '\t'){
            space_amount = 0;
            table_amount ++;
        }
    }
    return table_amount * table_len + space_amount ;
}





char str_is_real_quote(char string[],int i)
{
    int counter;
    for(i--,counter=0;string[i]=='\\';counter++,i--);

    if(counter%2)
        return 0;
    else
        return 1;//string[i] is not escaped,it is a real quote.
}



char str_char_is_num(char c)//0~9
{
    switch (c)
    {
        case '.':;
        case '0':;
        case '1':;
        case '2':;
        case '3':;
        case '4':;
        case '5':;
        case '6':;
        case '7':;
        case '8':;
        case '9':return 1;break;
    }
    return 0;
}

char str_char_is_eng(char c)//include '_'
{
     switch (c)
    {
        case 'a':;case 'b':;case 'c':;case 'd':;
        case 'e':;case 'f':;case 'g':;case 'h':;
        case 'i':;case 'j':;case 'k':;case 'l':;
        case 'm':;case 'n':;case 'o':;case 'p':;
        case 'q':;case 'r':;case 's':;case 't':;
        case 'u':;case 'v':;case 'w':;case 'x':;
        case 'y':;case 'z':;case 'A':;case 'B':;
        case 'C':;case 'D':;case 'E':;case 'F':;
        case 'G':;case 'H':;case 'I':;case 'J':;
        case 'K':;case 'L':;case 'M':;case 'N':;
        case 'O':;case 'P':;case 'Q':;case 'R':;
        case 'S':;case 'T':;case 'U':;case 'V':;
        case 'W':;case 'X':;case 'Y':;case 'Z':;
        case '_':;case '$':case '@':return 1;break;
    }
    return 0;
}

char str_char_is_op_symbol(char c)
{
    switch(c)
    {
        case '+':;case '-':;
        case '*':;case '/':;
        case '%':;case '~':;
        case ':':;case '>':;
        case '<':;case '|':;
        case '&':;case '!':;
        case '=':;
        return 1;
    }
    return 0;
}

char str_char_is_div_symbol(char c)
{
        switch(c)
    {
        case ',':;
        case '(':;
        case ')':;
        case '[':;
        case ']':;
        case '{':;
        case '}':;
        return 1;
    }
    return 0;
}


char str_string_include(char string[],char c)
{
    int length;
    int i;
    length = strlen(string);
    for(i = 0; i<length;i++)
        if(string[i]==c)
            return 1;
    return 0;

}






