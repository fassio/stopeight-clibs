// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/turncalculator.h"

template<> TurnCalculator<dpoint>::TurnCalculator() : ListInitializer<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> TurnCalculator<dpoint>::TurnCalculator(F& list){
    ListInitializer<dpoint> c = static_cast<ListInitializer<dpoint>& >(list);
    *this= static_cast<TurnCalculator<dpoint>& >(c);
}

// this has performance penalty!
template <> qreal TurnCalculator<dpoint>::getRegressionValueFor2Points(int pos, bool value){
    // segment is pointing forward for compatibility with calcTail in calculateDeltas
    // is this PROgression?
    if (pos>=0 && pos<this->size()-3){
        ListRotator<dpoint> regSeg = ListRotator<dpoint>();
        regSeg << this->at(pos) << this->at(pos+1) << this->at(pos+2) << this->at(pos+3);
        // this has to stay on XAxis
        regSeg.rotateSegmentToXAxis();
        qreal regH1 = regSeg.at(1).rot.y();
        qreal regH2 = regSeg.at(2).rot.y();
        if (value == REGH1) {
            return regH1;
        } else if (value == REGH2) {
            return regH2;
        }
    }
    throw "ListCalculator<dpoint>::getRegressionValue";
}

template <> qreal TurnCalculator<dpoint>::regH1At(int i){
    qreal cregH1 = getRegressionValueFor2Points(i,REGH1);
    return cregH1;
}

template <> qreal TurnCalculator<dpoint>::regH2At(int i){
    qreal cregH2 = getRegressionValueFor2Points(i,REGH2);
    return cregH2;
}

template <> bool TurnCalculator<dpoint>::isRegLineThroughAt(int i){
    qreal regH1 = this->regH1At(i);
    qreal regH2 = this->regH2At(i);
    if (/*(regH1 >=0 && regH2 <0) ||
        (regH1 <0 && regH2 >=0) ||
        (regH1 ==0 && regH2 ==0) */
            (regH1 >=0 && regH2 <0) ||
            (regH1 <=0 && regH2 >0)) {
        return true;
    } else {
        return false;
    }
}