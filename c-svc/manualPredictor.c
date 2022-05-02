#include "manualPredictor.h"

double predict(double pointToPredict[3], HyperPlane hyperPlane){
    return dotProduct3dVector(pointToPredict, hyperPlane.vector) + hyperPlane.intercept;
}

/*
void getHyperPlanes(HyperPlane* hyperPlanes){
    hyperPlanes = {
            {DRIVING, STATIONARY, { 0.19360316, -0.05755878,  0.06869084}, -2.11173355},
            {DRIVING, USING,      {-0.01926972, -0.0473883,   0.00589928},  2.78350823},
            {DRIVING, WALKING,    {-0.03895607, -0.0069259,   0.00745679},  3.23086372},
            {STATIONARY, USING,   {-0.14289515,  0.02128519, -0.01012966},  1.80626325},
            {STATIONARY, WALKING, {-0.04405645,  0.01245427, -0.00702321},  2.26081931},
            {USING, WALKING,      {-0.01216422,  0.04764652,  0.00791857}, -1.25052248},
            };
};
*/


HyperPlane HYPER_PLANES[HYPER_PLANES_LENGTH] = {
            {DRIVING, STATIONARY, { 0.19360316, -0.05755878,  0.06869084}, -2.11173355},
            {DRIVING, USING,      {-0.01926972, -0.0473883,   0.00589928},  2.78350823},
            {DRIVING, WALKING,    {-0.03895607, -0.0069259,   0.00745679},  3.23086372},
            {STATIONARY, USING,   {-0.14289515,  0.02128519, -0.01012966},  1.80626325},
            {STATIONARY, WALKING, {-0.04405645,  0.01245427, -0.00702321},  2.26081931},
            {USING, WALKING,      {-0.01216422,  0.04764652,  0.00791857}, -1.25052248},
            };
