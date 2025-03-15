#include "draw.hpp"

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
