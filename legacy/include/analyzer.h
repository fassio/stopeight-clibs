// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#ifndef ANALYZER_H
#define ANALYZER_H

#include "calculator.h"
#include "listswitchable.h"
#include "listcopyable.h"
#include "cornernormalizer.h"

template<typename T> class Analyzer : public Calculator<T>
{
public:
    //using Calculator<T>::Calculator;
Analyzer<T>(): Calculator<T>() {}
Analyzer<T>(const Analyzer<T>&) = default;
Analyzer<T>(Analyzer<T>&&) = default;
template<typename F> Analyzer(const F& list) {
    auto copy = F(list);
    *this = static_cast<Analyzer<T>&>(copy);
}
//Upcast Move Constructor
template<typename F> Analyzer(F&& list) {
    auto copy = std::move(list);
    *this = static_cast<Analyzer<T>>(copy);
}
    // careful: this is changing order
    // does not change index-numbering variable
    void reverseOrder();

    // make const?
    static Calculator<dpoint> populateTurns(const ListBase<dpoint>& originalData, const QList<QList<dpoint> > slices);

};

#endif // ANALYZER_H
