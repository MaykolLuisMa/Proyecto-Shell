#include "parse.c"

int GetRealSpace(char **params,int amount)
{
    int count = 0;
    for (int i = 0; i < amount; i++)
    {
        count += strlen(params[i]);
        count++;
    }
    return count;
}
void CopyStringList(char **NewList,char **OldList,int amount)
{
    for (int i = 0; i < amount; i++)
    {
        NewList[i] = strdup(OldList[i]);
    }
}
int ExecuteExternalCommand(Instruction *instruction,int TIn,int TOut)
{

    int FatherPid = getpid();

    pid_t ActualPid = fork();

    if(ActualPid == 0)
    {
        if(TIn > 2)
        {
            dup2(TIn,STDIN_FILENO);
            close(TIn);
        }
        if(TOut > 2)
        {
            dup2(TOut,STDOUT_FILENO);
            close(TOut);
        }
        if(instruction->ToOperatorEnabled_ == 1)
        {
            char *FileName = malloc(1000);
            ConcatString(instruction->ToOperatorTarget_.words,FileName,instruction->ToOperatorTarget_.Amount);
            int fd = creat(FileName, 0644);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if(instruction->DoubleToOperatorEnabled_ == 1)
        {
            char *FileName = malloc(300);
            ConcatString(instruction->DoubleToOperatorTarget_.words,FileName,instruction->DoubleToOperatorTarget_.Amount);
            int fd = open(FileName, O_CREAT | O_WRONLY | O_APPEND, 777);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if(instruction->FromOperatorEnabled_ == 1)
        {
            char *FileName = malloc(300);
            ConcatString(instruction->FromOperatorTarget_.words,FileName,instruction->FromOperatorTarget_.Amount);
            int fd = open(FileName, O_RDONLY);
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
    
        int result = execvp(instruction->Command_,instruction->Params_);
        exit(0);
    }
    else
    {
        
        wait(NULL);
        if(TIn > 2)
            close(TIn);
        if(TOut > 2)
            close(TOut);
    }
}


void ExecuteInstruction(Instruction *instruction, int TIn, int TOut)
{
    
    if(!strcmp(instruction->Command_,cd))
    {
        
        char *temp = malloc(200);
        if(instruction->ParamsAmount_!=0)
        {
            
            ConcatString(instruction->Params_,temp,instruction->ParamsAmount_);
            //printf(temp);
            chdir(temp+3);
        }
    }
    else if(!strcmp(instruction->Command_,HELP))
    {
        if(instruction->Params_[1]==NULL)
            PrincipalHelp();
        else if(!strcmp(instruction->Params_[1],"basic"))
            BasicHelp();
        else if(!strcmp(instruction->Params_[1],"multi-pipe"))
            MultiPipeHelp();
        else if(!strcmp(instruction->Params_[1],"help"))
            HelpHelp();
    }
    else if(!strcmp(instruction->Command_,EXIT))
    {
        exit(0);
    }
    else
    {
        ExecuteExternalCommand(instruction,TIn,TOut);
    }
}



void ExecuteAll(InstructionList *list)
{
    int TIn;
    int TOut;

    char *TemporalIn = malloc(TempSize);
    char *TemporalOut = malloc(TempSize);

    for (int i = 0; i < list->Amount; i++)
    {
        if(i == 0)
            TIn = STDIN_FILENO;
        else
            TIn = open(TemporalIn,O_RDONLY,777);
        
        if(i == list->Amount-1)
            TOut = STDOUT_FILENO;
        else
        {

            getcwd(TemporalOut,TempSize);
            strcat(TemporalOut,"/.Temporal_Output");
            char *number = malloc(5);
            ConvertToString(i,number,5);
            strcat(TemporalOut,number);

            TOut = creat(TemporalOut,S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        }
        ExecuteInstruction(&(list->ListByPipes[i]),TIn,TOut);

        if(i>0)
            remove(TemporalIn);
        if(i+1!=list->Amount)
            strcpy(TemporalIn,TemporalOut);
    }
}

