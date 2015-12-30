/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <GlfwWindowFactory.h>
#include "GlfwWindow.h"

namespace MinVR {

GlfwWindowFactory::GlfwWindowFactory() {
}

GlfwWindowFactory::~GlfwWindowFactory() {
	for (int f = 0; f < windows.size(); f++)
	{
		delete windows[f];
	}
}

std::vector<VRDisplayDevice*> GlfwWindowFactory::create(
		const VRDataIndex& config) {
	std::vector<VRDisplayDevice*> newWindows;
	VRDisplayDevice* window = new GlfwWindow();
	newWindows.push_back(window);
	windows.push_back(window);
	return newWindows;
}

} /* namespace MinVR */
