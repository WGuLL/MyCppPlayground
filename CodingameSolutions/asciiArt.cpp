#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

using namespace std;

/**
 * Resolves https://www.codingame.com/ide/puzzle/ascii-art
 */
int main()
{
    int L;
    cin >> L;
    cin.ignore();
    int H;
    cin >> H;
    cin.ignore();
    string T;
    getline(cin, T);
    std::vector<std::vector<string>> letters;
    const std::string lettersStr{"ABCDEFGHIJKLMNOPQRSTUVWXYZ?"};
    for (int i = 0; i < H; ++i)
    {
        string ROW;
        getline(cin, ROW);
        std::vector<string> letterParts;
        for (auto i = 0; i < ROW.size(); i += L)
        {
            letterParts.push_back(ROW.substr(i, L));
        }
        letters.push_back(letterParts);
    }

    std::vector<string> outputLetters(size_t{H});

    for (auto letter : T)
    {
        if (islower(letter))
        {
            letter = toupper(letter);
        }
        auto letterIdx = lettersStr.find(letter);
        if (letterIdx == string::npos)
        {
            letterIdx = lettersStr.size() - 1;
        }
        for (auto i = 0; i < H; ++i)
        {
            outputLetters[i].append(letters[i][letterIdx]);
        }
    }

    for (auto line : outputLetters)
    {
        std::cout << line << std::endl;
    }
}