#define GL_SILENCE_DEPRECATION

#include <iostream>
#include <map>
#include <stdio.h>
#include <ctime>
#include <GLUT/glut.h>

#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"

#define DEGREES_PER_MINUTE 6
#define DEGREES_PER_HOUR 30
#define PI 3.141592
#define W 600
#define H 300

#define MSK 3
#define SRT 4
#define NSK 7
#define CHT 9

#define DRAW_SEC_ARROW 0

using namespace std;

static vector<pair<string, bool>> timezones{
    {"Kaliningrad (MSK-1)", false},
    {"Moscow (MSK)", true},
    {"Samara (MSK+1)", false},
    {"Yekaterinburg (MSK+2)", false},
    {"Omsk (MSK+3)", false},
    {"Krasnoyarsk (MSK+4)", false},
    {"Irkutsk (MSK+5)", false},
    {"Yakutsk (MSK+6)", false},
    {"Vladivostok (MSK+7)", false},
    {"Magadan (MSK+8)", false},
    {"Kamchatka (MSK+9)", false},
};

bool isButtonPressed = false, isSingleArrowState = false;
int timer_var = 1 * 1000;	// in milliseconds
int angle, currentTimeZone, angleOffset;
float coords[5][2];
struct tm *t_m, *ptime; 

static float f = 0.0f;
static int counter = 0;
float x_offset = -1;

double degreeToRadian(double degree) {
	return degree * PI / 180;
}

double radianToDegree(double rad) {
	return rad * 180 / PI;
}

void calcArrowPos(int x, int y) {
	coords[0][0] = x;
	coords[0][1] = y;

	// Changing scale and offset
	coords[0][0] = (coords[0][0] - (W / 2)) / (W / 2);
	coords[0][1] = -(coords[0][1] - (H / 2)) / (H / 2);

	// Calc the angle 
	angle = radianToDegree(atan2(coords[0][0], coords[0][1]));

	// Fix length
	float c = 0.375 / sqrt (coords[0][0] * coords[0][0] + coords[0][1] * coords[0][1]);
	
	coords[0][0] *= c;
	coords[0][1] *= c;

	// Calc other arrows
	coords[1][0] = coords[0][0] * cos(degreeToRadian(DEGREES_PER_HOUR) * (MSK - currentTimeZone)) + coords[0][1] * sin(degreeToRadian(DEGREES_PER_HOUR) * (MSK - currentTimeZone));
	coords[1][1] = coords[0][1] * cos(degreeToRadian(DEGREES_PER_HOUR) * (MSK - currentTimeZone)) - coords[0][0] * sin(degreeToRadian(DEGREES_PER_HOUR) * (MSK - currentTimeZone));
	
	coords[2][0] = coords[0][0] * cos(degreeToRadian(DEGREES_PER_HOUR) * (SRT - currentTimeZone)) + coords[0][1] * sin(degreeToRadian(DEGREES_PER_HOUR) * (SRT - currentTimeZone));
	coords[2][1] = coords[0][1] * cos(degreeToRadian(DEGREES_PER_HOUR) * (SRT - currentTimeZone)) - coords[0][0] * sin(degreeToRadian(DEGREES_PER_HOUR) * (SRT - currentTimeZone));
	
	coords[3][0] = coords[0][0] * cos(degreeToRadian(DEGREES_PER_HOUR) * (NSK - currentTimeZone)) + coords[0][1] * sin(degreeToRadian(DEGREES_PER_HOUR) * (NSK - currentTimeZone));
	coords[3][1] = coords[0][1] * cos(degreeToRadian(DEGREES_PER_HOUR) * (NSK - currentTimeZone)) - coords[0][0] * sin(degreeToRadian(DEGREES_PER_HOUR) * (NSK - currentTimeZone));
	
	coords[4][0] = coords[0][0] * cos(degreeToRadian(DEGREES_PER_HOUR) * (CHT - currentTimeZone)) + coords[0][1] * sin(degreeToRadian(DEGREES_PER_HOUR) * (CHT - currentTimeZone));
	coords[4][1] = coords[0][1] * cos(degreeToRadian(DEGREES_PER_HOUR) * (CHT - currentTimeZone)) - coords[0][0] * sin(degreeToRadian(DEGREES_PER_HOUR) * (CHT - currentTimeZone));
}
