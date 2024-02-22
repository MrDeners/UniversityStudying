#include <stdio.h>


typedef enum COLOR {
    BLACK,// чёрный
    WHITE,// белый
    SILVER,// серебристый
//    BEIGE,// бежевый
//    TURQUOISE,// бирюзовый
//    BURGUNDY,// бордовый
//    BRONZE,// бронзовый
    BLUE,// голубой и синий и темно-синий и светло-синий
    YELLOW,// жёлтый
    GREEN,// зелёный и темно-зеленый и светло-зеленый
//    GOLD,// золотистый
//    CORAL,// коралловый
    BROWN,// коричневый
    RED,// красный и темно-красный
    PURPLE,// лиловый
//    COPPER,// медный
//    MINT,// мятный
    ORANGE,// оранжевый
//    PEACH,// персиковый
//    SAND,// песочный
    PINK,// розовый
    GREY,// серый и темно-серый и светло-серый
//    LILAC,// сиреневый
    VIOLET// фиолетовый
} color;


typedef struct {
    int ID;
    char *name;
    color COLOR;
    double diagonal;
    int RAM;
 } phones; 
