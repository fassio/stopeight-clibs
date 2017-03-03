// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#include "stdafx.h"

#include <experimental/algorithm>
#include <experimental/impl/algorithm_impl.h>

#include "algo.h"
#include "containers.h"

//double define
#include <experimental/execution_policy>

#include <vector>

using element = std::pair<double, double>;
using it_element = std::pair<typename std::vector<element>::iterator, typename std::vector<element>::iterator>;

using vector_single = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<double>>>;
using vector_pair = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<element>>>;

using vector_vectors = std::_Vector_iterator<std::_Vector_val<std::_Simple_types<it_element>>>;
//using fexec = std::experimental::parallel::parallel_vector_execution_policy;
#include "dummy.h"
using fexec = dummy;

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__calculate_rotations::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag)
{
	//binary,not unary
	std::transform(begin, end - 1, begin + 1, ++begin2, [](double a, double b) {
		int average_df = 0.1f;
		//return asin(b - a);
		//return asin((b - a)/average_df);
		return 300*asin(b - a);
	});
}
template void grapher::__calculate_rotations::operator()(fexec& task1, vector_single begin, vector_single end, vector_single begin2, std::random_access_iterator_tag);

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::__apply_rotation_matrix::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag)
{
	//binary,not unary
	std::transform(begin, end, begin2, begin2, [](double rot, element vec) {
		double x = (cos(rot)*vec.first - sin(rot)*vec.second);
		double y = (sin(rot)*vec.first + cos(rot)*vec.second);
		element p{ x , y };
		return p;
	});
}
template void grapher::__apply_rotation_matrix::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2, std::forward_iterator_tag);

template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::_sum_blocks::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag)
{

	std::transform(begin, end, begin2, [](it_element block) {
		if (block.first != block.second) {
			return std::accumulate(block.first, block.second, element{ 0.0f,0.0f }, [](element v1, element v2) {
				return element{ v1.first + v2.first, v1.second + v2.second };
			});
		}
		else {
			return *block.first;
		}
	});
}
template void grapher::_sum_blocks::operator()(fexec& task1, vector_vectors begin, vector_vectors end, vector_pair begin2, std::random_access_iterator_tag);

int grapher::samples_To_VG_vectorSize(int inputSize, int samplesPerVector) {
	return stopeight::blocks<element>::calculateSize(inputSize,samplesPerVector);
}

double grapher::samples_To_VG_vectorLength(int showSamples, double unitaryLength) {
	return unitaryLength / showSamples;
}

grapher::samples_To_VG::samples_To_VG(int samplesPerVector,double vectorLength) : _samplesPerVector(samplesPerVector), _vectorLength(vectorLength) {
}
grapher::samples_To_VG::~samples_To_VG() {
}
template <class ExecutionPolicy, class Iterator, class OutputIterator> void grapher::samples_To_VG::operator()(ExecutionPolicy& task1, Iterator begin, Iterator end, OutputIterator begin2)
{
	//par
	//std::experimental::parallel::transform(task1, begin, end, begin, [](float f) {return 3.3f; });

	size_t size = std::distance(begin, end);
	std::vector<double> rotations = std::vector<double>(size, 0.0f);
	__calculate_rotations()(task1, begin, end, std::begin(rotations), Iterator::iterator_category{});

	std::vector<element> vectors = std::vector<element>(size, element{ _vectorLength, 0.0f});
	__apply_rotation_matrix()(task1, std::begin(rotations), std::end(rotations), std::begin(vectors), Iterator::iterator_category{});

	stopeight::blocks<element> blocks_vector = stopeight::blocks<element>(std::move(vectors),_samplesPerVector);

	//std::vector<element> out_vectors = std::vector<element>(vectors.size(), { double(0.0f), double(0.0f) });
	std::vector<element> out_vectors = std::vector<element>(blocks_vector.size(), { double(0.0f), double(0.0f) });
	std::fill<typename std::vector<element>::iterator>(std::begin(out_vectors), std::end(out_vectors), element{ 1.0f, 1.0f });

	_sum_blocks()(task1, std::begin(blocks_vector), std::end(blocks_vector), std::begin(out_vectors), Iterator::iterator_category{});

	std::copy<typename std::vector<element>::iterator, OutputIterator>(std::begin(out_vectors), std::end(out_vectors), begin2);
}
template void grapher::samples_To_VG::operator()(fexec& task1, vector_single begin, vector_single end, vector_pair begin2);