#include "header.hpp"

void renderColorfulCheckbox(const char* label, bool* v, ImVec4 color) {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4 originalCheckMark = style.Colors[ImGuiCol_CheckMark];              // Сохраняем оригинальные цвета
    style.Colors[ImGuiCol_CheckMark] = color;                                 // Новый цвет галочки
    ImGui::Checkbox(label, v);
    style.Colors[ImGuiCol_CheckMark] = originalCheckMark;                     // Возвращаем оригинальные цвета
}

void timezonesMultiselect() {
    for (int i = 0; i < timezones.size(); i++) {
        // Генерция цвета на основе индекса
        float hue = (float)i / timezones.size();
        timezones[i].color = ImColor::HSV(hue, 0.7f, 0.7f);

		renderColorfulCheckbox(timezones[i].name.c_str(), &timezones[i].selected, timezones[i].color);
    }
}

void UI() {
	// Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGLUT_NewFrame();
    ImGui::NewFrame();
    ImGuiIO& io = ImGui::GetIO();

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
    ImGuiWindowFlags window_flags = 0;
    window_flags |= ImGuiWindowFlags_NoScrollbar;        // Убрать полосу прокрутки
    window_flags |= ImGuiWindowFlags_NoMove;             // Запретить перемещение окна
    window_flags |= ImGuiWindowFlags_NoResize;           // Запретить изменение размера окна
    window_flags |= ImGuiWindowFlags_NoCollapse;         // Запретить сворачивание окна
    window_flags |= ImGuiWindowFlags_NoSavedSettings;    // Не сохранять настройки окна

    ImGui::SetNextWindowPos(ImVec2(W / 2, 0), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(W / 2, H), ImGuiCond_FirstUseEver);
    ImGui::Begin("Timezones", nullptr, window_flags);                          // Create a window called "Hello, world!" and append into it.

    timezonesMultiselect();    

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

void drawConcreteArrow(string name) {
	TimezoneInfo value = getTimezoneByKey(name);

	if(value.selected) {
		glColor3f(value.color.x, value.color.y, value.color.z);
		glPushMatrix();

		if(isButtonPressed) {
			renderBitmapString(value.coords[0] + ARROW_NAME_OFFSET, value.coords[1] + ARROW_NAME_OFFSET, GLUT_BITMAP_HELVETICA_10, (char*)value.shortFormName.c_str());
			glRotatef(angle + DEGREES_PER_HOUR * (value.mskOffset - currentTimeZone), 0.0, 0.0, -1.0);
		} else 
			glRotatef(DEGREES_PER_HOUR * (ptime->tm_hour + value.mskOffset) + angleOffset, 0.0, 0.0, -1.0);

		glRectf(-0.025, 0.375, 0.025, 0.0);
		glPopMatrix();
	}
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
	// glPushMatrix();
	// glRotatef((DEGREES_PER_HOUR * t_m->tm_hour) + angleOffset, 0.0, 0.0, -1.0);
	// glRectf(-0.025, 0.375, 0.025, 0.0);
	// glPopMatrix();

	drawConcreteArrow("Kaliningrad (MSK-1)");
	drawConcreteArrow("Moscow (MSK)");
	drawConcreteArrow("Samara (MSK+1)");
	drawConcreteArrow("Yekaterinburg (MSK+2)");
	drawConcreteArrow("Omsk (MSK+3)");
	drawConcreteArrow("Krasnoyarsk (MSK+4)");
	drawConcreteArrow("Irkutsk (MSK+5)");
	drawConcreteArrow("Chita (MSK+6)");
	drawConcreteArrow("Vladivostok (MSK+7)");
	drawConcreteArrow("Magadan (MSK+8)");
	drawConcreteArrow("Kamchatka (MSK+9)");
}
