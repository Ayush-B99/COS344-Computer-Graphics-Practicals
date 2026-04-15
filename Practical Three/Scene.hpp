#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
using namespace std;

extern const float ROTOR_CX;
extern const float ROTOR_CY;
extern const float ROTOR_CZ;

void buildScene(vector<float>& tri, vector<float>& lines);
void buildRotor(vector<float>& tri, vector<float>& lines);

#endif