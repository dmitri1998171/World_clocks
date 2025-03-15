#define GL_SILENCE_DEPRECATION

#include <iostream>
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

void renderBitmapString(float x, float y, void *font, char *string) {
	glRasterPos2f(x, y);

	for (char* c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
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

void drawNumbers() {
	glPushMatrix();
	
	glLoadIdentity();
	glScalef(0.5, 1, 1);
	glTranslatef(x_offset, 0, 0);
	glColor3f(0.0, 0.0, 0.0);

	glRectf(0.025,0.75,-0.025,0.6);		// 12

	glRotatef(30.0,0.0,0.0,-1.0);
	glRectf(0.025,0.75,-0.025,0.6);		// 1

	glLoadIdentity();
	glScalef(0.5, 1, 1);
	glTranslatef(x_offset, 0, 0);
	glRotatef(60.0,0.0,0.0,-1.0);
	glRectf(0.025,0.75,-0.025,0.6);		// 2
	
	glLoadIdentity();
	glScalef(0.5, 1, 1);
	glTranslatef(x_offset, 0, 0);
	glRectf(-0.75,0.025,-0.6,-0.025);	// 3

	glRotatef(120.0,0.0,0.0,-1.0);
	glRectf(0.025,0.75,-0.025,0.6);		// 4

	glLoadIdentity();
	glScalef(0.5, 1, 1);
	glTranslatef(x_offset, 0, 0);
	glRotatef(150.0,0.0,0.0,-1.0);
	glRectf(0.025,0.75,-0.025,0.6);		// 5

	glLoadIdentity();  
	glScalef(0.5, 1, 1);
	glTranslatef(x_offset, 0, 0);
	glRectf(0.025,-0.75,-0.025,-0.6);	// 6

	glRotatef(210.0,0.0,0.0,-1.0);
	glRectf(0.025,0.75,-0.025,0.6);		// 7

	glLoadIdentity();
	glScalef(0.5, 1, 1);
	glTranslatef(x_offset, 0, 0);
	glRotatef(240.0,0.0,0.0,-1.0);
	glRectf(0.025,0.75,-0.025,0.6);		// 8

	glLoadIdentity();
	glScalef(0.5, 1, 1);
	glTranslatef(x_offset, 0, 0);
	glRectf(0.75,0.025,0.6,-0.025);		// 9

	glRotatef(-60.0,0.0,0.0,-1.0);
	glRectf(0.025,0.75,-0.025,0.6);		// 10

	glLoadIdentity();
	glScalef(0.5, 1, 1);
	glTranslatef(x_offset, 0, 0);
	glRotatef(-30.0,0.0,0.0,-1.0);
	glRectf(0.025,0.75,-0.025,0.6);		// 11
	glLoadIdentity();

	glPopMatrix();
}

void drawArrows() {
	#if DRAW_SEC_ARROW
		// Second Arrow
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef(DEGREES_PER_MINUTE * t_m->tm_sec, 0.0, 0.0, -1.0);
		glRectf(-0.025, 0.6, 0.005, 0.0);
		glPopMatrix();
	#endif

	// Minute Arrow
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(DEGREES_PER_MINUTE * t_m->tm_min, 0.0, 0.0, -1.0);
	glRectf(-0.025, 0.57, 0.025, 0.0);
	glPopMatrix();	

	// Hour Arrow (local)
	glPushMatrix();
	glRotatef((DEGREES_PER_HOUR * t_m->tm_hour) + angleOffset, 0.0, 0.0, -1.0);
	glRectf(-0.025, 0.375, 0.025, 0.0);
	glPopMatrix();

	if( ! isSingleArrowState) {
		// Hour Arrow (MSK)
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef(DEGREES_PER_HOUR * (ptime->tm_hour + MSK) + angleOffset, 0.0, 0.0, -1.0);
		glRectf(-0.025, 0.375, 0.025, 0.0);
		glPopMatrix();

		// Hour Arrow (SRT)
		glColor3f(1.0, 0.0, 1.0);
		glPushMatrix();
		glRotatef(DEGREES_PER_HOUR * (ptime->tm_hour + SRT) + angleOffset, 0.0, 0.0, -1.0);
		glRectf(-0.025, 0.375, 0.025, 0.0);
		glPopMatrix();

		// Hour Arrow (NSK)
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
		glRotatef(DEGREES_PER_HOUR * (ptime->tm_hour + NSK) + angleOffset, 0.0, 0.0, -1.0);
		glRectf(-0.025, 0.375, 0.025, 0.0);
		glPopMatrix();

		// Hour Arrow (CHT)
		glColor3f(0.0, 1.0, 0.0);
		glPushMatrix();
		glRotatef(DEGREES_PER_HOUR * (ptime->tm_hour + CHT) + angleOffset, 0.0, 0.0, -1.0);
		glRectf(-0.025, 0.375, 0.025, 0.0);
		glPopMatrix();
	}
}

void drawFollowingArrows() {
	#if DRAW_SEC_ARROW
		// Second Arrow
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glRotatef(DEGREES_PER_MINUTE * t_m->tm_sec, 0.0, 0.0, -1.0);
		glRectf(-0.025, 0.6, 0.005, 0.0);
		glPopMatrix();
	#endif
	
	// Minute Arrow
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glRotatef(DEGREES_PER_MINUTE * t_m->tm_min, 0.0, 0.0, -1.0);
	glRectf(-0.025, 0.57, 0.025, 0.0);
	glPopMatrix();

	// Hour Arrow (local)
	glPushMatrix();
	glRotatef(angle, 0.0, 0.0, -1.0);
	glRectf(-0.025, 0.375, 0.025, 0.0);
	glPopMatrix();

	// Hour Arrow (MSK)
	glColor3f(1.0, 0.0, 0.0);
	renderBitmapString(coords[1][0] + 0.03, coords[1][1] + 0.03, GLUT_BITMAP_HELVETICA_10, "MSK");
	glPushMatrix();
	glRotatef(angle + (DEGREES_PER_HOUR * (MSK - currentTimeZone)), 0.0, 0.0, -1.0);
	glRectf(-0.025, 0.375, 0.025, 0.0);
	glPopMatrix();
	
	// Hour Arrow (SRT)
	glColor3f(1.0, 0.0, 1.0);
	renderBitmapString(coords[2][0] + 0.03, coords[2][1] + 0.03, GLUT_BITMAP_HELVETICA_10, "SRT");
	glPushMatrix();
	glRotatef(angle + (DEGREES_PER_HOUR * (SRT - currentTimeZone)), 0.0, 0.0, -1.0);
	glRectf(-0.025, 0.375, 0.025, 0.0);
	glPopMatrix();
	
	// Hour Arrow (NSK)
	glColor3f(0.0, 0.0, 1.0);
	renderBitmapString(coords[3][0] + 0.03, coords[3][1] + 0.03, GLUT_BITMAP_HELVETICA_10, "NSK");
	glPushMatrix();
	glRotatef(angle + (DEGREES_PER_HOUR * (NSK - currentTimeZone)), 0.0, 0.0, -1.0);
	glRectf(-0.025, 0.375, 0.025, 0.0);
	glPopMatrix();

	// Hour Arrow (CHT)
	glColor3f(0.0, 1.0, 0.0);
	renderBitmapString(coords[4][0] + 0.03, coords[4][1] + 0.03, GLUT_BITMAP_HELVETICA_10, "CHT");
	glPushMatrix();
	glRotatef(angle + (DEGREES_PER_HOUR * (CHT - currentTimeZone)), 0.0, 0.0, -1.0);
	glRectf(-0.025, 0.375, 0.025, 0.0);
	glPopMatrix();
}

void display() {
	// Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();
    ImGuiIO& io = ImGui::GetIO();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.

    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.
    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

    ImGui::SliderFloat("float", &f, 0.0f, 90.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
        counter++;

    ImGui::SameLine();
    ImGui::Text("counter = %d", counter);

    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();



    ImGui::Render();
	
	glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	glPushMatrix();
		glScalef(0.5, 1, 1);
		glTranslatef(x_offset, 0, 0);

		if(isButtonPressed)
			drawFollowingArrows();
		else 
			drawArrows();
			
		drawNumbers();
		glutSolidSphere(0.05, 10, 10); 		// Center Circle
	glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void on_resize(int w, int h) {
    int win_width = w;
    int win_height = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void ProcessNormalKeys(unsigned char key, int x, int y) {
	if(key == 27) exit(0);

	if(key == ' ') {
		isSingleArrowState = ! isSingleArrowState;
		glutPostRedisplay();
	}
}

void mouseMove(int x, int y) {
	if(isButtonPressed) {
		calcArrowPos(x, y);
		glutPostRedisplay();
	}
}

void MouseFunc(int button, int state, int x, int y) {
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		isButtonPressed = ! isButtonPressed;

		calcArrowPos(x, y);
		glutPostRedisplay();
	}
}

void About_a_time() {
	const time_t t = time(NULL);
	t_m = localtime(&t);
	ptime = gmtime(&t);

	if(t_m->tm_min > 29)
		angleOffset = t_m->tm_min / 2;

	currentTimeZone = t_m->tm_hour - ptime->tm_hour;
	
	// cout << "Local time is: " << t_m->tm_hour << ":" << t_m->tm_min << ":" << t_m->tm_sec << endl;
	// cout << "Absolute time is: " << ptime->tm_hour << ":" << ptime->tm_min << ":" << ptime->tm_sec << endl;
	// cout << endl;
}

void Timer(int) {
	About_a_time();
	glutPostRedisplay();
	glutTimerFunc(timer_var, Timer, 0);
}

void Init() {
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glutKeyboardFunc(ProcessNormalKeys); 
	glutMouseFunc(MouseFunc);
	glutPassiveMotionFunc(mouseMove);
	glutTimerFunc(timer_var, Timer, 0);
	About_a_time();
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowSize(W, H);
	glutCreateWindow("Clock_GLUT");

	glutDisplayFunc(display);
	glutReshapeFunc(on_resize);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL2_Init();
	Init();
	ImGui_ImplGLUT_InstallFuncs();

	glutMainLoop();

	// imgui cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

	return 0;
}


