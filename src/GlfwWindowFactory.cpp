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

GlfwWindowFactory::GlfwWindowFactory(GlfwInputDevice* iDevice) : inputDevice(iDevice) {
}

GlfwWindowFactory::~GlfwWindowFactory() {
	for (int f = 0; f < windows.size(); f++)
	{
		delete windows[f];
	}
}

std::vector<VRDisplayDevice*> GlfwWindowFactory::create(
		const VRDataIndex& config, const std::string nameSpace, VRDisplayDeviceFactory* factory) {
	std::vector<VRDisplayDevice*> newWindows;
	GlfwWindow* window = new GlfwWindow();
	inputDevice->registerGlfwWindow(window);
	newWindows.push_back(window);
	windows.push_back(window);

	std::vector<VRDisplayDevice*> subDisplays = factory->create(config, nameSpace, factory);
	for (int f = 0; f < subDisplays.size(); f++)
	{
		window->addSubDisplay(subDisplays[f]);
	}

	return newWindows;
}

} /* namespace MinVR */
