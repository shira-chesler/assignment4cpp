
#include "sources/Character.hpp"
#include "sources/OldNinja.hpp"
#include "sources/YoungNinja.hpp"
#include "sources/TrainedNinja.hpp"
#include "sources/Cowboy.hpp"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include <random>
#include <chrono>
#include <iostream>

using namespace ariel;
using namespace std;
//<--------------------Helper Functions-------------------->
//https://www.geeksforgeeks.org/generate-a-random-float-number-in-cpp/
double random_float(double min = -100, double max = 100) {
    std::default_random_engine generator(static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

auto create_yninja = [](double x = random_float(), double y = random_float()) {
    return new YoungNinja{"Bob", Point{x, y}};
};

auto create_tninja = [](double x = random_float(), double y = random_float()) {
    return new TrainedNinja{"Bob", Point{x, y}};
};

auto create_oninja = [](double x = random_float(), double y = random_float()) {
    return new OldNinja{"Bob", Point{x, y}};
};

auto create_cowboy = [](double x = random_float(), double y = random_float()) {
    return new Cowboy{"Bob", Point{x, y}};
};

auto random_char(double x = random_float(), double y = random_float()) -> Character * {
    int flag = static_cast<int>(random_float()) % 4;

    if (flag == 0) return create_cowboy(x, y);

    if (flag == 1) return create_yninja(x, y);

    if (flag == 2) return create_tninja(x, y);

    return create_oninja(x, y);
}

auto simulate_battle = [](Team &team, Team &team2) {
    int i = 0;
    while (team.stillAlive() && team2.stillAlive()) {
        if (i % 2 == 0) {
            team.attack(&team2);
        } else {
            team2.attack(&team);
        }
        i++;
    }
};
//<-------------------------------------------------->

const int MAX_TEAM = 10;

auto multi_attack = [](int n, Team &attacker, Team &defender) {
        for (int i = 0; i < n; i++) {
            if (defender.stillAlive()) {
                attacker.attack(&defender);
            }
        }
};

int main(){
        printf("cowboy: %lu\n", sizeof(create_cowboy()));
        printf("yn: %lu\n", sizeof(create_yninja()));
        printf("on: %lu\n", sizeof(create_oninja()));
        printf("tn: %lu\n", sizeof(create_tninja()));
}