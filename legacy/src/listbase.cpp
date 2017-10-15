// Copyright (C) 2009-2015 Specific Purpose Software GmbH
// GNU Lesser General Public License, version 2.1

#include "listbase.h"

//#define debug() QNoDebug()

//using namespace legacy;

template<> ListBase<dpoint>::ListBase() : QList<dpoint>::QList()
{
}

//template<> ListBase<dpoint>::~ListBase(){}


// Note: ALL datamembers of target class destroyed
template<>template<typename F> ListBase<dpoint>::ListBase(F& list) : QList<dpoint>::QList(list){
    *this = static_cast<ListBase<dpoint>& >(list);
}

template<>template<typename F> ListBase<dpoint>::ListBase(const F& list) : QList<dpoint>::QList(list){
    *this = list;
}

// would need to append constructor to QList
//template<>template<typename F> QList<dpoint>::QList(F& list) : QList<dpoint>::QList(list) {
//	*this = static_cast<QList<dpoint>& >(list);
//}
//template QList<dpoint>::QList(ListBase<dpoint>& list);

template ListBase<dpoint>::ListBase(ListBase<dpoint>& list);
#include "spirals.h"
template ListBase<dpoint>::ListBase(Spirals<dpoint>& list);
template ListBase<dpoint>::ListBase(Analyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(AreaAnalyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(CliffsAnalyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(AreaCalculator<dpoint>& list);
template ListBase<dpoint>::ListBase(ListCopyable<dpoint>& list);
template ListBase<dpoint>::ListBase(const ListCopyable<dpoint>& list);
template ListBase<dpoint>::ListBase(TurnNormalizer<dpoint>& list);
template ListBase<dpoint>::ListBase(Calculator<dpoint>& list);
template ListBase<dpoint>::ListBase(ListSwitchable<dpoint>& list);
template ListBase<dpoint>::ListBase(QList<dpoint>& list);
template ListBase<dpoint>::ListBase(AreaNormalizer<dpoint>& list);
template ListBase<dpoint>::ListBase(CornerNormalizer<dpoint>& list);
#include "cliffs.h"
template ListBase<dpoint>::ListBase(Cliffs<dpoint>& list);
template ListBase<dpoint>::ListBase(CliffsNormalizer<dpoint>& list);
#include "turnanalyzer.h"
template ListBase<dpoint>::ListBase(TurnAnalyzer<dpoint>& list);
#include "straightsanalyzer.h"
template ListBase<dpoint>::ListBase(StraightsAnalyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(CornerAnalyzer<dpoint>& list);
template ListBase<dpoint>::ListBase(const CliffsCalculator<dpoint>& list);
template ListBase<dpoint>::ListBase(const AreaCalculator<dpoint>& list);
template ListBase<dpoint>::ListBase(const TurnCalculator<dpoint>& list);
template ListBase<dpoint>::ListBase(const CornerCalculator<dpoint>& list);
template ListBase<dpoint>::ListBase(const Calculator<dpoint>& list);
template ListBase<dpoint>::ListBase(const Spirals<dpoint>& list);
template ListBase<dpoint>::ListBase(const StraightsCalculator<dpoint>& list);
template ListBase<dpoint>::ListBase(const Cliffs<dpoint>& list);
#include "turns.h"
template ListBase<dpoint>::ListBase(const Turns<dpoint>& list);
#include "corners.h"
template ListBase<dpoint>::ListBase(const Corners<dpoint>& list);


template<> QList<QPointF> ListBase<QPointF>::loadSPFile(const QString& fileName)
{
//    debug()<<"legacy::ListBase<dpoint>::loadSPFile "+fileName.toLatin1();
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
		//C++11
		//throw legacy::alg_logic_error((file.errorString().toStdString()+file.fileName().toStdString()).c_str(),__FILE__,__func__);
        throw legacy::alg_logic_error("Unknown filename",__FILE__,"");//(file.errorString().toStdString()+file.fileName().toStdString()).c_str(),__FILE__,"");
		//throw std::string(file.errorString().toStdString() + " reading file " + file.fileName().toStdString());
        //return false;
    }
    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_5);
    unsigned int MagicNumber = 0x8E42B972;
    unsigned int magic;
    in >> magic;
    if (magic != MagicNumber) {
//        debug()<<"File is invalid."<<file.fileName()<<endl<<file.errorString();
        throw std::runtime_error("MainWindow::loadSPFile: Wrong magic number: "+magic);
        //return false;
    }

    dpoint p;
    QList<QPointF> input;
    input.clear();
    while (!in.atEnd()) {
        in >> p;
        input.push_back(QPointF(p.x(),p.y()));
    }
    return input;
}

template<> QList<QPointF> ListBase<dpoint>::convert(ListBase<dpoint> list) {
	QList<QPointF> newlist = QList<QPointF>();
	while (!list.isEmpty()) {
		dpoint point = list.takeFirst();
		newlist.append(QPointF(point.x(),point.y()));
	}
	return newlist;
}

template<> QList<QPointF> ListBase<dpoint>::open(const char *fileName){
    const QString& myString = QString::fromLatin1(fileName);
    //return ListBase<dpoint>::convert(ListBase<dpoint>::loadSPFile(myString));
	return ListBase<QPointF>::loadSPFile(myString);

}

//needed for wrapper!
//template QList<QPointF> ListBase<dpoint>::open(const char *fileName);
//template QList<QPointF> ListBase<dpoint>::convert(ListBase<dpoint> list);

template<> bool ListBase<dpoint>::checkPrecision() {
	/*
	Check if the list contains float values and set precision to high
	*/
	for (int i = 0; i<this->size(); i++) {
		if (!MyReal(this->at(i).x()).isInt() ||
			!MyReal(this->at(i).y()).isInt())
		{
			return true;
		}
	}
	return false;
}
