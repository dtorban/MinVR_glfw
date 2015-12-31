/* ================================================================================

This file is part of the MinVR Open Source Project.

File: main.cpp

Original Author(s) of this File:
	Dan Orban, 2015, University of Minnesota

Author(s) of Significant Updates/Modifications to the File:
	...

-----------------------------------------------------------------------------------
Copyright (c) 2015 Regents of the University of Minnesota
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice, this
  list of conditions and the following disclaimer in the documentation and/or
  other materials provided with the distribution.

* The name of the University of Minnesota, nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
================================================================================ */

#include <iostream>
#include "plugin/PluginManager.h"
#include "plugin/PluginInterface.h"
#include <vector>
#include <string>
#include "main/VRPluginInterface.h"
#include "GL/gl.h"
#include "main/VRTimer.h"
#include "display/VRRenderer.h"

using namespace MinVR;
using namespace std;

VRDisplayDeviceFactory* displayFactory;
VRInputDeviceFactory* inputDeviceFactory;
VRTimer* mainTimer;

class TestInterface : public MinVR::VRPluginInterface {
public:
	TestInterface() {}
	virtual ~TestInterface() {}

	void addVRDisplayDeviceFactory(VRDisplayDeviceFactory* factory) {displayFactory = factory;}
	void addVRInputDeviceFactory(VRInputDeviceFactory* factory) { inputDeviceFactory = factory; }
	void addVRTimer(VRTimer* timer) { mainTimer = timer; }
};

class Renderer : public VRRenderer {
public:
	Renderer() {}
	virtual ~Renderer() {}

	void render() const
	{
		  float ratio;
		  int width = 640;
		  int height = 480;
		  ratio = width / (float) height;
		  //glViewport(0, 0, width, height);
		  glClear(GL_COLOR_BUFFER_BIT);
		  glMatrixMode(GL_PROJECTION);
		  glLoadIdentity();
		  glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		  glMatrixMode(GL_MODELVIEW);
		  glLoadIdentity();
		  glRotatef((float) mainTimer->getTime() * 50.f, 0.f, 0.f, 1.f);
		  glBegin(GL_TRIANGLES);
		  glColor3f(1.f, 0.f, 0.f);
		  glVertex3f(-0.6f, -0.4f, 0.f);
		  glColor3f(0.f, 1.f, 0.f);
		  glVertex3f(0.6f, -0.4f, 0.f);
		  glColor3f(0.f, 0.f, 1.f);
		  glVertex3f(0.f, 0.6f, 0.f);
		  glEnd();
	}
};

int main(int argc, char **argv) {
  cout << "Registering plugins..." << endl;
  cout << "Plugin path: " << PLUGINPATH << endl;

  TestInterface iface;

  PluginManager pluginManager;
  pluginManager.addInterface(dynamic_cast<TestInterface*>(&iface));
  pluginManager.loadPlugin(std::string(PLUGINPATH) + "/MinVR_glfw", "MinVR_glfw");

  VRDataIndex config;
  VRDisplayDevice* window = displayFactory->create(config, "", displayFactory)[0];

  VRInputDevice* inputDevice = inputDeviceFactory->create(config)[0];

  VRDataQueue dataQueue;
  VRDataIndex dataIndex;
  Renderer renderer;

  bool isRunning = true;

  while (window->isOpen() && isRunning)
  {
	  inputDevice->appendNewInputEventsSinceLastCall(dataQueue);

	  while (dataQueue.notEmpty())
	  {
		  std::string p = dataIndex.addSerializedValue( dataQueue.getSerializedObject() );
		  if (p == "/keyboard")
		  {
			  std::string val = dataIndex.getValue("value", p);
			  if (val == "ESC_down")
			  {
				  isRunning = false;
			  }
			  cout << val << endl;
		  }
		  dataQueue.pop();
	  }

	  window->startRendering(renderer);

	  window->finishRendering();
  }
}
