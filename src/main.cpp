#include "input.hpp"

void display() {
	UI();
	
	glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	glPushMatrix();
		glScalef(0.5, 1, 1);
		glTranslatef(x_offset, 0, 0);

		drawArrows();
		drawNumbers();
		glutSolidSphere(0.05, 10, 10); 		// Center Circle
	glPopMatrix();

    glutSwapBuffers();
    glutPostRedisplay();
}

void on_resize(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
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
	glutPositionWindow(1500, 300);

	glutDisplayFunc(display);
	glutReshapeFunc(on_resize);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL2_Init();
	ImGui_ImplGLUT_InstallFuncs();
	Init();

	glutMainLoop();

	// imgui cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

	return 0;
}


