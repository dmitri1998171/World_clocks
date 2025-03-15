#include "header.hpp"

void UI() {
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
}

void renderBitmapString(float x, float y, void *font, char *string) {
	glRasterPos2f(x, y);

	for (char* c = string; *c != '\0'; c++)
		glutBitmapCharacter(font, *c);
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
