#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED

struct Position {
    int x, y;
    FIELD_STATE state;
    Position() :x(0), y(0) {};
    Position(int x, int y)
        :x(x), y(y) {};
};

enum DIRECTION {
    LEFT,
    TOP,
    RIGHT,
    BOTTOM
};

enum ORGANISMS {
    HUMAN=21,
    WOLF,   
    SHEEP,
    FOX,
    TURTLE,
    ANTELOPE,
    CYBER_SHEEP,
    GRASS,
    DANDELION,      // mlecz
    GUARANA,
    WOLF_BERRIES,
    PINE_BORSCHT    // Barszcz Sosnowskiego

};


enum FIELD_STATE {
    AVAILABLE,
    OCCUPIED,
    BORDER,
    NOTAVAILABLE
};

#endif 