#pragma once
#include <utility>
#include <iterator>
#include <type_traits>
#include <cassert>

template<class _It, class _Key>
_It interpolation_search(_It first, _It last, const _Key& key)
{
	typedef typename std::iterator_traits<_It>::iterator_category category;
	static_assert(std::is_same<category, std::random_access_iterator_tag>::value,
		      "interpolation_search() can be used with random access iterators only");

	if (first == last) 
		return last;

	_It low = first;
	_It high = std::prev(last);
	_It mid;

	while (*high != *low && key >= *low && key <= *high) 
	{
		mid = low + ((key - *low) * (high - low) / (*high - *low));

		if (*mid < key)
			low = mid + 1;
		else if (*mid > key)
			high = mid - 1;
		else
			return mid;
	}

	return ((key == *low) ? low : last);
}

template<class _It, class _Key, class _Proj>
_It interpolation_search(_It first, _It last, const _Key& what, _Proj proj = std::hash<_Key>())
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


/*! Usage example

int main()
{
    using namespace std;
    vector<string> vec = {
        "Hello", "from", "GCC", __VERSION__, "!" 
    };
    
    hash<string> proj;
    sort(vec.begin(), vec.end(), [&proj](const string& x, const string& y) {
        return proj(x) < proj(y);
    });
    
    copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "\n"));
    
    string key = "!";
    auto it = interpolation_search(vec.begin(), vec.end(), key, proj);
    if (it != vec.end())
        cout << "Found: '"<< key << "' at position: " << distance(vec.begin(), it) << endl;
    else
        cout << '\''<<  key << "' not found" << endl;
    
    return 0;
    
}
*/



