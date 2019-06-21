#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

#include <stdlib.h>
#include <stdbool.h>

typedef void* ListElement;
typedef void (*FreeElemFunc)(ListElement);

typedef struct llnode_t {
    ListElement value;
    struct llnode_t* next;
    struct llnode_t* prev;
} *LLNode;

typedef struct linkedlist_t {
    LLNode head;
    LLNode tail;
    size_t size;
} *LinkedList;

typedef struct linkedlistiter_t {
    LinkedList list;
    LLNode current;
    bool pastHead;
    bool pastTail;
} *LLIter;

// Creates a new linked list
// Returns
//   1 on success
//   0 on memory error
int CreateLinkedList(LinkedList* list);

// Frees the given LinkedList, uses FreeElemFunc to free all
// the elements in the list
void FreeLinkedList(LinkedList list, FreeElemFunc freeptr);

// Adds the given element to the head of the given LinkedList
// Returns
//   1 on success
//   0 on memory error
int LLAddFirst(LinkedList list, ListElement element);

// Retrieves the head of the given LinkedList through
// the retelement output parameter
// Returns
//   1 on success
//   0 if the list is empty
int LLGetFirst(LinkedList list, ListElement* retelement);

// Removes the head from the given LinkedList and
// returns its old value through the retelement output
// parameter
// The client takes responsibility for freeing the element
// Returns
//   1 on success
//   0 if the list is empty
int LLRemoveFirst(LinkedList list, ListElement* retelement);

// Adds the given element to the tail of the given LinkedList
// Returns
//   1 on success
//   0 on memory error
int LLAddLast(LinkedList list, ListElement element);

// Retrieves the tail of the given LinkedList through
// the retelement output parameter
// Returns
//   1 on success
//   0 if the list is empty
int LLGetLast(LinkedList list, ListElement* retelement);

// Removes the tail from the given LinkedList and
// returns its old value through the retelement output
// parameter
// The client takes responsibility for freeing the element
// Returns
//   1 on success
//   0 if the list is empty
int LLRemoveLast(LinkedList list, ListElement* retelement);

// Returns the size of the given LinkedList
size_t LLSize(LinkedList list);

// Creates a new iterator for the given linkedlist
// Returns
//   1 on success
//   0 on memory error
int LLCreateIterator(LinkedList list, int position, LLIter* iter);

// Frees the given iterator
void LLFreeIterator(LLIter iter);

// Advances the iterator to the next element
// Returns
//   true if iterator is advanced to the next element
//   false if there is no element to advance to
bool LLIteratorNext(LLIter iter);

// Advances the iterator to the previous element
// Returns
//   true if iterator is advanced to the previous element
//   false if there is no element to advance to
bool LLIteratorPrev(LLIter iter);

// Creates a new iterator for the given linkedlist
// Returns
//   1 on success
//   0 if the iterator is not pointing to an element
int LLIteratorGet(LLIter iter, ListElement* retelement);

#endif  // _LINKED_LIST_H_