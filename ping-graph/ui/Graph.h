#ifndef GRAPH_H
#define GRAPH_H

#include <queue>

#include "Window.h"
#include "GuiObj.h"

class Graph: public GuiObj
{
	public:
		Graph(int _xpos, int _ypos, int _width, int _height, GuiObj* _parent = nullptr);
		virtual ~Graph();

		void SetParam(double* _xVal, double *_yVal, double _maxVals);
		void Resize(int _width, int _height);

	private:
		virtual void Draw(Window &_win);
		virtual void UpdateInternal(Window &_win);

		double *xVal, *yVal;
		double maxVals;
		std::pair<std::queue<double>, std::queue<double>> vals;
};

#endif