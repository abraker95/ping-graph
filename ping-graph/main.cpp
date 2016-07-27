#include <thread>
#include <fstream>
#include <stdlib.h>
#include <iostream>

#include "irrlicht/include/irrlicht.h"
#include "ui/GuiObj.h"
#include "ui/Graph.h"

#ifdef _IRR_WINDOWS_
	#pragma comment(lib, "irrlicht/lib/Win32-visualstudio/Irrlicht.lib")
	//#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")  // show/hide console
#endif

#include "ui\Window.h"

double ms = 0;
bool run = true;

int GetPingTime()
{
	std::fstream ping("ping_res.txt");
	std::string line;

	if (ping.is_open())
	{
		std::getline(ping, line);
		std::getline(ping, line);
		std::getline(ping, line);
	}

	ping.close();

	int iTime = line.find("time");
	int iMs = line.find("ms");

	if (iTime == -1 || iMs == -1)
		return 0;

	std::string time = line.substr(iTime + 5, iMs - (iTime + 5));
	return atoi(time.c_str());
}

void Ping()
{
	while (run)
	{
		system("ping 192.168.1.1 -n 1 > ping_res.txt");
		ms = GetPingTime();
	}
}

int main()
{
	const int RESX = 1080;
	const int RESY = 720;

	double time = 0;

	Window win(RESX, RESY);
		win.device->setWindowCaption(L"ping-graph");
		win.device->setResizable(true);

	Graph graph(10, 10, 100, 100);
		graph.SetContParam(&time, &ms, 1000);

	std::thread first(Ping);

	while (win.device->run())
	{
		win.reciever.Update();
		win.updateFPS();

		win.driver->beginScene(true, true, SColor(255, 0, 0, 0));

			UpdateGuiObjs(win);

		win.driver->endScene();
		win.device->yield();
	}

	run = false;
	first.join();
	win.device->drop();
}