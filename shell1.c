#include "Execution.c"

void ProcessInput(char *input)
{
    IgnoreComments(input);
 
    char **Words = malloc(TheSize);

    int WordsAmount = Split(input,Words);

    InstructionList list;

    BuildInstructionList(&list);

    ProcessWords(&list,Words,WordsAmount);
    
    ExecuteAll(&list);
}

int main(int argc, char const *argv[])
{

    char *InitialPath = malloc(MaximumPathLenth*sizeof(char));
    GetCurrentDirectory(InitialPath);

    while (1)
    {      
        printf(Yellow "my-prompt ");
        printf(Reset "$ ");
        
        char *input = malloc(TempSize * sizeof(char));

        gets(input);
        if(AntiTrollSegurity(input) == 1)
            continue;
        ProcessInput(input);
    }
    
    return 0;
}