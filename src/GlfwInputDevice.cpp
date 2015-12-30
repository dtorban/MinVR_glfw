/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <GlfwInputDevice.h>
#include <ctime>

namespace MinVR {

GlfwInputDevice::GlfwInputDevice() {
}

GlfwInputDevice::~GlfwInputDevice() {
}

void GlfwInputDevice::appendNewInputEventsSinceLastCall(VRDataQueue& queue) {
/*	  dataIndex.addData("/HeadMove/x", 1);
	  dataIndex.addData("/HeadMove/y", 2);
	  dataIndex.addData("/HeadMove/z", 4);
	  dataIndex.addData("/HeadMove/timestamp", (int)clock());
	  queue.push(dataIndex.serialize("/HeadMove"));*/
	  for (int f = 0; f < events.size(); f++)
	  {
		  queue.push(events[f]);
	  }
}

std::vector<VRInputDevice*> GlfwInputDeviceFactory::create(
		const VRDataIndex& dataIndex) {
	std::vector<VRInputDevice*> devices;
	devices.push_back(device);
	return devices;
}


} /* namespace MinVR */

