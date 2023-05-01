#include <iostream>
#include <unordered_map>

enum RPS : unsigned char {
    UNDEFINED = 0b00000000,
    ROCK =      0b01000001,
    PAPER =     0b00010010,
    SCISSORS =  0b00100100
};

std::unordered_map<char, RPS> inMap = {
        {'r', RPS::ROCK},       {'R', RPS::ROCK},
        {'p', RPS::PAPER},      {'P', RPS::PAPER},
        {'s', RPS::SCISSORS},   {'S', RPS::SCISSORS}
};

std::unordered_map<RPS, const char*> outMap = {
        {RPS::ROCK,     "Rock"},
        {RPS::PAPER,    "Paper"},
        {RPS::SCISSORS, "Scissors"}
};

const RPS randMap[] = {RPS::ROCK, RPS::PAPER, RPS::SCISSORS};

int main() {
    RPS player;
    RPS rand;

    char in;
    std::srand(time(NULL));

    while (true) {
        std::cout << "Rock Paper Scissors \n  Shoot! [R/P/S] " << std::flush;
        std::cin >> in;

        player = inMap[in];
        while (player == RPS::UNDEFINED) {
            std::cout << "Invalid input!" << std::endl;
            std::cin >> in;
            player = inMap[in];
        }
        rand = randMap[std::rand() % 3];

        std::cout << '\n' << "I choose " << outMap[rand] << std::endl;

        if (player == rand) std::cout << "Draw! ";
        else if ((player >> 4) & (rand & 0b00001111)) std::cout << "You win! ";
        else std::cout << "I win! ";

        std::cout << "Again? [Y/N]" << std::endl;
        std::cin >> in;

        std::cout << "\n";
        if (in == 'y' or in == 'Y') continue;

        break;
    }
}