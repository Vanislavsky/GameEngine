#pragma once
class material
{
private:
    int diffuse;
    int specular;
    float shininess;

public:
    material(int _diffuse = 0, int _specular = 0, float _shininess = 0.0f);

    void set_diffuse(int _diffuse);
    int get_diffuse();

    void set_specular(int _specular);
    int get_specular();

    void set_shininess(float _shininess);
    float get_shininess();
};

