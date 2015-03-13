
/***********************************************************************************************
 * OpenGL Window and Animation Library (formerly the Open Art Engine)                          *
 ***********************************************************************************************
 * This software is copyrighted software.  Use of this code is given only with permission to   *
 * parties who have been granted such permission by its author, Herbert Elwood Gilliland III   *
 ***********************************************************************************************
 * Copyright (c) 2010 Herbert Elwood Gilliland III ; All rights reserved.                      *
 ***********************************************************************************************/

#include "macros.h"
#include "LinkedList.h"
#include "ListItem.h"

LinkedList::LinkedList(void)
{
 first=last=null;
 count=0;
}

LinkedList::~LinkedList(void)
{
}

void LinkedList::Up(ListItem *L, bool wrap) 
{
}

void LinkedList::Down(ListItem *L, bool wrap)
{
}

// Adds to end of list
void LinkedList::Append(ListItem *L) {
 count++;
 if ( last ) { 
  last->next=L;
  L->prev=last; 
  L->next=null;
  last=L; 
  return; 
 }
 L->next=L->prev=null;
 first=last=L;
}

// Adds to beginning of list
void LinkedList::Prepend(ListItem *L) {
 count++;
 if ( first ) {
  first->prev=L;
  L->next=first;
  L->prev=null;
  first=L;
  return;
 }
 L->next=L->prev=null;
 first=last=L;
}

// Finds element at index i, if none returns null
ListItem *LinkedList::Element(int i) {
 ListItem *l;
 int c=0;
 for ( l=first; l; l=l->next ) {
  if ( (c++)==i ) return l;
 }
 return null;
}

// Inserts element L before p ListItem in List
void LinkedList::InsertBefore(ListItem *L, ListItem *p) {
 L->prev=p->prev;
 L->next=p;
 p->prev=L;
 if ( p == first ) first=L;
 count++;
}

// Inserts element L after p ListItem in List
void LinkedList::InsertAfter(ListItem *L, ListItem *p) {
 L->next=p->next;
 L->prev=p;
 p->next=L;
 if ( p == last ) last=L;
 count++;
}

// Inserts element at index i (before), if index i exists, otherwise returns false
void LinkedList::InsertAt(ListItem *L, int i) {
 ListItem *p=Element(i);
 InsertBefore(L,p);
}

// Removes element L from list
void LinkedList::Remove(ListItem *L) {
 ListItem *p,*n;
 if ( first==last && first==L ) {
  first=last=null; 
  count=0;
  return;
 }
 if ( first==L ) {
  first=first->next;
  first->prev=null;
  L->next=L->prev=null;
  count--;
  return;
 }
 if ( last==L ) {
  last=last->prev;
  last->next=null;
  L->next=L->prev=null;
  count--;
  return;
 }
 p=L->prev;
 n=L->next;
 p->next=null;
 n->prev=null;
 L->prev=L->next=null;
 count--;
 return;
}

// Removes all elements from the list
void LinkedList::RemoveAll(void) {
 first=last=null;
 count=0;
}

// Deletes (frees) element L from list
void LinkedList::Delete(ListItem *L) {
 if ( first==L ) {
  if ( first==last ) {
   first=last=null; 
   delete L;
   count=0;
   return;
  }
 }
 if ( last==L ) {
  last=L->prev;
  delete L;
  count--;
  return;
 }
 L->prev->next=L->next;
 delete L;
 count--;
}