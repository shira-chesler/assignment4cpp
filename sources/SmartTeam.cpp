#include "SmartTeam.hpp"
#include <map>

using namespace ariel;
const int youngSpeed = 14;
const int trainedSpeed = 12;
const int oldSpeed = 8;


// This function calculates and returns a count for a given enemy.
// The count is calculated based on several factors:
// 1. The enemy's health - lower health enemies have a higher count.
// 2. The type of the character making the attack - different types of characters (Cowboy or different types of Ninjas) adjust the count differently.
// 3. The number of bullets left (if the character is a Cowboy) - the more bullets left, the higher the count.
// 4. The proximity of other enemies - the more enemies are near the target enemy, the higher the count.
double SmartTeam::enemycount(Character *enemy, Team *enemyTeam, Character *attackingCharacter) {
    double count = 0;

    double healthcount = 1.0 / enemy->getHp();
    count += healthcount * healthcount;

    if (attackingCharacter->getType() == "C") {
        auto *cowboy = dynamic_cast<Cowboy *>(attackingCharacter);
        if (cowboy->hasboolets()) {
            count += 5 * cowboy->getNumBullets();
        }
        return count;
    } 

    // only ninjas are left
    int speed = 0;
    if (attackingCharacter->getType() == "YN") {
        speed = youngSpeed;
        count += NinjaAttackcountAdd(attackingCharacter, enemy);
    } 
    else if (attackingCharacter->getType() == "TN") {
        speed = trainedSpeed;
        count += NinjaAttackcountAdd(attackingCharacter, enemy);
    } 
    else { 
        speed = oldSpeed;
        count += NinjaAttackcountAdd(attackingCharacter, enemy);
    }

    int nearbyEnemies = 0;
    for(size_t i; i<10; i++){ 
        Character *other = enemyTeam->getTeamAt(i);
        if (other != enemy && other != nullptr && other->isAlive()) {
            double distance = enemy->distance(other);
            if (distance <= speed) {
                nearbyEnemies++;
            }
        }
    }
    count += nearbyEnemies;
    return count;
}

//help function to check if to add to the count of the enemy
int SmartTeam::NinjaAttackcountAdd(Character *attackingCharacter, Character *enemy){
    if (attackingCharacter->distance(enemy) <= 1) {
            return 40;
    }
    return 0;
}


// This function makes the SmartTeam attack the enemy team.
// It does this by iterating over each character in the SmartTeam, and for each character:
// 1. If the character is not alive, it skips the character.
// 2. Otherwise, it calculates a count for each enemy in the enemy team.
// 3. It targets the enemy with the highest count.
// 4. If the character is a Cowboy and has bullets, it makes the Cowboy shoot the targeted enemy.
// 5. If the character is a Ninja, it checks the distance to the targeted enemy.
// 6. If the distance is less than or equal to 1, it makes the Ninja slash the targeted enemy.
// 7. Otherwise, it makes the Ninja move towards the targeted enemy.
// 8. If there are no enemies left alive, it breaks the loop.
void SmartTeam::attack(Team *enemyTeam) {
    //checks before an attack
    check_change_leader();
    if(!enemyTeam) throw std::invalid_argument("a nullptr has been given as a pointer");
    if(enemyTeam->stillAlive()==0) throw std::runtime_error("cannot attack a dead team");
    if (stillAlive()==0) return;
    if(this == enemyTeam) throw std::runtime_error("group cannot attck itself");
    if(!this->getStartedGame()){
        setStrtedGame(true);
        enemyTeam->setStrtedGame(true);
    }

    //attacking
    for (size_t j; j<10; j++){
        Character *attackingCharacter = this->getTeamAt(j);
        if (attackingCharacter == nullptr || !attackingCharacter->isAlive()) {
            continue;
        }

        //scoring the characters
        std::array<double, 10> counts{0};
        for (size_t i; i<10; i++){
            Character* enemy = enemyTeam->getTeamAt(i);
            if (enemy == nullptr || !enemy->isAlive()) {
                continue;
            }
            double count = this->enemycount(enemy, enemyTeam, attackingCharacter);
            counts.at(i) = count;
        }

        //choosing the best character according to the counts
        Character *bestEnemy = nullptr;
        double bestcount = -1;
        for (size_t i=0; i<10; i++){
            double count = counts.at(i);
            if (count > bestcount) {
                bestcount = count;
                bestEnemy = enemyTeam->getTeamAt(i);
            }
        }

        // attcaking the enemy according to rules if not null
        if (bestEnemy != nullptr) {
            if (attackingCharacter->getType() == "C") {
                dynamic_cast<Cowboy *>(attackingCharacter)->shoot(bestEnemy);
            } 
            else{ 
                if (attackingCharacter->distance(bestEnemy) <= 1) {
                    dynamic_cast<Ninja *>(attackingCharacter)->slash(bestEnemy);
                } 
                else {
                    dynamic_cast<Ninja *>(attackingCharacter)->move(bestEnemy);
                }
            }
        }
        
        //end of attack - the enemy team is dead
        if (enemyTeam->stillAlive() == 0) {
            break;
        }
    }
}

// smartTeam constructor
SmartTeam::SmartTeam(Character *leader) : Team2(leader) {
}


