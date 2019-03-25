#ifndef PHASABLE_BLOCKS_H
#define PHASABLE_BLOCKS_H

class PhasableBlock
{
    public:
    int locationX, locationY;
    PhasableBlock();
    static void Display(float beginX, float beginY, float blockWidth, float blockHeight);

};
#endif
