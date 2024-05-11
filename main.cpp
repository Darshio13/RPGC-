#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include <fstream>

bool fileExists(const string &filename = "data.dat") {
    std::ifstream file(filename);
    return file.good();
}

Player *readPlayerFromFile() {
    char buffer[Player::BUFFER_SIZE];
    ifstream readStream;
    readStream.open("data.dat", ios::binary);
    readStream.read(buffer, Player::BUFFER_SIZE);
    readStream.close();
    return Player::unserialize(buffer);
}

void writeToFile(char buffer[], unsigned int bufferSize) {
    ofstream writeStream;
    writeStream.open("data.dat", ios::binary);
    //Escribe en el archivo desde la direccion donde apunta buffer hasta donde mide bufferSize
    writeStream.write(buffer, bufferSize);
    writeStream.close();
}


int main() {
    string resp = "";
    do {
        Player *player;
        if (fileExists()) {
            cout << "Partida detectada\n Desea Cargarla? S=Si | N= No" << endl;
            cin >> resp;
            if (resp == "S" || resp == "s") {
                player = readPlayerFromFile();
                cout << "Partida cargada correctamente\n" << player->toString() << endl;
            } else {
                player = new Player("Cloud Strife", 100, 50, 4, 3);
            }
        } else {
            player = new Player("Cloud Strife", 100, 50, 4, 3);
        }

        Enemy *enemy = new Enemy("Sephirtoh", 50, 6, 2, 5, 10);
        Enemy *enemy2 = new Enemy("Jenova", 50, 6, 2, 5, 10);



        vector<Character *> participants;

        participants.push_back(player);
        participants.push_back(enemy);
        participants.push_back(enemy2);

        Combat *combat = new Combat(participants);
        combat->doCombat();
        if (player->getHealth() > 0) {
            cout
                    << "Deseas salvar la partida? S = Si / N = No \n Se perderan los datos si no guardan"
                    << endl;
            cin >> resp;
            if (resp == "S" || resp == "s") {
                char buffer[Player::BUFFER_SIZE];
                player->serialize(buffer);
                writeToFile(buffer, Player::BUFFER_SIZE);
            }
        }
        delete player;
        delete enemy;
        delete combat;
        cout << "Desea continuar?  S = Si / N = No " << endl;
        cin >> resp;
    } while (resp == "S" || resp == "s");
    return 0;
}
