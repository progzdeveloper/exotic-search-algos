#pragma once
#include <iterator>
#include <type_traits>
#include <cassert>

template<class _It, class _Key, class _Proj>
_It interpolation_search(_It first, _It last, const _Key& what, _Proj proj)
{
	typedef typename _Proj::result_type index_type;
	typedef typename std::iterator_traits<_It>::iterator_category category;
	static_assert(std::is_same<category, std::random_access_iterator_tag>::value,
		      "interpolation_search() can be used with random access iterators only");

	if (first == last) 
		return last;

#ifndef NDEBUG
	assert(std::is_sorted(first, last, [&proj](const _Key& x, const _Key& y) { return proj(x) < proj(y); }));
#endif

	_It lowIt = first;
	_It highIt = std::prev(last);
	_It midIt;

	index_type mid; 
	index_type low = proj(*lowIt);
	index_type high = proj(*highIt);
	index_type key = proj(what);

	while (high != low && key >= low && key <= high) 
	{
		midIt = lowIt + ((key - low) * (highIt - lowIt) / (high - low));
		mid = proj(*midIt);

		if (mid < key) {
			lowIt = midIt + 1;
			low = proj(*lowIt);
		}
		else if (mid > key) {
			highIt = midIt - 1;
			high = proj(*highIt);
		}
		else
			return midIt;
	}

	return ((key == low) ? lowIt : last);
}



