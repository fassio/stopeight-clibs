// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef PRELOADERIF_H
#define PRELOADERIF_H

#include <memory>
#include <vector>

namespace grapher {

	template<typename T,typename ReturnType>class PreloaderIF
	{
	public:
		//makes implementation!!
		//PreloaderIF<T>();
		PreloaderIF<T,ReturnType>(std::vector<T>* s);
		virtual ~PreloaderIF<T,ReturnType>(){};

		virtual ReturnType operator()(int samplesPerPixel) =0;
	};
}

#endif
