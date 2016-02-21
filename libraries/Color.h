#pragma once

class Color {
public:
    int redVal;
    int greenVal;
    int blueVal;

    Color(int red, int green, int blue) : redVal(red), greenVal(green), blueVal(blue) {}
};

Color white(255, 255, 255);
Color black(0, 0, 0);
Color red(255, 0, 0);
Color green(0, 255, 0);
Color blue(0, 0, 255);
Color yellow(255, 50, 0);
Color orange(255, 15, 0);
Color purple(255, 0, 165);
Color pink(255, 0, 55);
Color cyan(0, 200, 160);
