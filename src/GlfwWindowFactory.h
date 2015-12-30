/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef GLFWWINDOWFACTORY_H_
#define GLFWWINDOWFACTORY_H_

namespace MinVR {

class GlfwWindowFactory {
public:
	GlfwWindowFactory();
	virtual ~GlfwWindowFactory();
};

} /* namespace MinVR */

#endif /* GLFWWINDOWFACTORY_H_ */