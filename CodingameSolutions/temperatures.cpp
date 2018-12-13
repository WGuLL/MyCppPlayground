#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <algorithm>

using namespace std;

/**
 *  Resolves https://www.codingame.com/ide/puzzle/temperatures
 */
int main()
{
    int n; // the number of temperatures to analyse
    cin >> n;
    cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);

    auto result = 0;

    if (n != 0)
    {
        std::vector<int> temperatures(n);
        std::regex ws_re("\\s+");
        std::transform(std::sregex_token_iterator(temps.begin(), temps.end(), ws_re, -1),
                       std::sregex_token_iterator(),
                       std::begin(temperatures),
                       [](const std::string &t) {
                           return std::stoi(t);
                       });
        //Computes result
        result = *std::min_element(std::begin(temperatures),
                                   std::end(temperatures),
                                   [](int a, int b) {
                                       const auto aAbs = std::abs(a);
                                       const auto bAbs = std::abs(b);
                                       const auto result = (aAbs == bAbs) ? a > b : aAbs < bAbs;
                                       return result;
                                   });
    }

    cout << result << endl;
}
