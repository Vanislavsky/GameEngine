#include "material.h"


material::material(int _diffuse, int _specular, float _shininess) {
    diffuse = _diffuse;
    specular = _specular;
    shininess = _shininess;
}

void material::set_diffuse(int _diffuse) {
    diffuse = _diffuse;
}

int material::get_diffuse() {
    return diffuse;
}

void material::set_specular(int _specular) {
    specular = _specular;
}

int material::get_specular() {
    return specular;
}

void material::set_shininess(float _shininess) {
    shininess = _shininess;
}

float material::get_shininess() {
    return shininess;
}