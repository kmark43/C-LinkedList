#include "LinkedList.h"

void LLNullFreeElem(ListElement element) { }

int CreateLinkedList(LinkedList* list) {
    LinkedList l = malloc(sizeof(struct linkedlist_t));
    if (l == NULL) {
        return 0;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    *list = l;
    return 1;
}

void FreeLinkedList(LinkedList list, FreeElemFunc freeptr) {
    if (list->size > 0) {
        LLNode current = list->head;
        while (current != NULL) {
            LLNode next = current->next;
            if (freeptr != NULL) {
                freeptr(current->value);
            }
            free(current);
            current = next;
        }
    }
    free(list);
}

int LLAddFirst(LinkedList list, ListElement element) {
    LLNode node = malloc(sizeof(struct llnode_t));
    if (node == NULL) {
        return 0;
    }

    node->value = element;
    node->next = list->head;
    node->prev = NULL;

    if (list->size == 0) {
        list->tail = node;
    } else {
        list->head->prev = node;
    }

    list->head = node;
    list->size++;

    return 1;
}

int LLGetFirst(LinkedList list, ListElement* retelement) {
    if (list->size == 0) {
        return 0;
    }
    *retelement = list->head->value;
    return 1;
}

int LLRemoveFirst(LinkedList list, ListElement* retelement) {
    if (list->size == 0) {
        return 0;
    }
    LLNode node = list->head;
    *retelement = node->value;
    list->head = node->next;
    if (list->size > 1) {
        list->head->prev = NULL;
    }
        
    list->size--;
    if (list->size == 0) {
        list->head = NULL;
        list->tail = NULL;
    }

    return 1;
}

int LLAddLast(LinkedList list, ListElement element) {
    LLNode node = malloc(sizeof(struct llnode_t));
    if (node == NULL) {
        return 0;
    }

    node->value = element;
    node->prev = list->tail;
    node->next = NULL;

    if (list->size == 0) {
        list->head = node;
    } else {
        list->tail->next = node;
    }

    list->tail = node;
    list->size++;

    return 1;
}

int LLGetLast(LinkedList list, ListElement* retelement) {
    if (list->size == 0) {
        return 0;
    }
    *retelement = list->tail->value;
    return 1;
}

int LLRemoveLast(LinkedList list, ListElement* retelement) {
    if (list->size == 0) {
        return 0;
    }
    LLNode node = list->tail;
    *retelement = node->value;
    list->tail = node->prev;
    if (list->size > 1) {
        list->tail->next = NULL;
    }
        
    list->size--;
    if (list->size == 0) {
        list->head = NULL;
        list->tail = NULL;
    }

    return 1;
}

size_t LLSize(LinkedList list) {
    return list->size;
}

int LLCreateIterator(LinkedList list, int position, LLIter* iter) {
    LLIter i = malloc(sizeof(struct linkedlistiter_t));
    if (i == NULL) {
        return 0;
    }

    i->list = list;

    if (list->size == 0) {
        i->pastHead = true;
        i->pastTail = true;
    } else {
        if (position == 0) {
            i->pastHead = true;
            i->pastTail = false;
        } else {
            i->pastHead = false;
            i->pastTail = true;
        }
    }

    *iter = i;

    return 1;
}

void LLFreeIterator(LLIter iter) {
    free(iter);
}

bool LLIteratorNext(LLIter iter) {
    if (iter->pastTail) {
        return false;
    }

    if (iter->pastHead) {
        iter->current = iter->list->head;
        iter->pastHead = false;
    } else {
        iter->current = iter->current->next;
        if (iter->current == NULL) {
            iter->pastTail = true;
            return false;
        }
    }

    return true;
}

bool LLIteratorPrev(LLIter iter) {
    if (iter->pastHead) {
        return false;
    }

    if (iter->pastTail) {
        iter->current = iter->list->tail;
        iter->pastTail = false;
    } else {
        iter->current = iter->current->prev;
        if (iter->current == NULL) {
            iter->pastHead = true;
            return false;
        }
    }

    return true;
}

int LLIteratorGet(LLIter iter, ListElement* retelement) {
    if (iter->pastHead || iter->pastTail) {
        return 0;
    }

    *retelement = iter->current->value;

    return 1;
}
