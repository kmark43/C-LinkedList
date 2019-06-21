#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

void CheckMemError(int operationReturn);
void PrintList(LinkedList list);

int main(int argc, char** argv) {
    LinkedList list;

    CheckMemError(CreateLinkedList(&list));
    
    CheckMemError(LLAddFirst(list, (ListElement)5));
    CheckMemError(LLAddFirst(list, (ListElement)11));
    CheckMemError(LLAddFirst(list, (ListElement)12));
    CheckMemError(LLAddFirst(list, (ListElement)13));
    CheckMemError(LLAddFirst(list, (ListElement)14));
    CheckMemError(LLAddLast(list, (ListElement)7));

    int first;
    
    printf("%u\n", LLSize(list));

    PrintList(list);
    LLRemoveLast(list, (ListElement*)&first);
    PrintList(list);
    
    while (LLSize(list)) {
        LLRemoveFirst(list, (ListElement*)&first);
        PrintList(list);
    }

    FreeLinkedList(list, NULL);

    return EXIT_SUCCESS;
}

void CheckMemError(int operationReturnValue) {
    if (!operationReturnValue) {
        fprintf(stderr, "Memory error\n");
        exit(EXIT_FAILURE);
    }
}

void PrintList(LinkedList list) {
    LLIter iter;
    CheckMemError(LLCreateIterator(list, 0, &iter));
    printf("[");

    int element;

    if (LLIteratorNext(iter)) {
        LLIteratorGet(iter, (ListElement*)&element);
        printf("%i", element);
    }

    while (LLIteratorNext(iter)) {
        LLIteratorGet(iter, (ListElement*)&element);
        printf(", %i", element);
    }

    printf("]\n");

    LLFreeIterator(iter);
}