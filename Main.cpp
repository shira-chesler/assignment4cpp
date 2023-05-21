#include <iostream>
#include <stdexcept>
#include <random>
#include <chrono>
#include "sources/Team.hpp"
#include "sources/SmartTeam.hpp"
#include "sources/Team2.hpp"

using namespace std;

using namespace ariel;

double random_float(double min = -100, double max = 100) {
    std::default_random_engine generator(
            static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> distribution(min, max);

    return distribution(generator);
}

auto create_yninja = []() {
    double x = random_float(), y = random_float();
    return new YoungNinja{"YoungNinja", Point{x, y}};
};

auto create_tninja = []() {
    double x = random_float(), y = random_float();
    return new TrainedNinja{"TrainedNinja", Point{x, y}};
};

auto create_oninja = []() {
    double x = random_float(), y = random_float();
    return new OldNinja{"OldNinja", Point{x, y}};
};

auto create_cowboy = []() {
    double x = random_float(), y = random_float();
    return new Cowboy{"Cowboy", Point{x, y}};
};

int main() {
    // Creating teams
    Team team1(create_cowboy());
    Team2 team2(create_oninja());
    SmartTeam smartTeam1(create_tninja());
    auto deadNinja = new YoungNinja("dead", {0, 0});
    auto oldNin = new OldNinja("ninja", {0, 0});
    while (deadNinja->isAlive()) {
        oldNin->slash(deadNinja);
    }

    try {
        team1.add(nullptr);
    } catch (std::runtime_error &error) {
        cout << error.what() << endl;
    }
    try {
        Team team(nullptr);
    } catch (std::runtime_error &error) {
        cout << error.what() << endl;
    }
    try {
        team1.add(deadNinja);
    } catch (std::runtime_error &error) {
        cout << error.what() << endl;
    }
    try {
        deadNinja->slash(oldNin);
    } catch (std::runtime_error &error) {
        cout << error.what() << endl;
    }
//     Adding characters to the teams
    for (int i = 0; i < 9; i++) {
        team1.add(create_yninja());
        team2.add(create_tninja());
        smartTeam1.add(create_cowboy());
    }

    // Printing initial state of the teams
    std::cout << "Initial state of the teams:\n";
    team1.print();
    team2.print();
    smartTeam1.print();

    // Battle between Team and SmartTeam
    while (team1.stillAlive() > 0 && smartTeam1.stillAlive() > 0) {
        team1.attack(&smartTeam1);
        smartTeam1.attack(&team1);
    }

    // Print the winning team
    if (team1.stillAlive() > 0) {
        std::cout << "\nWinner is team" << std::endl;
    } else {
        std::cout << "\nWinner is smartTeam" << std::endl;
    }

    // Battle between Team2 and SmartTeam
    while (team2.stillAlive() > 0 && smartTeam1.stillAlive() > 0) {
        team2.attack(&smartTeam1);
        smartTeam1.attack(&team2);
    }

    // Print the winning team
    if (team2.stillAlive() > 0) {
        std::cout << "\nWinner is team2" << std::endl;
    } else {
        std::cout << "\nWinner is smartTeam" << std::endl;
    }

    return 0;
}