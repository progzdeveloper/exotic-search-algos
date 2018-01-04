#include <iostream>
#include <algorithm>
#include <list>
#include <vector>

#include "interpolation_search.h"

/*! Usage example */
/*
 * This example show a possible use case
 * for interpolation_search() algorithm.
 *
 * In this example we have a vector of strings in witch we want to search
 * a some key.
 *
 * First of all we define a projector functor (in our case it's a hash).
 * Then we sort out string array according to projection functor,
 * and finally apply interpolation_search() to find out where our key is placed.
 */
int main()
{
    using namespace std;
    // input data: this array is not so big for example purposes,
    // but in a real world it may contain a millions of elements
    vector<string> vec = {
        "Hello", "from", "GCC", __VERSION__, "!" 
    };
    
    // our projection functor
    hash<string> proj; 
    
    // sort according to a projection
    sort(vec.begin(), vec.end(), [&proj](const string& x, const string& y) {
        return proj(x) < proj(y);
    });
    
    // print out the sorted data
    copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "\n"));
    
    string key = "!"; // the key we are looking for
    // perform interpolation search
    auto it = interpolation_search(vec.begin(), vec.end(), key, proj);
    if (it != vec.end())
        cout << "Found: '"<< key << "' at position: " << distance(vec.begin(), it) << endl;
    else
        cout << '\''<<  key << "' not found" << endl;
    
    return 0;
}
