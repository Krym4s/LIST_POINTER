//
// Created by egolg on 06.11.2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#ifndef LIST_POINTER_LIST_POINTER_H
#define LIST_POINTER_LIST_POINTER_H

struct ListMember
{
    double value;
    struct ListMember* prev;
    struct ListMember* next;
};

struct List
{
    struct ListMember* first;
    struct ListMember* last;
    int error;
    unsigned int sz;

    FILE* textLogs;
    FILE* graphicLogs;
};

enum ListErrors
{
    NO_ERRORS = 0,
    LIST_INTERRUPT = 1,
    NO_LOG_FILE = 2,
    BAD_SIZE = 3,
};

const double EPSILON = 1e-10;

int ListConstruct (struct List* thou, FILE* textLogs, FILE* graphicLogs);

int ListInit (struct List* thou);

int ListDestruct (struct List* thou);

struct ListMember* InsertAfter (struct List* thou, struct ListMember* index, double value);

struct ListMember* InsertBefore (struct List* thou, struct ListMember* index, double value);

struct ListMember* InsertAfterByIndex (struct List* thou, unsigned int index, double value);

struct ListMember* InsertBeforeByIndex (struct List* thou, unsigned int index, double value);

struct ListMember* InsertBegin (struct List* thou, double value);

struct ListMember* InsertEnd (struct List* thou, double value);

int DeleteMember (struct List* thou, struct ListMember* index);

int DeleteFirst (struct List* thou);

int DeleteLast (struct List* thou);

int DeleteMiddle (struct List* thou, struct ListMember* index);

int TextDump (struct List* thou, char* reason, int line);

int GraphicDump (struct List* thou, char* reason, int line);

ListMember* FindValue (struct List* thou, double  value);

int VerifyList (struct List* thou);

ListMember* FindAddress (struct List* thou, int ind);

struct ListMember* FindIndex (struct List* thou, unsigned int index);

int DeleteMemberByIndex (struct List* thou, unsigned int index);

char* ErrorName (int error);

#endif //LIST_POINTER_LIST_POINTER_H
