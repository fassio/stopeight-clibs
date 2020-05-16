// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

//#ifndef CLIFFS_H
//#define CLIFFS_H

#include "listswitchable.h"
#include "analyzer.h"
#include "cliffsanalyzer.h"

template<typename T> class Cliffs : public ListSwitchable<T>
{
public:
    //using ListSwitchable<T>::ListSwitchable;
Cliffs<T>() : ListSwitchable<T>() {}
template<typename F> Cliffs(const F& list) {
    auto copy = F(list);
    *this = static_cast<Cliffs<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> Cliffs(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<Cliffs<T>>(copy);
}

    static QList<dpoint> findCliffs(ListSwitchable<dpoint> output);

};

//#endif // CLIFFS_H
