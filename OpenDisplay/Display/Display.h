#pragma once

#include "Bitmap/DrawBitmapDD7.h"

// TODO: Fix ReSharper++ markings
class Display
{
    DrawBitmapDD7* drawBitmapDD7;
    int unknown0;
    int unknown1;
    int unknown2;
    int unknown3;

public:
    Display();

   /* virtual void sub_10026AF0();
    virtual void sub_10026B20();
    virtual void sub_10026600();
    virtual void sub_1001FF00();
    virtual void sub_10026B00();
    virtual void sub_1000A180();
    virtual void sub_100042C0();
    virtual void sub_10026B10();
    virtual void nullsub_2();
    virtual void sub_10007970();
    virtual void nullsub_4();
    virtual void sub_10025D30();
    virtual void sub_10025F80();
    virtual void sub_10026070();
    virtual void sub_100262E0();
    virtual void sub_100260E0();
    virtual void sub_10026210();
    virtual void sub_10026350();
    virtual void sub_100263F0();
    virtual void sub_10026550();
    virtual void sub_10026490();
    */
	virtual DrawBitmapDD7* getDrawBitmapInstance();
	/*
    virtual void sub_10026560();
    virtual void sub_10026570();
    virtual void sub_10026610();
    virtual void sub_100251A0();*/
    virtual void createDrawBitmapDD7();
   // virtual void sub_100265A0();

    static void CreateDisplayInstance(bool unknown, Display** display);
};