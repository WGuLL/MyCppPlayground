#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

// https://www.codingame.com/ide/puzzle/rock-paper-scissors-lizard-spock

using Sign = std::string_view;

struct Player
{
    Player(size_t id_, char sign_) noexcept : id (id_), sign (sign_){} 
    size_t id;
    char sign;
    std::vector<size_t> pastOpponents;

    [[nodiscard]] Player withDefeatedOpponent (const Player& other) const
    {
        auto newPlayer = *this;
        newPlayer.pastOpponents.push_back(other.id);
        return newPlayer;
    }
};

namespace
{
[[nodiscard]] Player extractPlayer (const std::string& idStr, std::string_view signStr)
{
    const auto playerId = std::stoul (idStr.data ());
    return {playerId, signStr.front ()};
}

[[nodiscard]] Player confront (const Player& p1, const Player& p2)
{
    if (p1.sign == p2.sign)
    {
        return p1.id < p2.id ? p1.withDefeatedOpponent(p2) : p2.withDefeatedOpponent(p1);
    }
    if (p1.sign == 'C')
    {
        if (p2.sign == 'P' or p2.sign == 'L')
        {
            return p1.withDefeatedOpponent(p2);
        }
        return p2.withDefeatedOpponent(p1);
    }
    if (p1.sign == 'P')
    {
        if (p2.sign == 'R' or p2.sign == 'S')
        {
            return p1.withDefeatedOpponent(p2);
        }
        return p2.withDefeatedOpponent(p1);
    }
    if (p1.sign == 'R')
    {
        if (p2.sign == 'L' or p2.sign == 'C')
        {
            return p1.withDefeatedOpponent(p2);
        }
        return p2.withDefeatedOpponent(p1);
    }
    if (p1.sign == 'L')
    {
        if (p2.sign == 'S' or p2.sign == 'P')
        {
            return p1.withDefeatedOpponent(p2);
        }
        return p2.withDefeatedOpponent(p1);
    }
    else
    {
        if (p2.sign == 'C' or p2.sign == 'R')
        {
            return p1.withDefeatedOpponent(p2);
        }
        return p2.withDefeatedOpponent(p1);
    }
}

[[nodiscard]] Player findWinner (const std::vector<Player>& players)
{   
    std::vector<Player> nextRound;
    for (auto i = 0; i < players.size(); i+=2)
    {
        nextRound.push_back (confront(players[i], players[i + 1]));
    }
    if (nextRound.size () == 1)
    {
        return nextRound.front();
    }
    return findWinner (nextRound);
}
}

int main()
{
    std::istream_iterator<std::string> input (std::cin);
    std::advance(input, 1); // Not needed with this implementation.
    std::vector<Player> players;
    while (input != std::istream_iterator<std::string> ())
    {
        const std::string& playerId = *input++;
        const std::string_view sign = *input++;
        players.emplace_back (extractPlayer (playerId, sign));
    }
    const auto winner = findWinner (players);
    std::cout << winner.id << std::endl;
    for_each (std::begin (winner.pastOpponents), std::prev(std::end (winner.pastOpponents)), [](const auto& opp)
    {
        std::cout << opp << " ";
    });
    std::cout << *std::prev(std::end (winner.pastOpponents)) << std::endl;
}
