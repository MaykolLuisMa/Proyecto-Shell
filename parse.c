#include "Extras.c"

void IgnoreComments(char *input)
{   
    char *Comment = strchr(input,'#');

    if(Comment == NULL)
        return;
    
    int CommentPosition = (strlen(input)-strlen(Comment));
    
    input[CommentPosition] = '\0';
}

int Split(char *input,char **Words)
{
    int WordsAmount = 1+CountCaracter(input,' ');
    
    char *word = strtok(input," ");

    int counter = 0;
    while (word!=NULL)
    {
        Words[counter] =  strdup(word);
        word = strtok(NULL," "); 
        counter++;
    }  

    return WordsAmount;
}

int GetInstruction(Instruction *Instruction1,char **Words,int start,int WordsAmount)
{
    int Next = 0;
    int PosParam = 0;
    int PosFileName = 0;
    int ParamCounter = 0;
    int ToCounter = 0;
    int DoubleToCounter = 0;
    int FromCounter = 0;
    int ParamWithSpaces = 0;
 
    for (int i = start; i < WordsAmount;i++)
    {
        if(i == start)
        {
            Instruction1 -> Command_ = strdup(Words[i]);
            PosParam = 1;
            Instruction1->Params_[ParamCounter] = strdup(Words[i]);
            ParamCounter++;
            if(!strcmp(Instruction1->Command_,cd))
                ParamWithSpaces = 1;
        }
        else if(!strcmp(Words[i],ToOperator))
        {
            
            PosFileName = 1;
            Instruction1->ToOperatorEnabled_ = 1;
            PosParam = 0;
        }
        else if(!strcmp(Words[i],FromOperator))
        {
           
            PosFileName = 2;
            Instruction1->FromOperatorEnabled_ = 1;
            PosParam = 0;
        }
        else if(!strcmp(Words[i],DoubleToOperator))
        {
           
            PosFileName = 3;
            Instruction1->DoubleToOperatorEnabled_=1;
            PosParam = 0;
        }
        else if(!strcmp(Words[i],PipeOperator))
        {
            Next = i+1;
            break;
        }
        else if(PosParam == 1)
        {
           
            Instruction1->Params_[ParamCounter] = strdup(Words[i]);
            ParamCounter++;
        }
        else if(PosFileName == 1)
        {
            Instruction1->ToOperatorTarget_.words[ToCounter] = strdup(Words[i]);
            ToCounter++;
        }
        else if(PosFileName == 2)
        {
            Instruction1->FromOperatorTarget_.words[FromCounter] = strdup(Words[i]);
            FromCounter++;
        }
        else if(PosFileName == 3)
        {
            Instruction1->DoubleToOperatorTarget_.words[DoubleToCounter] = strdup(Words[i]);
            DoubleToCounter++;
        }
    }
    Instruction1->ParamsAmount_=ParamCounter;
    Instruction1->ToOperatorTarget_.Amount=ToCounter;
    Instruction1->FromOperatorTarget_.Amount=FromCounter;
    Instruction1->DoubleToOperatorTarget_.Amount=DoubleToCounter;
    return Next;
}

void ProcessWords(InstructionList *list,char **Words,int WordsAmount)
{
    int n = CountInstructionsByPipes(Words,WordsAmount);
    list->Amount = n;

    for (size_t i = 0; i < list->Amount; i++)
    {
        BulidIntstruction(&(list->ListByPipes[i]));
    }

    for (int i = 0; i < n; i++)
    {
        int Next = GetInstruction(&(list->ListByPipes[i]),Words,Next,WordsAmount);
        list->ListByPipes[i].PipeIndex_ = i;
    }
}