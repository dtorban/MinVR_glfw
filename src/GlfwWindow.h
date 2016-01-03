/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef GLFWWINDOW_H_
#define GLFWWINDOW_H_

#include "display/VRDisplayDevice.h"
#include <GLFW/glfw3.h>

namespace MinVR {

class GlfwWindow : public VRDisplayDevice {
public:
	GlfwWindow(int x, int y, int width, int height);
	virtual ~GlfwWindow();

	bool isOpen();
	void use(const MinVR::VRDisplayAction& action);
	void finishRendering();

	GLFWwindow* getWindow() const {
		return window;
	}

	//void addSubDisplay(VRDisplayDevice* display);

protected:
	void startRendering(const MinVR::VRRenderer& renderer, int x);

private:
	GLFWwindow* window;
	//std::vector<VRDisplayDevice*> subDisplays;
};

} /* namespace MinVR */

#endif /* GLFWWINDOW_H_ */
