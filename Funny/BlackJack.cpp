#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <string_view>
#include <cstring>
#include <cstdio>
#include <array>
#include <random>


using namespace std;



namespace Random
{
    std::mt19937 mt{ std::random_device{}() };

    int get(int min, int max)
    {
        std::uniform_int_distribution die{ min, max };
        return die(mt);
    }
}

enum class ranks
{
	r_2,
	r_3,
	r_4,
	r_5,
	r_6,
	r_7,
	r_8,
	r_9,
	r_10,
	Jack,
	Queen,
	King,
	Ace,
	max_ranks,
};

enum class suits
{
	clubs,
	diamonds,
	hearts,
	spades,
	max_suits,
};

struct Card
{
	ranks c_rank{};
	suits c_suit{};
};

void printCard(const Card& card)
{
    switch (card.c_rank)
    {
    case ranks::r_2:      std::cout << '2';   break;
    case ranks::r_3:      std::cout << '3';   break;
    case ranks::r_4:      std::cout << '4';   break;
    case ranks::r_5:      std::cout << '5';   break;
    case ranks::r_6:      std::cout << '6';   break;
    case ranks::r_7:      std::cout << '7';   break;
    case ranks::r_8:      std::cout << '8';   break;
    case ranks::r_9:      std::cout << '9';   break;
    case ranks::r_10:     std::cout << "10";   break;
    case ranks::Jack:   std::cout << 'J';   break;
    case ranks::Queen:  std::cout << 'Q';   break;
    case ranks::King:   std::cout << 'K';   break;
    case ranks::Ace:    std::cout << 'A';   break;
    default:
        std::cout << '?';
        break;
    }

    switch (card.c_suit)
    {
    case suits::clubs:       std::cout << 'C';   break;
    case suits::diamonds:    std::cout << 'D';   break;
    case suits::hearts:      std::cout << 'H';   break;
    case suits::spades:      std::cout << 'S';   break;
    default:
        std::cout << '?';
        break;
    }
}

void createDeck(std::array<Card, 52>& pack)
{
    int index{ 0 };
        for (int i = 0; i < static_cast<int>(ranks::max_ranks); i++)
        {
            for (int g = 0; g < static_cast<int>(suits::max_suits); g++)
            {
                pack[index].c_rank = static_cast<ranks>(i);
                pack[index].c_suit = static_cast<suits>(g);
                ++index;
            }
        }
}

void printDeck(const std::array<Card, 52>& pack)
{
    for (const auto& iterator : pack)
    {
        printCard(iterator);
        cout<< ' ';
    }
    cout << '\n';
}

void shuffleDeck(std::array<Card, 52>& pack)
{
    static std::mt19937 mt{ static_cast<std::mt19937::result_type>(std::time(nullptr)) };
    std::shuffle(pack.begin(), pack.end(),mt);
}

int getCardValue(const Card& card)
{
    switch (card.c_rank)
    {
    case ranks::r_2:      return 2; 
    case ranks::r_3:      return 3;
    case ranks::r_4:      return 4;
    case ranks::r_5:      return 5;
    case ranks::r_6:      return 6;
    case ranks::r_7:      return 7;
    case ranks::r_8:      return 8;
    case ranks::r_9:      return 9;
    case ranks::r_10:    
    case ranks::Jack:   
    case ranks::Queen:  
    case ranks::King:   
        return 10;
    case ranks::Ace:   
        return 11;
    default:
        cout << "Undefined Card Value\n";
        return INT_MAX;
    }
}


void printVector(const vector<Card>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        printCard(vec[i]); 
        cout << ' ';
    }
}

int getSum(const vector<Card>& vec)
{
    int sum = { 0 };
    for (int i = 0; i < vec.size(); i++)
    {
        sum += getCardValue(vec[i]);
    }
    return sum;
}
bool solo_BlackJack()
{

    std::array<Card, 52> pack;
    createDeck(pack);
    shuffleDeck(pack);
    vector<Card> vec;
    vec.push_back(pack[Random::get(0, 51)]);
    vec.push_back(pack[Random::get(0, 51)]);

    cout << "Welcome to BlackJack!\n";
    cout << "\nYour cards is ";
    printVector(vec);
    {
        int mySum = getSum(vec);
        if (mySum == 21)
            return true;
        cout << "\nSum is " << mySum << '\n';
    }
    char c{};
    while (true)
    {
        cin >> c;
        if (c == 's')
            break;
        vec.push_back(pack[Random::get(0, 51)]);
        printVector(vec);
        cout << '\n';
        int summary = getSum(vec);
        cout << "Sum is " << summary << '\n';
        if (summary > 21)
            return false;
        else if (summary == 21)
            return true;
    }
}

bool duo_BlackJack()
{
    std::array<Card, 52> pack;
    createDeck(pack);
    shuffleDeck(pack);
    vector<Card> vec1;
    vector<Card> vec2;
    vec1.push_back(pack[Random::get(0, 51)]);
    vec2.push_back(pack[Random::get(0, 51)]);
    vec2.push_back(pack[Random::get(0, 51)]);

    cout << "Welcome to BlackJack!\n";
    cout << "Diler's card is ";
    printVector(vec1);
    cout << "\nYour cards is ";
    printVector(vec2);
    {
        int mySum = getSum(vec2);
        if (mySum == 21)
            return true;
        cout << "\nSum is " << mySum << '\n';
    }
    char c{};
    int summary{};
    while (true)
    {
        cin >> c;
        if (c == 's')
            break;
        vec2.push_back(pack[Random::get(0, 51)]);
        printVector(vec2);
        cout << '\n';
        summary = getSum(vec2);
        cout << "Sum is " << summary << '\n';
        if (summary > 21)
            return false;
        else if (summary == 21)
            return true;
    }
    int diler_summary = getCardValue(vec1[0]);
    while (diler_summary < 17)
    {
        vec1.push_back(pack[Random::get(0, 51)]);
        diler_summary = getSum(vec1);
        if (diler_summary > 21)
            return true;
        else if (diler_summary == 21)
        {
            if (summary == 21)
                cout << "Oops,Draw\n";
            return false;
        }
    }
    if (diler_summary == summary)
    {
        cout << "Oops,Draw\n";
        return false;
    }
    return (diler_summary < summary);

}

int main()
{
    bool finish = { false };
    while (!finish)
    {
        bool flag = { false };
        cout<<"Do you wanna play alone or with Diler? 1 / 2\n";
        {
            char c{};
            bool bollka = { false };
            while (!bollka)
            {
                cin >> c;
                switch (c)
                {
                case '1':
                    bollka = true;
                    break;
                case '2':
                    flag = true;
                    bollka = true;
                    break;
                default: cout << "Error\n"; break;
                }
            }

        }
        bool game{};
        if(flag)
        game= duo_BlackJack();
        else 
            game = solo_BlackJack();

        if (game)
            cout << "You won!!!\n";
        else cout << "You loose :(\n";

        cout << "\nWould u like to play again? Y/n \n";
        bool bollka = { false };
        while (!bollka)
        {
            char c;
            cin >> c;
            switch (c)
            {
            case 'n':
            case 'N':
                finish = true;
                bollka = true;
                break;
            case 'y':
            case 'Y':
                bollka = true; break;
            default: "Error\n"; break;
            }
        }
    }
    cout << "\nThanks for playing! :)\n";
    system("pause");
	return 0;
}