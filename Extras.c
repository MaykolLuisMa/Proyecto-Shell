#include "help.c"

int CountCaracter(char *string,char caracter)
{
    int n = 0;
    for (int i = 0; i < strlen(string); i++)
    {
        if(string[i]==caracter&&string[i+1]!=caracter)
            n++;
    }
    return n;
}

int CountWords(char **Words,int WordsAmount,char *word)
{
    int counter = 0;
    for (int i = 0; i < WordsAmount; i++)
    {
        if(!strcmp(Words[i],word))
            counter++;
    }
    return counter;
    
}

void ConcatString(char **InitialStrings,char *FinalString,int Amount)
{
    for (int i = 0; i < Amount; i++)
    {
        strcat(FinalString,InitialStrings[i]);
        if(i+1!=Amount)
            strcat(FinalString," ");
    }
    
}

void ConvertToString(int number,char *str,int lenth)
{
    int f;
    for(f = 0;f < lenth && number;f++)
    {
        str[f] = '0' + number%10;
        number /= 10;
    }
    str[f--] = '\0';

    int i = 0;
    while(i < f)
    {
        char t = str[i];
        str[i] = str[f];
        str[f] = t;

        i++; f--;
    }
}
int GetCurrentDirectory(char *path)
{
    int MaxPathLen = MaximumPathLenth;
    errno = 0;
    if(getcwd(path,MaxPathLen) == NULL)
    {
        if(errno == ERANGE)
        {
            path = "Error, pathname is too long";      
        }
        else
        {
            perror("getcwd");
            path = "Error, getcwd is fail";
        }
        return 1;
    }
    return 0;
} 
int AntiTrollSegurity(char *input)
{
   
    while(input[0] == ' ')
    {
        for (int i = 1; i < TempSize*sizeof(char); i++)
        {
            input[i-1] = input[i];
        }
    }
    if(strlen(input) ==0)
        return 1;
    while (input[strlen(input)-1]==' ')
    {
        input[strlen(input)-1] = '\0';
    }
    
    return 0;
}
int CountInstructionsByPipes(char **Words,int WordsAmount)
{
    return 1+CountWords(Words,WordsAmount,"|");
}