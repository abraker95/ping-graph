#ifndef GRAPH_H
#define GRAPH_H

#include <queue>

#include "Window.h"
#include "GuiObj.h"
#include "ColorTable.h"

class Graph: public GuiObj
{
	public:
		Graph(int _xpos, int _ypos, int _width, int _height, GuiObj* _parent = nullptr);
		virtual ~Graph();

		void SetContParam(double* _xVal, double *_yVal, double _maxVals);
		void SetStaticParam(std::vector<double> *_xVal, std::vector<double> *_yVal, double _maxVals);
		
		void setWindow(double _xBeg, double _yBeg, double _xEnd, double _yEnd);
		void Resize(int _width, int _height);

	private:
		enum AXIS
		{
			X_AXIS,
			Y_AXIS
		};

		virtual void Draw(Window &_win);
		virtual void UpdateInternal(Window &_win);

		double Val2Pos(double _val, AXIS _axis);

		double *xVal, *yVal;
		double xBeg, xEnd, yBeg, yEnd;
		double maxVals;
		bool cont;

		std::pair<std::queue<double>, std::queue<double>> vals;
		ColorTable table;
};

#endif