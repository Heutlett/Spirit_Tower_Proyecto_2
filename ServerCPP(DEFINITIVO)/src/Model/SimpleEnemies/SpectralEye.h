//
// Created by carlo on 6/30/2020.
//

#ifndef SERVER_SPECTRALEYE_H
#define SERVER_SPECTRALEYE_H


#include "SimpleEnemy.h"

class SpectralEye: public SimpleEnemy {

private:
    //ATTRIBUTES
    int visionRange = 0;


    //METHODS
    vector<int> *getStartPos();
    void setEyeEdge();
    void setWhereToTeleport();
    void callSpectres();

public:

    static Position *tpSpot;
    static string lastSeen;
    SpectralEye(const string &pId, const string &pType, int pVisionRange, Position *pPosition);

    //ATTRIBUTES
    static vector<SpectralEye*> *listOfSpectralEyes;

    //METHODS
    void setEyeGraph();
    void checkVisionRange();
    static void sendSignalToPersuit(Spectre* pSpectre);
    static void clear();

    //SETTER & GETTERS
    static Position * getWhereToTeleport();
};

#endif //SERVER_SPECTRALEYE_H
