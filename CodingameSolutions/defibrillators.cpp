// Resolves https://www.codingame.com/ide/puzzle/defibrillators

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <locale.h>

using namespace std;

namespace
{
struct Position
{
    double longitude{0};
    double latitude{0};

    double calculateDistance(const Position &other) const
    {
        const auto x = (other.longitude - longitude) * cos((latitude + other.latitude) / 2);
        const auto y = (other.latitude - latitude);
        return sqrt(pow(x, 2) + pow(y, 2)) * 6371;
    }
};

struct DefibInfo
{
    DefibInfo(const std::string &defibName, const Position &defibPos, const Position &userPosition) : name(defibName), pos(defibPos)
    {
        distance = defibPos.calculateDistance(userPosition);
    }
    std::string name;
    Position pos;
    double distance{0.};
};

template <char token>
class StringWithToken
{
  public:
    std::string data;
};

template <char token>
std::istream &operator>>(std::istream &is, StringWithToken<token> &output)
{
    std::getline(is, output.data, token);
    return is;
}

double myStod(const string &input)
{
    return stod(string(input).replace(input.find(','), 1, "."));
}

DefibInfo parse(const StringWithToken<'\n'> &inputStr, const Position &userPos)
{
    istringstream sstr(inputStr.data);
    istream_iterator<StringWithToken<';'>> inputIt(sstr);
    const auto name = (++inputIt)->data;
    advance(inputIt, 3);
    return DefibInfo(name, {myStod(inputIt++->data), myStod(inputIt++->data)}, userPos);
}
} // namespace

int main()
{
    istream_iterator<StringWithToken<'\n'>> inputIt(cin);
    Position pos({myStod(inputIt++->data), myStod(inputIt++->data)});
    advance(inputIt, 1);
    vector<DefibInfo> defibInfos;
    transform(inputIt, istream_iterator<StringWithToken<'\n'>>(), back_inserter(defibInfos),
              [pos](const auto &line) {
                  return parse(line, pos);
              });
    cout << min_element(begin(defibInfos), end(defibInfos),
                        [&pos](const auto &lhs, const auto &rhs) {
                            return lhs.distance < rhs.distance;
                        })
                ->name
         << endl;
}
