
/***********************************************************************************************
 * OpenGL Window and Animation Library (formerly the Open Art Engine)                          *
 ***********************************************************************************************
 * This software is copyrighted software.  Use of this code is given only with permission to   *
 * parties who have been granted such permission by its author, Herbert Elwood Gilliland III   *
 ***********************************************************************************************
 * Copyright (c) 2010 Herbert Elwood Gilliland III ; All rights reserved.                      *
 ***********************************************************************************************/

#pragma once
#include "ListItem.h"
class LinkedList
{
public:
	int count;
	ListItem *first;
	ListItem *last;

	LinkedList(void);
	~LinkedList(void);

 void Up(ListItem *L, bool wrap);
 void Down(ListItem *L, bool wrap);
	void Append(ListItem *L);
 void Prepend(ListItem *L);
	ListItem *Element(int i);
	void InsertBefore(ListItem *L,ListItem *p);
 void InsertAfter(ListItem *L, ListItem *p);
	void InsertAt(ListItem *L, int i);
	void Remove(ListItem *L);
 void RemoveAll(void);
	void Delete(ListItem *L);
};

