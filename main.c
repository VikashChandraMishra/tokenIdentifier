#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define SIZE 100

char s[SIZE];
int top = -1;

int isempty()
{
    if(top == -1) return 1;
    else return 0;
}

int isfull()
{
    if(top == SIZE - 1) return 1;
    else return 0;
}

void push(char c)
{
    if(isfull()) return;
    else s[++top] = c;
}

int pop()
{
    if(isempty()) return (-1);
    else top--;
    return 1;
}

char get_top()
{
    if(!isempty()) return s[top];
    else return '0';
}

int isoperator(char symbol)
{
    char operators[] = "+-=*/%!,;[](){}<>&!|";
    int i = 0;
    while(operators[i] != '\0')
    {
        if(operators[i] == symbol) return 1;
        i++;
    }
    return 0;
}

int isidentifier(char *symbol)
{
    int flag = 0;

    if (!isalpha(*symbol) && *symbol != '_')
        return 0;
    else
    {
        while (*symbol != '\0')
        {
            if (!isalnum(*symbol) && *symbol != '_')
                return 0;
            else if(isalpha(*symbol))
                flag++;

            symbol++;
        }
    }

    if(flag)
        return 1;
    else
        return 0;
}

int iskeyword(char word[])
{
    char keywords[][9] = {"auto",
                          "break",
                          "case",
                          "char",
                          "const",
                          "default",
                          "double",
                          "enum",
                          "extern",
                          "float",
                          "for",
                          "goto",
                          "int",
                          "long",
                          "register",
                          "return",
                          "short",
                          "signed",
                          "sizeof",
                          "static",
                          "struct",
                          "switch",
                          "typedef",
                          "union",
                          "unsigned",
                          "void",
                          "volatile",
                          "while",
                          "if",
                          "else",
                          "for",
                          "do",
                          "while",
                          "continue"};

    for (int i = 0;word[i] != '\0'; i++)
    {
        if (!isalpha(word[i]))
            return 0;
    }

    for (int i = 0; i < 32; i++)
    {
        if (!strcmp(word, keywords[i]))
            return 1;
        if (i == 31)
            return 0;
    }
}

int isconstant(char symbols[])
{
    int i = 0, flag = 0;

    if(symbols[0] == '"')
    {
        while(symbols[i] != '\0')i++;
        if( (symbols[--i] == '"' && ++i >= 2)) return 1;
        else return 0;
    }
    else
        while(symbols[i] != '\0')
        {
            if(isdigit(symbols[i]))i++;
            else if(symbols[i] == '.')
            {
                i++;
                flag++;
                if(flag == 2) return 0;
            }
            else return 0;
        }
    if(symbols[0] != '\0')
        return 1;
}

void identify_tokens(char string[])
{
    int i = 0, flag = 0, ws = 0;
    char word[50] = "";

    while(string[i] != '\0')
    {
        if(isoperator(string[i]))
        {
            printf("\n%c is an operator.\n", string[i]);
            flag++;
        }
        else if(isspace(string[i]))
        {
            ws++;
            flag++;
        }

        if(!flag)stradd(word, string[i]);

        if(flag || string[i + 1] == '\0')
        {
            if(iskeyword(word))
                printf("\n%s is a keyword.\n", word);
            else if(isidentifier(word))
                printf("\n%s is an identifier.\n", word);
            else if(isconstant(word))
                printf("\n%s is a constant.\n", word);
            flag = 0;
            word[0] = '\0';
        }

        i++;
    }

    printf("\nNumber of white space characters in the string: %d.\n", ws);
}

void stradd(char word[], char c)
{
    int i = 0;
    while(word[i] != '\0')i++;
    word[i++] = c;
    word[i] = '\0';
}

int main()
{
    char string[100];
    int i = 0;

    printf("Enter a string:");
    gets(string);

    identify_tokens(string);

    return 0;
}
