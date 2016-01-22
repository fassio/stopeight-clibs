// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "include/spiralsanalyzer.h"

template<> SpiralsAnalyzer<dpoint>::SpiralsAnalyzer() : SpiralsCalculator<dpoint>() {}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> SpiralsAnalyzer<dpoint>::SpiralsAnalyzer(F& list){
    *this = static_cast<SpiralsAnalyzer<dpoint>& >(list);
}

// Note: ALL datamembers of target class destroyed
template<>template<typename F> void SpiralsAnalyzer<dpoint>::operator=(F& list){
    this->swap(list);
}

template<> bool SpiralsAnalyzer<dpoint>::consistencyCheck(QList<dpoint> cliffs){
    debug()<<"We have "<< cliffs.size() << " cliffs in input.";
    if (cliffs.size()!=0 && fmod(cliffs.size(),2) == 0){
        debug()<< "ShapeMatcher::verify: Inconsistency: even number of cliffs not allowed";
        //throw "ShapeMatcher::verify: Inconsistency: even number of cliffs not allowed";
    } else {
        return true;
    }
    return false;
}




