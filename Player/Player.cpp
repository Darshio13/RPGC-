//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>
#include <cmath>

using namespace std;

Player::Player(char _name[], int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack,
                                                                                             _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (isDefending) {
        trueDamage -= int(round((double) defense * .20));
    }
    health -= trueDamage;

    std::cout << name << " took " << trueDamage << " damage!" << endl;


    if (health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

void Player::levelUp() {

    level++;
    health = health + 20;
    attack = attack +5;
    speed = speed + 3;
    defense = defense +10;

    cout<<"Subiste al nivel " << level <<endl ;
    cout << "Tu salud mejora en 20 puntos "<<endl;
    cout << "Tu ataque mejora en 5 puntos "<<endl;
    cout << "Tu velocidad mejora en 3 puntos "<<endl;
    cout << "Tu defensa mejora en 10 puntos "<<endl;




}

void Player::gainExperience(int exp) {
    experience += exp;
    cout << "Ganas " << exp<<" puntos de experiencia"<<endl;

    if (experience >= 100) {
        int veces = (experience/100)%10;

        if (veces > 1)
        {
            experience = experience-(100*veces);


            for (int i = 0; i <= veces; ++i) {

                levelUp();
            }
            cout << "Tu experiencia actual es de " << experience<<endl;

        }
        else
        {
            experience = experience-100;
            cout << "Tu experiencia actual es de " << experience<<endl;

            levelUp();
        }




    }

}

Character *Player::selectTarget(vector<Enemy *> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy *> enemies) {
    bool error;
    int action = 0;
    Action currentAction;
    do {
        error = false;
        cout << "Select an action: " << endl
             << "1. Attack" << endl
             << "2. Defend" << endl;
        cin >> action;
        Character *target = nullptr;
        defend(false);
        switch (action) {
            case 1:
                target = selectTarget(enemies);
                currentAction.target = target;
                currentAction.action = [this, target]() {
                    doAttack(target);
                };
                currentAction.speed = getSpeed();
                break;
            case 2:
                currentAction.target = this;
                currentAction.action = [this]() {
                    defend(true);
                };
                currentAction.speed = 999999;
                break;

            default:
                cout << "Invalid action" << endl;
                error = true;
                break;
        }
    } while (error);
    return currentAction;
}