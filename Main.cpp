#include <iostream>
#include <stdexcept>
#include <random>
#include <unistd.h>
#include <chrono>
#include "sources/Team.hpp"
#include "sources/SmartTeam.hpp"
#include "sources/Team2.hpp"

using std::cout;
using std::endl;
using std::runtime_error;


namespace ariel {

double gen_random_float(double lower = -100, double upper = 100) {
    std::default_random_engine engine(
        static_cast<unsigned long>(std::chrono::system_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution<double> dist(lower, upper);
    return dist(engine);
}

template<typename T, typename... Args>
T* create_character(Args... args) {
    double x = gen_random_float(), y = gen_random_float();
    return new T(args..., Point{x, y});
}

void fight(Team& team1, SmartTeam& smartTeam) {
    while (team1.stillAlive() > 0 && smartTeam.stillAlive() > 0) {
        team1.attack(&smartTeam);
        smartTeam.attack(&team1);
    }
    if (team1.stillAlive() > 0) {
        cout << "\nWinner is team1" << endl;
    } else {
        cout << "\nWinner is smartTeam" << endl;
    }
}

Character* create_random_character() {
    usleep(25);
    int characterType = rand() % 4;
    switch (characterType) {
        case 0:
            return create_character<YoungNinja>("YoungNinja");
        case 1:
            return create_character<TrainedNinja>("TrainedNinja");
        case 2:
            return create_character<OldNinja>("OldNinja");
        case 3:
            return create_character<Cowboy>("Cowboy");
        default:
            return nullptr;  // Should never happen
    }
}

void fill_teams(Team& team1, Team2& team2, SmartTeam& smartTeam) {
    for (int i = 0; i < 9; i++) {
        team1.add(create_random_character());
        team2.add(create_random_character());
        smartTeam.add(create_random_character());
    }
}

void print_teams(Team& team1, Team2& team2, SmartTeam& smartTeam) {
    cout << "Initial state of the teams:\n";
    cout << "team1:\n";
    team1.print();
    cout << "team2:\n";
    team2.print();
    cout << "smartTeam:\n";
    smartTeam.print();
}

}

using namespace ariel;

int main() {
    Team team1(create_character<Cowboy>("Cowboy"));
    Team2 team2(create_character<OldNinja>("OldNinja"));
    SmartTeam smartTeam(create_character<TrainedNinja>("TrainedNinja"));

    auto* deadNinja = create_character<YoungNinja>("dead ninja");
    auto* Woody = create_character<Cowboy>("woody");
    while (deadNinja->isAlive()) {
        Woody->shoot(deadNinja);
    }

    Team team3(create_character<Cowboy>("cowboy dummy"));
    Team2 team4(create_character<YoungNinja>("young ninja dummy"));
    team3.attack(&team4);
    std::cout << "-----ERRORS CATCHING-----" << std::endl;
    try{
        team3.add(create_character<OldNinja>("old ninja dummy"));
    } catch (std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }
    try{
        team4.add(create_character<TrainedNinja>("trained ninja dummy"));
    } catch (std::runtime_error &e){
        std::cout << e.what() << std::endl;
    }
    try {
        team1.add(nullptr);
    } catch (runtime_error& error) {
        cout << error.what() << endl;
    }
    try {
        Team team(nullptr);
    } catch (runtime_error& error) {
        cout << error.what() << endl;
    }
    try {
        team1.add(deadNinja);
    } catch (runtime_error& error) {
        cout << error.what() << endl;
    }
    try {
        deadNinja->slash(Woody);
    } catch (runtime_error& error) {
        cout << error.what() << endl;
    }

    fill_teams(team1, team2, smartTeam);
    print_teams(team1, team2, smartTeam);

    fight(team1, smartTeam);

    Team team3(create_character<Cowboy>("Cowboy"));
    Team2 team4(create_character<OldNinja>("OldNinja"));
    SmartTeam smartTeam2(create_character<TrainedNinja>("TrainedNinja"));
    fill_teams(team3, team4, smartTeam2);
    fight(team4, smartTeam2);

    return 0;
}