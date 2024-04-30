//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include <iostream>
#include <cmath>

using namespace std;
using namespace combat_utils;

Enemy::Enemy(char _name[], int _health, int _attack, int _defense, int _speed, int _experience) : Character(_name,
                                                                                                            _health,
                                                                                                            _attack,
                                                                                                            _defense,
                                                                                                            _speed,
                                                                                                            false) {
    experience = _experience;
    totalHealth = health;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

int Enemy::getTotalHealth() const {
    return totalHealth;
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (isDefending) {
        trueDamage -= int(ceil((double) defense * .20));
    }
    health -= trueDamage;

    std::cout << name << " took " << trueDamage << " damage!" << endl;


    if (health <= 0) {
        cout << name << " has been defeated!" << endl;


    }
}

int Enemy::getExperience() {
    if (health<=0) {
        experience = 75;
    }
    return experience;
}

Character *Enemy::selectTarget(vector<Player *> possibleTargets) {
    //target with less health
    int lessHealth = 9999999;
    Character *target = nullptr;
    for (auto character: possibleTargets) {
        if (character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}

Action Enemy::takeAction(vector<Player *> partyMembers) {
    Action currentAction;
    int selectedAction;
    if ((((double) getHealth()) / ((double) getTotalHealth())) <= 0.15) {
        selectedAction = selectActionForIA();
    } else {
        selectedAction = 1;
    }
    Character *target;
    switch (selectedAction) {
        case 1:
            currentAction.speed = getSpeed();
            target = selectTarget(partyMembers);
            currentAction.target = target;
            currentAction.action = [this, target]() {
                doAttack(target);
            };
            break;
        case 2:
            currentAction.speed = 999999;
            currentAction.target = this;
            currentAction.action = [this]() {
                defend(true);
            };
            break;
    }


    return currentAction;
}

int Enemy::selectActionForIA() {
    if (getRandBetweenRange(0, 100) > 40) {
        return 1;
    } else {
        return 2;
    }
}

int Enemy::getRandBetweenRange(int lowerBound, int upperBound) {
    srand(time(nullptr)); // Use current time as seed for random generator0
    return (rand() % (upperBound - lowerBound + 1)) + lowerBound;
}