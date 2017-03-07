//#pragma once
#ifndef SHARED_TYPES_H
#define SHARED_TYPES_H
namespace sp {

	enum class tctype
	{
		EMPTY,
		TURN,
		CORNER
	};
	template<typename T> struct timecode : public std::pair<T,T> {
	public:
		using std::pair<T, T>::pair;
		using timecode_types = typename tctype;
		timecode_types category{sp::tctype::EMPTY};
		//virtual ~timecode() = 0;
	};
	template<typename T> struct turn : timecode<T> {
	public:
		using timecode_types = typename timecode::timecode_types;
		timecode_types category{ sp::tctype::TURN };
		
		//fixpoint() {};
		//fixpoint(timecode&& point) :*this{point}
		//~fixpoint() override {
		//	throw std::exception("fixpoints refer to timecode data and can not be deleted.");
		//};
	};
	using element = timecode<double>;
	//using element = std::pair<double, double>;
	using result = std::pair<std::vector<element>, std::vector<element>>;
	//using result = std::vector<element>;
	double static _angle(double diff) { return 300 * asin(diff); };
}
sp::element static operator+(const sp::element& a, const sp::element& b) { return sp::element{ a.first + b.first, a.second + b.second }; };
sp::element static operator-(const sp::element& a, const sp::element& b) { return sp::element{ a.first - b.first, a.second - b.second }; };

#endif