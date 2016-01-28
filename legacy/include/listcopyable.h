// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef LISTCOPYABLE_H
#define LISTCOPYABLE_H

#include "dpoint.h"
#include "listbase.h"
#include "listswitchable.h"

template<typename T> class ListCopyable : public ListBase<T>
{
public:
    ListCopyable();

    template<typename F> ListCopyable<T>(F& list);
    //template<typename F> ListCopyable<T>(const F list);
    //overwrite & operator for being stolen from listswitchable and cast to listswitchable
    //ListSwitchable<dpoint>* operator&();

    ListCopyable<dpoint> chopCopy(int startPosition, int endPosition);

private:
    int calls;

};

#endif // LISTCOPYABLE_H