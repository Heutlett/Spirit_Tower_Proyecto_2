//
// Created by carlo on 6/30/2020.
//

#include "BlueSpectre.h"

BlueSpectre::BlueSpectre(string pId, string pType, vector<string> pPatrolRoute,
                         Direction pDirection, double pRouteVelocity, double pPersuitVelocity, int pVisionRange)
        : Spectre(pId, pType, pPatrolRoute, pDirection, pRouteVelocity, pPersuitVelocity, pVisionRange) {



}

void BlueSpectre::teleport() {

}
