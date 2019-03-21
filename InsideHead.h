#pragma once
#ifndef _INC_INSIDEHEAD
#define _INC_INSIDEHEAD

#include <GLTools.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL\glut.h>

const double Black[3]	= { 0.0, 0.0, 0.0 };
const double White[3]	= { 1.0, 1.0, 1.0 };
const double Red[3]		= { 1.0, 0.0, 0.0 };
const double Green[3]	= { 0.0, 1.0, 0.0 };
const double Blue[3]	= { 0.0, 0.0, 1.0 };
//const double White[3]	= { 1.0, 1.0, 1.0 };
//const double White[3]	= { 1.0, 1.0, 1.0 };
//const double White[3]	= { 1.0, 1.0, 1.0 };
//const double White[3]	= { 1.0, 1.0, 1.0 };
//const double White[3]	= { 1.0, 1.0, 1.0 };

const double GolbalFovy = 30;
const double GoldenMean = (sqrt(5.0) - 1) / 2;//0.6180339887
const double GolbalTranslateZ = -5000;//all of the picture that must be translated on "z" just for seen

enum Control
{
	start,stop
};

class TimeManager
{
public:
	int Time;
	int Value;
	double Step;

	TimeManager();
	TimeManager(int time, double step);
	TimeManager(int time, double step, int value);	
};

void init();
void ChangeSize(int w, int h);
#endif