//C's librerys:
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

//Colors:
#define Yellow "\x1b[33m"
#define Reset "\x1b[0m"

//Boolean
#define True 1
#define False 0

//Comands:
#define cd "cd"
#define EXIT "exit"
#define HELP "help"
#define ToOperator ">"
#define FromOperator "<"
#define DoubleToOperator ">>"
#define PipeOperator "|"

//Other constants
#define MaximumPathLenth 300
#define TheSize 10000
#define TempSize 500

typedef struct StringList
{
    char **words;
    int Amount;
}StringList;

void BuildStringList(StringList *list)
{
    list->words = malloc(TheSize);
    list->Amount = 0;
} 

typedef struct Instruction
{
    char *Command_;
    char **Params_;
    int ParamsAmount_;
    StringList ToOperatorTarget_;//>
    StringList FromOperatorTarget_;//<
    StringList DoubleToOperatorTarget_;//>>
    int ToOperatorEnabled_;
    int FromOperatorEnabled_;
    int DoubleToOperatorEnabled_;
    int PipeIndex_;
}
Instruction;

void BulidIntstruction(Instruction *instruction)
{
    instruction->Command_ = malloc(sizeof(char)*TheSize);
    instruction->Params_ = malloc(TheSize);
    instruction->ParamsAmount_ = 0;
    BuildStringList(&(instruction->ToOperatorTarget_));
    BuildStringList(&(instruction->FromOperatorTarget_));
    BuildStringList(&(instruction->DoubleToOperatorTarget_));
    instruction->ToOperatorEnabled_ = 0;
    instruction->FromOperatorEnabled_ = 0;
    instruction->DoubleToOperatorEnabled_ = 0;
    instruction->PipeIndex_ = 0;
}

typedef struct InstructionList
{
    Instruction *ListByPipes;
    int Amount;
}
InstructionList;

void BuildInstructionList(InstructionList *list);
void BuildInstructionList(InstructionList *list)
{
    list->ListByPipes = malloc(TheSize);
    list->Amount = 0;
}