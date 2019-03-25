#ifndef WEAPONS_H
#define WEAPONS_H
class Weapon
{
    public:
    int locationX, locationY;
    Weapon();

    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);

};
#endif
