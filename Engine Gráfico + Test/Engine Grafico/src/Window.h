#ifndef WINDOW_H
#define WINDOW_H

#include "export.h"

#include <stdlib.h>
#include <string>
#include <iostream>

class GLFWwindow;

class ENGINE_API Window {
public:
	Window();
	~Window();
	GLFWwindow* window;
	int Start(const char* windowName);
	static void ClearBackground();
	bool WindowShouldClose();
	void FinishWindowCycle();
	void CloseWindow();
	void setWidth(int newWith);
	int getWidth();
	void setHeight(int newHeight);
	int getHeight();
private:
	int width;
	int height;

};
#endif // !WINDOW_H
