//
// Created by egolg on 06.11.2020.
//

#include <assert.h>
#include "LIST_POINTER.h"

#define ASSERTED !VerifyList (thou) || GraphicDump (thou, ErrorName (thou->error), __LINE__);

#define ARGNAME(x) #x

int ListConstruct (struct List* thou, FILE* textLogs, FILE* graphicLogs)
{
    assert (thou);

    thou->first = NULL;
    thou->last = NULL;
    thou->sz = 0;
    thou->error = NO_ERRORS;

    thou->textLogs = textLogs;
    thou->graphicLogs = graphicLogs;

    if (!thou->textLogs)
        return NO_LOG_FILE;

    if (!thou->graphicLogs)
        return  NO_LOG_FILE;

    return NO_ERRORS;
}

int ListInit (struct List* thou)
{
    assert (thou);

    if (VerifyList(thou))
        GraphicDump (thou, "check", __LINE__);

    thou->first = NULL;
    thou->last = NULL;
    thou->sz = 0;
    thou->error = NO_ERRORS;thou->error = NO_ERRORS;

    thou->textLogs = fopen("textLogs.txt", "w");
    thou->graphicLogs = fopen ("graphicLogs.dot", "w");

    if (!thou->textLogs)
        return NO_LOG_FILE;

    if (!thou->graphicLogs)
        return  NO_LOG_FILE;

    if (VerifyList(thou))
        GraphicDump (thou, "check", __LINE__);

    return NO_ERRORS;
}

struct ListMember* InsertAfter (struct List* thou, struct ListMember* index, double value)
{
    assert (thou);
    assert (index);

    thou->sz++;
    struct ListMember* newMember = (struct ListMember*) calloc (1, sizeof(ListMember));

    newMember->next = index->next;
    newMember->prev = index;
    newMember->value = value;

    if (index->next)
        index->next->prev = newMember;
    else
        thou->last = newMember;

    index->next = newMember;

    return newMember;
}

struct ListMember* InsertBefore (struct List* thou, struct ListMember* index, double value)
{
    assert (thou);
    assert (index);

    thou->sz++;
    struct ListMember* newMember = (struct ListMember*) calloc (1, sizeof(ListMember));

    newMember->prev = index->prev;
    newMember->next = index;
    newMember->value = value;

    if (index->prev)
        index->prev->next = newMember;
    else
        thou->first = newMember;

    index->prev = newMember;

    return newMember;
}

struct ListMember* InsertBegin (struct List* thou, double value)
{
    assert (thou);

    ASSERTED

    thou->sz++;
    struct ListMember* newMember = (struct ListMember*) calloc (1, sizeof(ListMember));

    newMember->prev = NULL;
    newMember->next = thou->first;

    if (thou->sz == 1)
        thou->last = newMember;

    thou->first = newMember;
    newMember->value = value;

    ASSERTED

    return newMember;
}

struct ListMember* InsertEnd (struct List* thou, double value)
{
    assert (thou);

    ASSERTED

    thou->sz++;
    struct ListMember* newMember = (struct ListMember*) calloc (1, sizeof(ListMember));

    newMember->next = NULL;
    newMember->prev = thou->last;
    if (thou->sz == 1)
        thou->first = newMember;

    thou->last = newMember;
    newMember->value = value;

    ASSERTED

    return newMember;
}

int DeleteMember (struct List* thou, struct ListMember* index)
{
    assert (thou);
    assert (index);

    ASSERTED

    if (thou->first == index)
        return DeleteFirst (thou);

    if (thou->last == index)
        return DeleteLast (thou);

    ASSERTED

    return DeleteMiddle (thou, index);
}

int DeleteFirst (struct List* thou)
{
    assert (thou);

    ASSERTED

    if (thou->last != thou->first)
        thou->first->next->prev = NULL;
    thou->first->value = NAN;

    thou->first = thou->first->next;

    ASSERTED

    return NO_ERRORS;
}

int DeleteLast (struct List* thou)
{
    assert (thou);

    ASSERTED

    if (thou->last != thou->first)
        thou->last->prev->next = NULL;
    thou->last->value = NAN;

    thou->last = thou->last->prev;

    ASSERTED

    return NO_ERRORS;
}

int DeleteMiddle (struct List* thou, struct ListMember* index)
{
    assert (thou);
    assert (index);

    ASSERTED

    index->prev->next = index->next;
    index->next->prev = index->prev;
    free (index);

    ASSERTED

    return NO_ERRORS;
}

int ListDestruct (struct List* thou)
{
    struct ListMember* curr = thou->first;
    struct ListMember* next = curr->next;

    while (next)
    {
        free (curr);
        curr = NULL;
        curr = next;
        next = next->next;
    }

    free (thou);
    thou = NULL;
    return NO_ERRORS;
}

int TextDump (struct List* thou, char* reason, int line)
{
    ListMember* pointer = thou->first;
    fprintf (thou->textLogs, "{\n");
    do
    {
        fprintf (thou->textLogs, "\t" "value            = %lg\n", pointer->value);
        fprintf (thou->textLogs, "\t" "previous pointer = %p\n", pointer->prev);
        fprintf (thou->textLogs, "\t" "current pointer  = %p\n", pointer);
        fprintf (thou->textLogs, "\t" "next pointer     = %p\n", pointer->next);
        pointer = pointer->next;
    }while (pointer->next);

    fprintf (thou->textLogs, "}\n");

    return NO_ERRORS;
}

int GraphicDump (struct List* thou, char* reason, int line)
{
    fseek (thou->graphicLogs, 0, SEEK_SET);

    if (!thou)
        printf ("there is no List. Executed on line %d", line);

    if (!thou->sz)
        return NO_ERRORS;

    fprintf (thou->graphicLogs, "digraph LIST{\n");
    fprintf (thou->graphicLogs, "\t" "rankdir = TB;\n");

    ListMember* pointer = thou->first;
    unsigned int index = 1;

    do
    {
        fprintf (thou->graphicLogs,"\t" "%d[shape=record,label=\" { value = %lg |  <prev> prev = %p | <current> current = %p | <next> next =  %p } \"];\n",
                 index, pointer->value, pointer->prev, pointer, pointer->next);

        pointer = pointer->next;
        index++;
    }while (pointer);

    fprintf (thou->graphicLogs, "\n");


    pointer = thou->first;
    index = 1;

    while (pointer->next)
    {
        fprintf (thou->graphicLogs,"\t" "%d -> %d;\n", index, index + 1);
        pointer = pointer->next;
        index++;
    }

    pointer = thou->last;
    index = thou->sz - 1;

    while (pointer->prev)
    {
        fprintf (thou->graphicLogs,"\t" "%d -> %d;\n", index, index - 1);
        pointer = pointer->prev;
        index--;
    }

    fprintf (thou->graphicLogs, "}\n");

    return NO_ERRORS;
}

ListMember* FindValue (struct List* thou, double  value)
{
    ASSERTED

    ListMember* index = thou->first;
    while (index)
    {
        if (fabs (index->value - value) < EPSILON)
            return index;

        index = index->next;
    }

    ASSERTED

    return NULL;
}

int VerifyList (struct List* thou)
{
    assert (thou);

    ListMember* index = thou->first;
    int memberCounter = 0;
    while (index)
    {
        memberCounter++;
        index = index->next;

        if (memberCounter > thou->sz)
            return thou->error = LIST_INTERRUPT;
    }

    if (memberCounter != thou->sz)
        return thou->error = LIST_INTERRUPT;

    index = thou->last;
    memberCounter = 0;
    while (index)
    {
        memberCounter++;
        index = index->prev;

        if (memberCounter > thou->sz)
            return thou->error = LIST_INTERRUPT;
    }

    if (memberCounter != thou->sz)
        return thou->error = LIST_INTERRUPT;

    return NO_ERRORS;
}

struct ListMember* FindIndex (struct List* thou, unsigned int index)
{
    assert (thou);

    ASSERTED

    ListMember* currentMember = thou->first;
    while (index > 0)
    {
        currentMember = currentMember->next;
        if (!currentMember)
            return currentMember;

        index--;
    }

    ASSERTED

    return currentMember;
}

struct ListMember* InsertAfterByIndex (struct List* thou, unsigned int index, double value)
{
    ASSERTED
    return InsertAfter (thou, FindIndex (thou, index), value);
}

struct ListMember* InsertBeforeByIndex (struct List* thou, unsigned int index, double value)
{
    ASSERTED
    return InsertAfter (thou, FindIndex (thou, index) - 1, value);
}

int DeleteMemberByIndex (struct List* thou, unsigned int index)
{
    ASSERTED
    return DeleteMember(thou, FindIndex (thou, index));
}

char* ErrorName (int error)
{
    switch (error)
    {
        case NO_ERRORS: return ARGNAME(NO_ERRORS);
        case LIST_INTERRUPT: return ARGNAME (LIST_INTERRUPT);
        case NO_LOG_FILE: return ARGNAME (NO_LOG_FILE);
        case BAD_SIZE: return ARGNAME (BAD_SIZE);
    }
}

#undef ARGNAME
#undef ASSERTED
