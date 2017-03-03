// Copyright (C) 2017 Fassio Blatter
// GNU Lesser General Public License, version 2.1

#ifndef ALGO_H
#define ALGO_H

namespace grapher {
	//specialization: 1 iterator_category, 2 value_types
	class __calculate_rotations {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2,std::random_access_iterator_tag);
	};

	//specialization: 1 iterator_category, 2 value_types
	class __apply_rotation_matrix {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag);
	};

	//specialization: 1 iterator_category, 2 value_types
	class _sum_blocks {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::random_access_iterator_tag);
	};

	//specialization: 1 iterator_category, 2 value_types
	class _append {
	public:
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2, std::forward_iterator_tag);
	};

	int samples_To_VG_vectorSize(int inputSize, int samplesPerVector=1);
	double samples_To_VG_vectorLength(int showSamples, double unitaryLength = 1);
	template <class Iterator> std::pair<std::pair<double,double>, std::pair<double, double>> samples_To_VG_lengthPos(Iterator begin, Iterator end, double vectorLength, double unitaryLength);

	class samples_To_VG {
	public:
		samples_To_VG(int samplesPerVector,double vectorLength);
		~samples_To_VG();

		//specialization: 1 iterator_category, 2 value_types
		template <class ExecutionPolicy, class Iterator, class OutputIterator>void operator()(ExecutionPolicy&, Iterator begin, Iterator end, OutputIterator begin2);

	private:
		int _samplesPerVector;
		double _vectorLength;
	};
}
#endif