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
}

std::vector<VRDisplayDevice*> GlfwWindowFactory::create(
		const VRDataIndex& config) {
	std::vector<VRDisplayDevice*> windows;
	windows.push_back(new GlfwWindow());
	return windows;
}

} /* namespace MinVR */
