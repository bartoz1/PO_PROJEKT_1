#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED

enum FIELD_STATE {
    AVAILABLE,
    OCCUPIED,
    BORDER,
    NOTAVAILABLE,
    UNKNOWN
};

struct Position {
    int x, y;
    FIELD_STATE state;
    Position() :x(0), y(0), state(UNKNOWN) {};
    Position(int x, int y)
        :x(x), y(y), state(UNKNOWN) {};
    Position(int x, int y, FIELD_STATE state)
        :x(x), y(y), state(state) {};
};

enum DIRECTION {
    LEFT,
    TOP,
    RIGHT,
    BOTTOM,
    NONE
};

enum ORGANISMS {
    HUMAN=21,
    WOLF,   
    SHEEP,
    FOX,
    TURTLE,
    ANTELOPE,
    GRASS,
    CYBER_SHEEP,
    DANDELION,      // mlecz
    GUARANA,
    WOLF_BERRIES,
    PINE_BORSCHT    // Barszcz Sosnowskiego

};


#endif 