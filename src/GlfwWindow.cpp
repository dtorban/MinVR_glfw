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

void GlfwWindow::startRendering(const MinVR::VRRenderer& renderer, int x) {
	use();
	if (subDisplays.size() > 0)
	{
		for (int f = 0; f < subDisplays.size(); f++)
		{
			VRDisplayDevice::startRendering(subDisplays[f], renderer, 1);
		}
	}
	else
	{
		renderer.render();
	}
}

bool GlfwWindow::isOpen() {
	return !glfwWindowShouldClose(window);
}

void GlfwWindow::finishRendering() {
	for (int f = 0; f < subDisplays.size(); f++)
	{
		subDisplays[f]->finishRendering();
	}

	glfwSwapBuffers(window);
    glfwPollEvents();
}

void GlfwWindow::addSubDisplay(VRDisplayDevice* display) {
	subDisplays.push_back(display);
}

} /* namespace MinVR */
