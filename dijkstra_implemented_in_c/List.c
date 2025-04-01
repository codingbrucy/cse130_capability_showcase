#include "List.h"
#include <stdio.h> // For standard input and output functions
#include <assert.h>
// private Node type
// Node Layer
Node newNode(int num)
{
    Node N = malloc(sizeof(NodeObj));
    assert(N != NULL);
    N->num = num;
    N->prev = NULL;
    N->next = NULL;
    return (N);
}
void freeNode(Node *pN)
{
    if (pN != NULL && *pN != NULL)
    {
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

int front(List L)
{
    if (!L->front)
    {
        return -999;
    }
    return L->front->num;
}
// Returns front element
int back(List L)
{
    if (!L->back)
    {
        return -999;
    }
    return L->back->num;
}
// Returns back element
int get(List L)
{
    if (!L->cur)
    {
        return -999;
    }
    return L->cur->num;
}
// Returns cursor element of L. Pre: length()>0, index()>=0

bool equals(List A, List B)
{
    // both empty
    if (!A && !B)
    {
        return true;
    }
    if (!A || !B)
    {
        return false;
    }
    if (length(A) != length(B))
    {
        return false;
    }
    Node p = A->front;
    Node q = B->front;
    while (p)
    {
        if (p->num != q->num)
        {
            return false;
        }
        p = p->next;
        q = q->next;
    }
    return true;
}
// check for element-wise equality

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
void set(List L, int x)
{
    if (!L->cur)
        return;
    L->cur->num = x;
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

void prepend(List L, int x)
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
void append(List L, int x)
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
void insertBefore(List L, int x)
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
void insertAfter(List L, int x)
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
void deleteBack(List L)
{
    if (!L->back){
        printf("No element at back to delete!\n");
        return;
    }
    Node toDelete = L->back;

    if (L->cur == toDelete)
    {
        L->cur = NULL; // Avoid dangling pointer
    }
    if (L->front == toDelete)
    {
        L->front = NULL; // Avoid dangling pointer
    }
    L->back = toDelete->prev;
    freeNode(&toDelete);
    if(L->back)
        L->back->next = NULL;
} // Delete the back element. Pre: length()>0
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
    freeNode(&L->cur);
    L->cur = NULL;
} // Delete cursor element, making cursor undefined.
  // Pre: length()>0, index()>=0
// Other operations -----------------------------------------------------------
void printList(FILE *out, List L)
{
    if (!L)
    {
        printf("EMPTY LIST NOTHING TO PRINT!");
        return;
    }
    Node it = L->front;
    while (it)
    {
        fprintf(out, "%d ", it->num);
        it = it->next;
    }
    fprintf(out, "\n");
}
List copyList(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    List ret = newList();
    Node it = L->front;

    while (it != NULL)
    {
        append(ret, it->num); // Add the data to the new list
        it = it->next;        // Move to the next node
    }

    return ret;
}
void insertInOrder(List L, int data)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: calling insertInOrder() on NULL List reference\n");
        return;
    }

    moveFront(L); // Start at the beginning of the list
    while (index(L) >= 0 && get(L) < data)
    {
        moveNext(L); // Move forward until we find the right spot
    }

    if (index(L) == -1)
    {
        // Reached the end, append the data
        append(L, data);
    }
    else
    {
        // Insert before the current element if it's not a duplicate
        insertBefore(L, data);
    }
}