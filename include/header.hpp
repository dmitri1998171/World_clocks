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

#define MSK 3 // Moscow Standard Time is GMT+3

#define ARROW_NAME_OFFSET 0.03
#define DRAW_SEC_ARROW 0

using namespace std;

struct TimezoneInfo {
	string name;
	string shortFormName;
	short mskOffset;
	bool selected;
	ImVec4 color;
	float coords[2];
};

static std::vector<TimezoneInfo> timezones{
	{"Kaliningrad (MSK-1)", "KAL", (MSK-1), false, ImVec4(), {0, 0}},
	{"Moscow (MSK)", "MOS", MSK, true, ImVec4(), {0, 0}},
	{"Samara (MSK+1)", "SAM", (MSK+1), false, ImVec4(), {0, 0}},
	{"Yekaterinburg (MSK+2)", "YEK", (MSK+2), false, ImVec4(), {0, 0}},
	{"Omsk (MSK+3)", "OMS", (MSK+3), false, ImVec4(), {0, 0}},
	{"Krasnoyarsk (MSK+4)", "KRA", (MSK+4), false, ImVec4(), {0, 0}},
	{"Irkutsk (MSK+5)", "IRK", (MSK+5), false, ImVec4(), {0, 0}},
	{"Chita (MSK+6)", "CHI", (MSK+6), false, ImVec4(), {0, 0}},
	{"Vladivostok (MSK+7)", "VLA", (MSK+7), false, ImVec4(), {0, 0}},
	{"Magadan (MSK+8)", "MAG", (MSK+8), false, ImVec4(), {0, 0}},
	{"Kamchatka (MSK+9)", "KAM", (MSK+9), false, ImVec4(), {0, 0}},
};

bool isButtonPressed = false;
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
	coords[0][0] = (coords[0][0] - (W / 4)) / (W / 4);
	coords[0][1] = -(coords[0][1] - (H / 2)) / (H / 2);

	// Calc the angle 
	angle = radianToDegree(atan2(coords[0][0], coords[0][1]));

	// Fix length
	float c = 0.375 / sqrt (coords[0][0] * coords[0][0] + coords[0][1] * coords[0][1]);
	
	coords[0][0] *= c;
	coords[0][1] *= c;

	for(auto& pair : timezones) {
		pair.coords[0] = coords[0][0] * cos(degreeToRadian(DEGREES_PER_HOUR) * (pair.mskOffset - currentTimeZone)) + coords[0][1] * sin(degreeToRadian(DEGREES_PER_HOUR) * (pair.mskOffset - currentTimeZone));
		pair.coords[1] = coords[0][1] * cos(degreeToRadian(DEGREES_PER_HOUR) * (pair.mskOffset - currentTimeZone)) - coords[0][0] * sin(degreeToRadian(DEGREES_PER_HOUR) * (pair.mskOffset - currentTimeZone));
	}
}

TimezoneInfo getTimezoneByKey(const string& key) {
	for(const auto& pair : timezones) {
		if(pair.name == key) {
			return pair;
		}
	}
	return {"", "", MSK, false, ImVec4(), {0, 0}};
}