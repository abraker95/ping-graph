#include "Graph.h"
#include "../utils/mathUtils.h"

Graph::Graph(int _xpos, int _ypos, int _width, int _height, GuiObj* _parent) : GuiObj(_xpos, _ypos, _width, _height, _parent)
{
	xVal = nullptr;
	yVal = nullptr;
}

Graph::~Graph()
{

}

void Graph::SetParam(double* _xVal, double *_yVal, double _maxVals)
{
	xVal = _xVal;
	yVal = _yVal;
	maxVals = _maxVals;

	while (vals.first.size() > maxVals)		vals.first.pop();
	while (vals.second.size() > maxVals)	vals.second.pop();
}

void Graph::Resize(int _width, int _height)
{

}

void Graph::Draw(Window &_win)
{
	if (vals.second.size() == 0)
		return;

	int i = 1;
	for (; i < vals.second.size(); i++)
	{
		double currVal = vals.second._Get_container()[i];
		double prevVal = vals.second._Get_container()[i - 1];

		SColor color;
		if (BTWN(0, currVal, 100))
			color = SColor(255, 100, 255, 175);
		else if (BTWN(100, currVal, 1000))
			color = SColor(255, 255, 175, 100);
		else
			color = SColor(255, 255, 100, 100);

		currVal /= 10.0;
		prevVal /= 10.0;

		currVal = height - currVal;
		prevVal = height - prevVal;

		_win.driver->draw2DLine(vector2di(absXpos + i, absYpos + prevVal), vector2di(absXpos + i + 1, absYpos + currVal), color);
	}

	double val = vals.second._Get_container()[i - 1];
	_win.font->draw(core::stringw(val), rect<s32>(absXpos + i + 10, absYpos + (height - val / 10.0), absXpos + 100, absYpos + 10), SColor(255, 255, 255, 255));

	_win.font->draw(core::stringw(1000), rect<s32>(absXpos, absYpos + (height - 1000.0 / 10.0), absXpos + 100, absYpos + 10), SColor(255, 255, 100, 100));
	_win.font->draw(core::stringw(100), rect<s32>(absXpos, absYpos + (height - 100.0 / 10.0), absXpos + 100, absYpos + 10), SColor(255, 255, 175, 100));
	_win.font->draw(core::stringw(0), rect<s32>(absXpos, absYpos + (height - 0.0 / 10.0), absXpos + 100, absYpos + 10), SColor(255, 100, 255, 175));
}

void Graph::UpdateInternal(Window &_win)
{
	if (xVal == nullptr)	return;
	if (yVal == nullptr)	return;

	vals.first.push(*xVal);
	vals.second.push(*yVal);

	while (vals.first.size() > maxVals)		vals.first.pop();
	while (vals.second.size() > maxVals)	vals.second.pop();
	
}