//
// Created by carlo on 6/29/2020.
//


#include "GameManager.h"
#include "../Model/Objects/Treasure.h"
#include "../Model/Objects/Jarron.h"
#include "../Model/Board/Jugador.h"
#include "../Model/SimpleEnemies/SpectralEye.h"
#include "../Model/SimpleEnemies/Chuchu.h"
#include "../Model/SimpleEnemies/Mouse.h"

void GameManager::initSpectresMovement() {

    for(int i = 0; i < Spectre::listOfSpectres->size(); i++){

        Spectre::listOfSpectres->at(i)->startMovement();

    }

}

void GameManager::loadGame(int pLevel) {

    cout << "Iniciando carga del nivel: " << pLevel << endl;
    ifstream file("..\\src\\resources\\maps\\level_0" + to_string(pLevel) + "\\level0" + to_string(pLevel) +".json");
    ostringstream tmp;
    tmp<<file.rdbuf();
    string JSON = tmp.str();
    loadGameFromJSON(JSON);
    board.printBoardCellType();
    board.printBoardEntity();
    generateEntityLastStatusJSON();

}

/**
 * Inicia el juego cargando los datos que se encuentran en el json del nivel
 * @param pLevel
 */
void GameManager::startGame() {
    initSpectresMovement();
    thread(&GameManager::updateGame, this).detach();
}

void GameManager::updateGame() {
    while(1){
        sleep(0.5);
        generateEntityLastStatusJSON();
        //board.printBoardEntity();
    }
}

void GameManager::parseJugadorJSON(json pJSON) {

    cout << "Cargando los datos del jugador desde el archivo JSON..." << endl;

    string id = pJSON["jugador"]["id"];
    string type = pJSON["jugador"]["type"];
    Position *position = new Position(pJSON["jugador"]["position"][0], pJSON["jugador"]["position"][1]);
    Jugador *jugador = new Jugador(id, type, position, 1);

}

void GameManager::createMatrizJsonString(json pJSON) {

    matrizJSONString = "{\"matriz\":";
    matrizJSONString += pJSON["matriz"].dump();
    matrizJSONString += "}";

}

/**
 * Parsea la matriz desde el archivo json del mapa
 * @param pJSON
 */
void GameManager::parseMatrizJSON(json pJSON) {

    createMatrizJsonString(pJSON);

    cout << "Cargando la matriz del archivo JSON..." << endl;

    for(int i = 0; i < pJSON["matriz"].size(); i++){

        for(int e = 0; e < pJSON["matriz"].at(i).size(); e++){

            string id = "C" + to_string(i) + "," + to_string(e);
            //cout << id << endl;
            CellType cellType;

            if(pJSON["matriz"].at(i).at(e) == 0){
                cellType = NORMAL;
            }else{
                if(pJSON["matriz"].at(i).at(e) == 1){
                    cellType = OBSTACLE;
                }else{
                    if(pJSON["matriz"].at(i).at(e) == 2){
                        cellType = SAFEZONE;
                    }
                }
            }

            Cell* c = new Cell(i, e, id, cellType);
            board.matriz[i][e] = c;
        }
    }

}
/**
 * Parsea los espectros que se encuentran en el json a la memoria
 * @param pJSON
 */
void GameManager::parseSpectresJSON(json pJSON) {

    cout << "Cargando los espectros del archivo JSON..." << endl;

    for(int i = 0; i < pJSON["spectres"].size(); i++){

        string id = pJSON["spectres"].at(i)["id"];
        string type = pJSON["spectres"].at(i)["type"];
        Position *position = new Position(pJSON["spectres"].at(i)["position"][0],pJSON["spectres"].at(i)["position"][1]);

        string direction = pJSON["spectres"].at(i)["direction"];
        double routeVelocity = pJSON["spectres"].at(i)["routeVelocity"];
        double persuitVelocity = pJSON["spectres"].at(i)["persuitVelocity"];
        int visionRange = pJSON["spectres"].at(i)["visionRange"];
        vector<Position>* patrolRoute = new vector<Position>();
        SpectreType spectreType;

        if(type.compare("spectre_gray") == 0){
            spectreType = GRAY;
        }else{
            if(type.compare("spectre_blue") == 0){
                spectreType = BLUE;
            } else{
                if(type.compare("spectre_red") == 0){
                    spectreType = RED;
                }
            }
        }

        for(int e = 0; e < pJSON["spectres"].at(i)["patrolRoute"].size(); e++){
            Position *tmpPosition = new Position(pJSON["spectres"].at(i)["patrolRoute"].at(e)[0], pJSON["spectres"].at(i)["patrolRoute"].at(e)[1]);
            patrolRoute->push_back(*tmpPosition);
        }
        Spectre *spectre = new Spectre(id, type, patrolRoute, direction, routeVelocity, persuitVelocity, visionRange, position, spectreType);
    }

}
/**
 * Parsea los objetos que se encuentran el archivo json del mapa
 * @param pJSON
 */
void GameManager::parseObjectsJSON(json pJSON) {
    for(int i = 0; i < pJSON["objects"].size(); i++){

        string id = pJSON["objects"].at(i)["id"];
        string type = pJSON["objects"].at(i)["type"];
        int scorePoints = pJSON["objects"].at(i)["scorePoints"];
        Position *position = new Position(pJSON["objects"].at(i)["position"][0], pJSON["objects"].at(i)["position"][1]);
        if(type.compare("treasure") == 0){

            Treasure *treasure = new Treasure(id, type, scorePoints, position);
            //board.getListOfObjects()->push_back(treasure);

        }else{

            if(type.compare("jarron") == 0){

                int heartQuantity = pJSON["objects"].at(i)["heartQuantity"];
                Jarron *jarron = new Jarron(id, type, scorePoints, heartQuantity, position);

            }

        }
    }
}

void GameManager::parseSimpleEnemiesJSON(json pJSON) {
    for(int i = 0; i < pJSON["simpleEnemies"].size(); i++){

        string id = pJSON["simpleEnemies"].at(i)["id"];
        string type = pJSON["simpleEnemies"].at(i)["type"];
        Position *position = new Position(pJSON["simpleEnemies"].at(i)["position"][0], pJSON["simpleEnemies"].at(i)["position"][1]);
        if(type.compare("spectralEye") == 0){

            int visionRange = pJSON["simpleEnemies"].at(i)["visionRange"];
            SpectralEye *spectralEye = new SpectralEye(id, type, visionRange, position);

        }else if(type.compare("chuchu") == 0){
                Chuchu *chuchu = new Chuchu(id, type, position);
        }else if(type.compare("mouse") == 0){
            Mouse *mouse = new Mouse(id, type, position);
        }
    }
}


/**
 * Carga los datos del json al juego
 * @param pJSON
 */
void GameManager::loadGameFromJSON(string pJSON) {

    cout << "Cargando datos desde el archivo JSON..." << endl;
    json jsonObj;
    stringstream(pJSON) >> jsonObj;

    parseMatrizJSON(jsonObj);
    parseJugadorJSON(jsonObj);
    parseSpectresJSON(jsonObj);
    parseObjectsJSON(jsonObj);
    parseSimpleEnemiesJSON(jsonObj);

    cout << "Carga completa!" << endl;
}

void GameManager::generateEntityLastStatusJSON() {

    json j;
    j["listOfEntitys"] = {};

    //cout << "SEPARATOR" << endl << endl;

    for(int i = 1; i < Entity::listOfEntitys->size(); i++){

        json j2;
        Position * position = new Position(Entity::listOfEntitys->at(i).getPosition()->getRow(), Entity::listOfEntitys->at(i).getPosition()->getColumn());

        j2["id"] =  Entity::listOfEntitys->at(i).getId();
        j2["type"] =  Entity::listOfEntitys->at(i).getType();
        j2["position"] = {};
        j2["position"][0] = position->getRow();
        j2["position"][1] = position->getColumn();
        j["listOfEntitys"][i-1] = j2;

    }
    entitysJSONString = j.dump();
}



string GameManager::getMatrizJsonString() {
    return matrizJSONString;
}


/* Null, because instance will be initialized on demand. */
GameManager* GameManager::instance = 0;

GameManager* GameManager::getInstance()
{
    if (instance == 0)
    {
        instance = new GameManager();
    }

    return instance;
}

GameManager::GameManager()
{

}

Board GameManager::getBoard() {
    return board;
}

int GameManager::getScore() {
    return score;
}

int GameManager::getLifes() {
    return lifes;
}

string GameManager::getEntitysJsonString() {
    return entitysJSONString;
}








