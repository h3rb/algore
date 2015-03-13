
/***********************************************************************************************
 * OpenGL Window and Animation Library (formerly the Open Art Engine)                          *
 ***********************************************************************************************
 * This software is copyrighted software.  Use of this code is given only with permission to   *
 * parties who have been granted such permission by its author, Herbert Elwood Gilliland III   *
 ***********************************************************************************************
 * Copyright (c) 2010 Herbert Elwood Gilliland III ; All rights reserved.                      *
 ***********************************************************************************************/

#include "macros.h"
#include "ListItem.h"


ListItem::ListItem(void)
{
 next=prev=null;
}


ListItem::~ListItem(void)
{
}

void ListItem::Virtual(void) 
{
}