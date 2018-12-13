#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <bitset>

using namespace std;

// Resolves https://www.codingame.com/ide/puzzle/chuck-norris
int main()
{
    string message, binaryStr, answer;
    getline(cin, message);
    for (const auto c : message)
    {
        binaryStr += bitset<7>(c).to_string();
    }

    auto it = begin(binaryStr);
    while (it != end(binaryStr))
    {
        answer += *it == '0' ? "00 " : "0 ";
        const auto endOfSerie = find_if_not(it, end(binaryStr), [&it](const char &c) { return c == *it; });
        fill_n(back_inserter(answer), distance(it, endOfSerie), '0');
        answer += ' ';
        it = endOfSerie;
    }
    answer.resize(answer.size() - 1);
    cout << answer << endl;
}
