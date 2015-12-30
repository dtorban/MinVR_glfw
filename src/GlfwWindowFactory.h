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

namespace MinVR {

class GlfwWindowFactory : public VRDisplayDeviceFactory {
public:
	GlfwWindowFactory();
	virtual ~GlfwWindowFactory();

	std::vector<VRDisplayDevice*> create(const VRDataIndex& config);
};

} /* namespace MinVR */

#endif /* GLFWWINDOWFACTORY_H_ */
