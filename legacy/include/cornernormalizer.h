// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef CORNERNORMALIZER_H
#define CORNERNORMALIZER_H

#include "cornercalculator.h"
#include "calculator.h"


template<typename T> class CornerNormalizer : public CornerCalculator<T>
{
public:
    CornerNormalizer<T>();
    template<typename F> CornerNormalizer<T>(F& list);
    template<typename F> void operator=(F& list);

    void requireMinimumLength(qreal length);

};

#endif // CORNERNORMALIZER_H
