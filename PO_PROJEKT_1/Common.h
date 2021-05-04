#ifndef COMMON_INCLUDED
#define COMMON_INCLUDED

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ESC 27
#define LETTER_S 83
#define LETTER_s 115
#define PLANT_GROWTH 13
#define REPROD_AGE 2

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
    DANDELION,      // mlecz
    GUARANA,
    WOLF_BERRIES,
    PINE_BORSCHT,    // Barszcz Sosnowskiego
    CYBER_SHEEP

};


#endif 