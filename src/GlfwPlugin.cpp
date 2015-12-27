/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "plugin/Plugin.h"
#include <iostream>

namespace MinVR {

class GlfwPlugin : public MinVR::Plugin {
public:
	PLUGIN_API GlfwPlugin() {
		std::cout << "GlfwPlugin created." << std::endl;
	}
	PLUGIN_API virtual ~GlfwPlugin() {
		std::cout << "GlfwPlugin destroyed." << std::endl;
	}
	PLUGIN_API bool registerPlugin(MinVR::PluginInterface *iface)
	{
		std::cout << "Registering GlfwPlugin with the following interface: " << iface->getName() << std::endl;
		return true;

		/*VRInputDeviceInterface* inputDeviceInterface = iface->getInterface<VRInputDeviceInterface>();
		if (inputDeviceInterface != NULL)
		{
			std::cout << "Registering VrpnPlugin with the following interface: " << iface->getName() << std::endl;
			inputDeviceInterface->addInputDeviceDriver(new VrpnDeviceDriver());
			return true;
		}

		return false;*/
	}
	PLUGIN_API bool unregisterPlugin(MinVR::PluginInterface *iface)
	{
		std::cout << "Unregistering GlfwPlugin with the following interface: " << iface->getName() << std::endl;
		return true;
	}
};

}

extern "C"
{
	PLUGIN_API MinVR::Plugin* loadPlugin() {
		return new MinVR::GlfwPlugin();
	}
}

