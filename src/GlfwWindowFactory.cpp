/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <GlfwWindowFactory.h>
#include "GlfwWindow.h"
#include <iostream>
#include "config/VRDataIndex.h"

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
		VRDataIndex& config, const std::string nameSpace, VRDisplayDeviceFactory* factory) {

/*	std::list<std::string> names = config.getNames();
	for (VRContainer::iterator f = names.begin(); f != names.end(); f++)
	{
		std::cout << *f << std::endl;
	}*/

	std::vector<VRDisplayDevice*> newWindows;

	VRContainer item = config.getValue(nameSpace);

	for (VRContainer::iterator f = item.begin(); f != item.end(); f++)
	{
		if (config.getType(*f) == VRCORETYPE_CONTAINER) {

			bool createWindow = false;
			int width = 0;
			int height = 0;

			VRContainer item = config.getValue(*f);
			for (VRContainer::iterator it = item.begin(); it != item.end(); it++) {
				if (*it == *f + "/displayType")
				{
					std::string type = config.getValue(*it);
					if (type == "glfw_display")
					{
						createWindow = true;
					}
					width = config.getValue("width", *f);
					height = config.getValue("height", *f);
				}
			}

			if (createWindow)
			{
				GlfwWindow* window = new GlfwWindow(0, 0, width, height);
				inputDevice->registerGlfwWindow(window);
				newWindows.push_back(window);
				windows.push_back(window);

				std::vector<VRDisplayDevice*> subDisplays = factory->create(config, *f, factory);
				for (int f = 0; f < subDisplays.size(); f++)
				{
					window->addSubDisplay(subDisplays[f]);
				}
			}
		}
	}

	return newWindows;
}

} /* namespace MinVR */
