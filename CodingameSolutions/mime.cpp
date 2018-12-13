#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>

using namespace std;
namespace
{
string toLower(const string &str)
{
    string lowerStr;
    transform(begin(str), end(str), back_inserter(lowerStr), ::tolower);
    return lowerStr;
}
} // namespace

struct keyComp
{
    bool operator()(const string &lhs, const string &rhs) const
    {
        return toLower(lhs) < toLower(rhs);
    }
};

/**
 * Resolves https://www.codingame.com/ide/puzzle/mime-type
 */
int main()
{
    istream_iterator<string> istr(cin);
    const auto nbTypes = stoi(*istr++);
    const auto nbFiles = stoi(*istr++);
    std::map<string, string, keyComp> mappingTable;

    for (auto i = 0; i < nbTypes; ++i)
    {
        auto key = *istr++;
        auto value = *istr++;
        mappingTable.insert(make_pair<string, string>(move(key), move(value)));
    }
    for (auto i = 0; i < nbFiles; ++i)
    {
        const auto fileNameStr = *istr++;
        const auto tokenPosition = find(fileNameStr.rbegin(), fileNameStr.rend(), '.');
        const auto fileType = tokenPosition == fileNameStr.rend() ? "" : mappingTable[fileNameStr.substr(distance(tokenPosition, fileNameStr.rend()))];
        cout << (fileType == "" ? "UNKNOWN" : fileType) << endl;
    }
}