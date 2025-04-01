#include "List.h"
#include <stdio.h> // For standard input and output functions
#include <assert.h>
// private Node type
// Node Layer
Node newNode(void* elem)
{
    Node N = malloc(sizeof(NodeObj));
    assert(N != NULL);
    N->elem = elem;
    N->prev = NULL;
    N->next = NULL;
    return (N);
}
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
        free((*pN)->elem);  // free whatever the elem field is pointin in N 
        free(*pN);
        *pN = NULL;
    }
}
//-----------------------------------------------
// List operations
List newList(void)
{
    List L;
    L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->front = L->back = L->cur = NULL;
    return (L);
}
void freeList(List *pL)
{
    if (pL == NULL || *pL == NULL)
    {
        return; // Do nothing if the pointer or list is NULL
    }

    Node ptr = (*pL)->front;
    while (ptr != NULL)
    {
        Node rmv = ptr;
        ptr = ptr->next;
        freeNode(&rmv);
    }

    free(*pL);  // Free the List structure
    *pL = NULL; // Avoid dangling pointer
}
// Accessor
int length(List L)
{
    Node p = L->front;
    int cnt = 0;
    while (p)
    {
        cnt++; 
        p = p->next;
    }
    return cnt;
}
int index(List L)
{
    Node p = L->cur;
    if (!p)
        return -1;
    int i = 0;
    while (p->prev)
    {
        p = p->prev;
        i++;
    }
    return i;
}
// Returns index of cursor element if defined, -1 otherwise.

void* front(List L)
{
    if (!L->front)
    {
        return NULL;
    }
    return L->front->elem;
}
// Returns front element
void* back(List L)
{
    if (!L->back)
    {
        return NULL;
    }
    return L->back->elem;
}
// Returns back element
void* get(List L)
{
    if (!L->cur)
    {
        return NULL;
    }
    return L->cur->elem;
}
// Returns cursor element of L. Pre: length()>0, index()>=0

// Manipulation procedures ----------------------------------------------------
void clear(List L)
{
    Node ptr = (L)->front;
    while (ptr)
    {
        Node rmv = ptr;
        ptr = ptr->next;
        freeNode(&rmv);
    }
    L->back = NULL;
    L->front = NULL;
    L->cur = NULL;
} // Resets L to its original empty state.
void set(List L, void* x)
{
    if (!L->cur)
        return;
    L->cur->elem = x;
}
void moveFront(List L)
{
    if(!L) return;
    L->cur = L->front;
}
void moveBack(List L)
{
    if(!L) return;
    L->cur = L->back;
} 
void movePrev(List L)
{
    if(!L)return;
    if (L->cur)
    {
        L->cur = L->cur->prev; 
    }
    else if (length(L)==1){
        printf("calling MovePrev on a Length1 list when cursor is not initialized/ at back, moving cur to front!\n");
        L->cur = L->front; // special case where it has length 1:
    }
}
void moveNext(List L)
{
    if(!L)return;
    if (L->cur)
    {
        L->cur = L->cur->next; 
    }
    else if (length(L)==1){
        printf("calling Movenext on a Length1 list when cursor is not initialized/ at front, moving cur to back!\n");
        L->cur = L->front; // special case where it has length 1:
    }
}

void prepend(List L, void* x)
{
    Node n = newNode(x);
    if (L->front)
    {
        n->next = L->front;
        L->front->prev = n;
        L->front = n;
        return;
    }
    // emptyList?
    L->front = n;
    L->back = n;
}
void append(List L, void* x)
{
    Node n = newNode(x);
    if (L->back)
    {
        L->back->next = n;
        n->prev = L->back;
        L->back = n;
        return;
    }
    // emptyList?
    L->front = n;
    L->back = n;
}
// insertion takes place after back element.
void insertBefore(List L, void* x)
{
    if (!L)
        return;
    if (!L->cur)
        return;
    Node it = L->cur;

    // if 'it' is head
    if (!it->prev)
    {
        prepend(L, x);
        return;
    }
    Node n = newNode(x);
    n->prev = it->prev;
    n->next = it;
    it->prev->next = n;
    it->prev = n;
}
void insertAfter(List L, void* x)
{
    if (!L)
        return;
    if (!L->cur)
        return;
    Node it = L->cur;

    // if 'it' is tail
    if (!it->next)
    {
        append(L, x);
        return;
    }
    Node n = newNode(x);
    n->prev = it;
    n->next = it->next;
    it->next->prev = n;
    it->next = n;
}

//RIGOROUSly written deletes
void deleteFront(List L)
{
    if (!L->front){
        printf("No element at front to delete!\n");
        return;
    }
    Node toDelete = L->front;
    // extra check
    if (L->cur == toDelete)
    {
        L->cur = NULL; // Avoid dangling pointer
    }
    if (L->back == toDelete)
    {
        L->back = NULL; // Avoid dangling pointer
    }
    L->front = toDelete->next;
    freeNode(&toDelete);

    if(L->front) // if L still has a front (edge)
        L->front->prev = NULL; // nothing dangling here
}

void deleteBack(List L) {
    if (!L->back) {
        printf("No element at back to delete!\n");
        return;
    }
    Node toDelete = L->back;

    if (L->cur == toDelete) {
        L->cur = NULL; // Avoid dangling pointer
    }
    if (L->front == toDelete) { // Single-element list case
        L->front = NULL;
        L->back = NULL;
    } else {
        L->back = toDelete->prev;
        L->back->next = NULL;
    }
    
    freeNode(&toDelete);
}

void delete(List L)
{
    if (!L->cur){
        printf("No element at cursor to delete!\n");
        return;
    }
    Node toDelete = L->cur;

    if (!toDelete->prev)
    { // if points to head
        deleteFront(L);
        L->cur = NULL;
        return;
    }
    if (!toDelete->next)
    {
        deleteBack(L);
        L->cur = NULL;
        return;
    }
    toDelete->prev->next = toDelete->next;
    toDelete->next->prev = toDelete->prev;
    freeNode(&toDelete);
    L->cur = NULL;
} // Delete cursor element, making cursor undefined.
