// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include <experimental/algorithm>

#include "algo_impl.h"

//double define
//#include <sycl/execution_policy>
#include <vector>

template <class ExecutionPolicy, class Iterator, class OutputIterator>
void grapher::samples_To_VG(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	//par
	//sycl::impl::transform(task1_sub1, begin, end,begin2, [](float f) {return 3.3f; });//its doing queue stuff internally -> not sycl inside sycl
	std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });
}

// Taken from msvc symbol error
using fvect = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<float>>>;
//using dvect = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<double>>>;
template void grapher::samples_To_VG(std::experimental::parallel::v1::parallel_execution_policy& task1, fvect begin, fvect end, fvect begin2);
//template void grapher::samples_To_VG(dvect begin, dvect end, dvect begin2);