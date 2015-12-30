/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef GLFWWINDOWFACTORY_H_
#define GLFWWINDOWFACTORY_H_

#include "display/VRDisplayDevice.h"
#include "GlfwInputDevice.h"

namespace MinVR {

class GlfwWindowFactory : public VRDisplayDeviceFactory {
public:
	GlfwWindowFactory(GlfwInputDevice* inputDevice);
	virtual ~GlfwWindowFactory();

	std::vector<VRDisplayDevice*> create(const VRDataIndex& config);

private:
	std::vector<VRDisplayDevice*> windows;
	GlfwInputDevice* inputDevice;
};

} /* namespace MinVR */

#endif /* GLFWWINDOWFACTORY_H_ */
