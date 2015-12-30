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
	GlfwWindow();
	virtual ~GlfwWindow();

	bool isOpen();
	void use();
	void release();
	void startRendering();
	void finishRendering();

private:
	GLFWwindow* window;
};

} /* namespace MinVR */

#endif /* GLFWWINDOW_H_ */
