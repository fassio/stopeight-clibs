// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

//#ifndef SPIRALS_H
//#define SPIRALS_H

#include "listinitializer.h"
#include "areaanalyzer.h"
#include "analyzer.h"

template<typename T> class Spirals : public ListInitializer<T>
{
public:
    Spirals<T>();
    template<typename F> Spirals<T>(F& list);

    static QList<dpoint> findSpirals(ListBase<dpoint> output,bool& pleaseReverse);

private:
    static QList<dpoint> findAreas(ListBase<dpoint>& stroke, qreal limit);
    //auxiliary function for findAreas
    static qreal findLimit(ListBase<dpoint> toBeProcessed);

};

//#endif // SPIRALS_H
