#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

#include "exponential_search.h"

/*! Usage example */
/*
 * This example show a possible use case
 * for exponential_search() algorithm.
 *
 * In this example we have a vector of strings in witch we want to search
 * a some key.
 *
 * First of all we sort out string array and then apply exponential_search() 
 * to find out where our key is placed.
 */
int main()
{
    	using namespace std;
	    // input data
	    vector<string> vec = {
		    "Hello", "from", "GCC", __VERSION__, "!" 
	    };

	    // sort
	    sort(vec.begin(), vec.end());

	    // print out the sorted data
	    copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "\n"));

	    string key = "GCC"; // the key we are looking for
	    auto it = exponential_search(vec.begin(), vec.end(), key);
	    if (it != vec.end())
        	cout << "Found: '"<< key << "' at position: " << distance(vec.begin(), it) << endl;
    	else
		      cout << '\''<< key << "' not found" << endl;
	    return 0;
}

