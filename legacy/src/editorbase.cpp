// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "editorbase.h"

//#define debug() QDebug(QtDebugMsg)//::QDebug(QtDebugMsg)
//#define debug() QNoDebug()

template<typename T> EditorBase<T>::EditorBase() : EditorInterface<T>(), data(ListStorage<T>())
{
    //Note: data has to be allocated in subclass!
    //debug()<<"EditorBase<T>::EditorBase() constructor called and data initialized";
}

template EditorBase<ListSwitchable<dpoint> >::EditorBase();

//EditorBase::~EditorBase(){
//    data.input.~ListSwitchable();
//    data.output.~ListSwitchable();
//}

template<typename T> T& EditorBase<T>::getOutput(){
    return data.output;
}

template ListSwitchable<dpoint>& EditorBase<ListSwitchable<dpoint> >::getOutput();


/*template<typename T> ListSwitchable<dpoint> EditorBase<T>::getConvertedOutput() {
	auto newlist = ListSwitchable<dpoint>();
	for (int i = 0; i < data.output.size(); i++) {
		newlist.append(QPointF(data.output[i].x(),data.output[i].y()));
	}
	return newlist;
}
template ListSwitchable<dpoint> EditorBase<ListSwitchable<dpoint> >::getConvertedOutput();*/

template<typename T> void EditorBase<T>::setOutput(T list){
    data.output=list;
}

template void EditorBase<ListSwitchable<dpoint> >::setOutput(ListSwitchable<dpoint> list);

template<> void EditorBase<ListSwitchable<dpoint> >::resetLists(){
    data.input.clear();
    data.output.clear();
}

template<> void EditorBase<ListSwitchable<dpoint> >::addPoint(QPointF p){
     if (p.x()>=0 && p.y()>=0){
         dpoint newpoint(p);
         newpoint.position = data.input.size();
         data.input.push_back(newpoint);
    }else {
         throw std::runtime_error("Invalid point. Only positive point coordinates accepted.");
     }
}

template<> void EditorBase<ListSwitchable<dpoint> >::flushOutput(){
    data.output.clear();
    setOutput(data.input);
}

template<> void EditorBase<ListSwitchable<dpoint> >::automatic(){
    this->flushOutput();
    //debug()<<"Computation started with data size "<<this->getOutput().size();
    this->process(this->getOutput());
}

template<> void EditorBase<ListSwitchable<dpoint> >::automatic(ListSwitchable<dpoint> list) {
	if (list.size() > 2) {
		for (int i = 0; i < list.size(); i++) {
			this->addPoint(list.at(i));
		}
		automatic();
	}
	else {
        throw std::runtime_error("List can not be valid. At least TCT required.");
	}
}

template<> void EditorBase<ListSwitchable<dpoint> >::mainIterator(const ListSwitchable<dpoint> constCliffs,QList<ListSwitchable<dpoint> >& slicesRef){
    ListSwitchable<dpoint> out = this->getOutput();
    int currentSegment = 0;
    //maemo works: check cliff size
    std::array<ListSwitchable<dpoint>::iterator,2> it;
    if (constCliffs.size()==0){
        currentSegment += 1;
        it = out.position_to_iterator(out.first().position,out.last().position);
        slicesRef << this->processSegment(it[0],it[1]);
    } else {
        for (int i=0;i<constCliffs.size();i++){
            currentSegment += 1;
            if (i==0){
                it = out.position_to_iterator(out.first().position,constCliffs[i].position-1);
                // the last one does not have an illegal point in the end:
                // but has to be omitted to be consistent with rest. see bug below
            } else if (i==constCliffs.size()-1) {
                //slicesRef << processSegment(out.chopCopy(constCliffs[i-1].position,constCliffs[i].position));
                it = out.position_to_iterator(constCliffs[i-1].position,constCliffs[i].position-1);
            } else {
                it = out.position_to_iterator(constCliffs[i-1].position,constCliffs[i].position-1);
            }
            slicesRef << this->processSegment(it[0],it[1]);
        }
        currentSegment += 1;
        // it might have to hop over last point of second last segment? - bug.
        // dangerous: +1
        //slicesRef << processSegment(out.chopCopy(constCliffs[constCliffs.size()-1].position+1,out.last().position));
        it = out.position_to_iterator(constCliffs[constCliffs.size()-1].position,out.last().position);
        slicesRef << processSegment(it[0],it[1]);
    }
}


//void EditorBase::process(ListAnalyzer<dpoint> toBeProcessed){
//    throw "ERROR: EditorBase::process called. this should be superclass-call";
//}
