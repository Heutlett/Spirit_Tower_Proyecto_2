//
// Created by carlo on 6/30/2020.
//

#include "Mouse.h"

vector<Mouse*> *Mouse::listOfMice = new vector<Mouse*>();

Mouse::Mouse(const string &pId, const string &pType, Position* pPosition)
: SimpleEnemy(pId, pType, pPosition)
{
    if(listOfMice != nullptr){
        listOfMice->push_back(this);
    }
}

/* ===============================  GETTERS  ========================================
 * =============================== & SETTERS ======================================== */



/* =============================== FUNCTION =======================================
 * ===============================          ======================================= */


/**
 * Start thread for the mouse movement.
 */
void Mouse::startMovement() {
    thread(&Mouse::moveRandomly, this).detach();
}


/**
 * Get a random place to where to move.
 */
void Mouse::moveRandomly() {

    while(!getEntityPause()){

        sleep(1);

        int mov;
        bool searchAvailable = true;
        Position * nextPos;

        while(searchAvailable){

            mov = rand()%(4-1+1)+1;

            switch(mov){
                case 1: //norte
                    if(Board::matriz[getEntityPosition()->getRow()-1][getEntityPosition()->getColumn()] != nullptr && Board::matriz[getEntityPosition()->getRow()-1][getEntityPosition()->getColumn()]->getCellType() == NORMAL && Board::matriz[getEntityPosition()->getRow()-1][getEntityPosition()->getColumn()]->getEntity()==""){
                        searchAvailable = false;
                        nextPos = new Position(getEntityPosition()->getRow()-1,getEntityPosition()->getColumn());
                        setEntityDirection("north");

                    }
                    break;
                case 2: //sur
                    if(Board::matriz[getEntityPosition()->getRow()-1][getEntityPosition()->getColumn()] != nullptr && Board::matriz[getEntityPosition()->getRow()+1][getEntityPosition()->getColumn()]->getCellType() == NORMAL && Board::matriz[getEntityPosition()->getRow()+1][getEntityPosition()->getColumn()]->getEntity()==""){
                        searchAvailable = false;
                        nextPos = new Position(getEntityPosition()->getRow()+1,getEntityPosition()->getColumn());
                        setEntityDirection("south");
                    }
                    break;
                case 3: //este
                    if(Board::matriz[getEntityPosition()->getRow()-1][getEntityPosition()->getColumn()] != nullptr && Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()+1]->getCellType() == NORMAL && Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()+1]->getEntity()==""){
                        searchAvailable = false;
                        nextPos = new Position(getEntityPosition()->getRow(),getEntityPosition()->getColumn()+1);
                        setEntityDirection("east");
                    }
                    break;
                case 4: //oeste
                    if(Board::matriz[getEntityPosition()->getRow()-1][getEntityPosition()->getColumn()] != nullptr && Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()-1]->getCellType() == NORMAL && Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()-1]->getEntity()==""){
                        searchAvailable = false;
                        nextPos = new Position(getEntityPosition()->getRow(),getEntityPosition()->getColumn()-1);
                        setEntityDirection("west");
                    }
                    break;
            }

        }
        if(Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()] != nullptr){
            Board::matriz[getEntityPosition()->getRow()][getEntityPosition()->getColumn()]->setEntity("");
            setEntityPosition(nextPos);
            Board::matriz[nextPos->getRow()][nextPos->getColumn()]->setEntity(getEntityId());
        }
    }
}

void Mouse::clear() {
    if(listOfMice != nullptr){
        for(int i = 0; i < listOfMice->size();i++){
            listOfMice->at(i)->setEntityPause(true);
        }
        listOfMice->clear();
    }

    //listOfMice = new vector<Mouse*>();
}

