// Resolves https://www.codingame.com/training/easy/horse-racing-duals

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

int main()
{
    vector<int> sortedValues, adjacentDifferences;
    copy(++istream_iterator<int>(cin), istream_iterator<int>(), back_inserter(sortedValues));
    sort(begin(sortedValues), end(sortedValues));
    adjacent_difference(begin(sortedValues), end(sortedValues), back_inserter(adjacentDifferences));
    cout << *min_element(begin(adjacentDifferences), end(adjacentDifferences)) << endl;
}
