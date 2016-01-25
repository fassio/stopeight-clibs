// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CLIFFSCALCULATOR_H
#define CLIFFSCALCULATOR_H

#include "listswitchable.h"

template<typename T> class CliffsCalculator : public ListSwitchable<T>
{
public:
    CliffsCalculator<T>();
    template<typename F> CliffsCalculator<T>(F& list);


};

#endif // CLIFFSCALCULATOR_H
