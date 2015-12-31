/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <GlfwWindow.h>
#include <iostream>

namespace MinVR {

GlfwWindow::GlfwWindow() {
	window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	if (!window)
	{
		std::cout << "Error creating window." << std::endl;
	}
	std::cout << "Created window." << std::endl;
	glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

GlfwWindow::~GlfwWindow() {
	glfwDestroyWindow(window);
}

void GlfwWindow::use() {
	glfwMakeContextCurrent(window);
}

void GlfwWindow::release() {
}

void GlfwWindow::startRendering(const MinVR::VRRenderer& renderer) {
	use();
	renderer.render();
}

bool GlfwWindow::isOpen() {
	return !glfwWindowShouldClose(window);
}

void GlfwWindow::finishRendering() {
	glfwSwapBuffers(window);
    glfwPollEvents();
}

} /* namespace MinVR */
