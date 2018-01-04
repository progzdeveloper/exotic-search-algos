#pragma once
#include <algorithm>
#include <functional>
#include <iterator>

template<class _It, class _Key, class _Comp>
_It exponential_search(_It first, _It last, const _Key& key, _Comp comp)
{
	typedef typename std::iterator_traits<_It>::difference_type difference_type;

	if (first == last) 
		return last;

#ifndef NDEBUG
	assert(std::is_sorted(first, last, comp));
#endif
	difference_type size = std::distance(first, last);
	difference_type bound = 1;
	while (bound < size && !comp(key, first[bound]))
	{
		first += bound;
		size -= bound;
		bound = ((bound + 1) << 1) - 1;
	}

	return std::lower_bound(first, first + (std::min)(bound, size), key);
}

template<class _It, class _Key>
inline _It exponential_search(_It first, _It last, const _Key& key) {
	return exponential_search(first, last, key, std::less<_Key>());
}

