//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SPECTRE_H
#define SERVER_SPECTRE_H

#include "../Board/Entity.h"
#include <string>
#include <vector>
#include <thread>
#include <unistd.h>
#include "../Board/Board.h"


using namespace std;

enum SpectreType{

    GRAY,
    BLUE,
    RED

};

class Spectre: Entity {

private:

    vector<Position*>* patrolRoute;
    queue<Position*>* queuePatrolRoute;
    vector<Position*>* auxVec = new vector<Position*>();

    //string direction;
    int routeVelocity;
    int persuitVelocity;
    int visionRange;

    int paralizeTime = 5;

    bool teleportTo = false;
    bool teleportFrom = false;
    Position* teleportToPos = new Position();
    Position* teleportFromPos = new Position();

    bool paralize = false;

    SpectreType spectreType;
    bool useBreadcrumbing = false;

public:

    bool backtracking;
    static bool isOnPersuit;
    //Constructor
    Spectre(string pId, string pType, vector<Position*>* pPatrolRoute, int pRouteVelocity,
            int pPersuitVelocity, int pVisionRange, Position *pPosition, SpectreType pSpectreType);

    static vector<Spectre*> *listOfSpectres;

    //Methods
    void moveNext();
    void startMovement();
    void updateDirection(Position * pPosition);
    void checkVisionRange();
    void moveRoutePatrol();
    void moveToPos(Position * pPosition);
    void movePersuit();
    void moveBreadcrumbing();
    void moveAStar();
    void moveBacktracking();
    void teleportToSpectre();
    void resetPatrolQueue();

    void persuitPlayer();
    void sendSignalToPersuit();
    static void sendSignalToStopPersuit();
    void returnToPatrol();
    void attackedFromBack();
    void attackedFromFront();
    void paralizeCuzMouse();
    void calculateAStar();

    void setNewDirection(string pDirection);


    //Setters and getters
    void setPatrolRoute(vector<Position*>* pPatrolRoute);
    vector<Position*>* getPatrolRoute();
    //void setDirection(string pDirection);
    //string getDirection();
    void setRouteVelocity(double pRouteVelocity);
    double getRouteVelocity();
    void setPersuitVelocity(double pPersuitVelocity);
    double getPersuitVelocity();
    void setVisionRange(int pVisionRange);
    int getVisionRange();
    Spectre* getSpectreByID(string pId);
    void setIsOnPersuit(bool pIsOnPersuit);
    void setTeleportTo(bool pTeleport);
    bool getTeleportTo() const;
    void setTeleportFrom(bool pTeleport);
    bool getTeleportFrom() const;
    Position *getTeleportToPos() const;
    void setTeleportToPos(Position *pTeleportPos);
    Position *getTeleportFromPos() const;
    void setTeleportFromPos(Position *pTeleportPos);

    deque<Position*> * getDequeBackTracking();

    //toString, prints, logs
    string toString();
    void printSpectre();
    string getSpectreId();
    string getSpectreType();
    static void clear();
    static void printAllSpectres();

    void setPauseEntity(bool pPause);

    deque<Position*>* queueBackTracking = new deque<Position*>();
    queue<Position*>* queueAStar;
};


#endif //SERVER_SPECTRE_H
