#pragma once
#include <algorithm>
#include <functional>
#include <iterator>

template<class _It, class _Key, class _Comp>
bool exponential_search(_It first, _It last, const _Key& key, _Comp comp)
{
	typedef typename std::iterator_traits<_It>::difference_type difference_type;

	if (first == last) return false;
	difference_type size = std::distance(first, last);
	difference_type bound = 1;
	while (bound < size && !comp(key, first[bound]))
	{
		first += bound;
		size -= bound;
		bound = ((bound + 1) << 1) - 1;
	}

	return std::binary_search(first, first + (std::min)(bound, size), key);
}

template<class _It, class _Key>
inline bool exponential_search(_It first, _It last, const _Key& key)
{
	typedef typename std::iterator_traits<_It>::value_type value_type;
	return exponential_search(first, last, key, std::less<_Key>());
}

