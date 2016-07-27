#include "Graph.h"
#include "../utils/mathUtils.h"

Graph::Graph() : GuiObj(0, 0, 100, 100, nullptr)
{
	xVal = nullptr;
	yVal = nullptr;

	table.AddValueMap(0, SColor(255, 100, 255, 175));
	table.AddValueMap(100, SColor(255, 255, 175, 100));
	table.AddValueMap(1000, SColor(255, 255, 100, 100));

	setWindow(-10, -10, 10, 10);
}

Graph::Graph(int _xpos, int _ypos, int _width, int _height, GuiObj* _parent) : GuiObj(_xpos, _ypos, _width, _height, _parent)
{
	xVal = nullptr;
	yVal = nullptr;

	table.AddValueMap(0, SColor(255, 100, 255, 175));
	table.AddValueMap(100, SColor(255, 255, 175, 100));
	table.AddValueMap(1000, SColor(255, 255, 100, 100));

	setWindow(-10, -10, 10, 10);
}

Graph::~Graph()
{

}

void Graph::SetContParam(double *_xVal, double *_yVal, double _maxVals)
{
	cont = true;

	xVal = _xVal;
	yVal = _yVal;
	maxVals = _maxVals;

	while (vals.first.size() > maxVals)		vals.first.pop();
	while (vals.second.size() > maxVals)	vals.second.pop();
}

void Graph::SetStaticParam(std::vector<double> *_xVal, std::vector<double> *_yVal, double _maxVals)
{
	cont = false;
	maxVals = _maxVals;

	for (double val : *_xVal)	vals.first.push(val);
	for (double val : *_yVal)	vals.second.push(val);
}

void Graph::Clear()
{
	while (vals.first.size() > 0)	vals.first.pop();
	while (vals.second.size() > 0)	vals.second.pop();
}

void Graph::setWindow(double _xBeg, double _yBeg, double _xEnd, double _yEnd)
{
	xBeg = _xBeg;	yBeg = _yBeg;
	xEnd = _xEnd;	yEnd = _yEnd;
}

void Graph::Resize(int _width, int _height)
{
	width = _width;
	height = _height;
}

double Graph::Val2Pos(double _val, AXIS _axis)
{
	double pos = 0;

	switch (_axis)
	{
		case X_AXIS:
			pos = absXpos + getPercent(xBeg, _val, xEnd)*width;
			return BOUND(xBeg, pos, xEnd);
			break;

		case Y_AXIS:
			pos = absYpos + (height - getPercent(yBeg, _val, yEnd)*height);
			return BOUND(yBeg, pos, yEnd);
			break;

		default:
			return -1;
			break;
	};
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

		SColor color = table.getColor(currVal);

		//currVal /= 10.0;
		//prevVal /= 10.0;

		vector2di p1(Val2Pos(i, X_AXIS), Val2Pos(prevVal, Y_AXIS));
		vector2di p2(Val2Pos(i + 1, X_AXIS), Val2Pos(currVal, Y_AXIS));

		_win.driver->draw2DLine(p1, p2, color);
	}

	double val = vals.second._Get_container()[i - 1];
	_win.font->draw(core::stringw(val), rect<s32>(Val2Pos(i, X_AXIS) + 10, Val2Pos(val, Y_AXIS), absXpos + 100, absYpos + 10), SColor(255, 255, 255, 255));

	_win.font->draw(core::stringw(1000), rect<s32>(absXpos, Val2Pos(1000, Y_AXIS), absXpos + 100, absYpos + 10), table.getColor(1000));
	_win.font->draw(core::stringw(100), rect<s32>(absXpos, Val2Pos(100, Y_AXIS), absXpos + 100, absYpos + 10), table.getColor(100));
	_win.font->draw(core::stringw(0), rect<s32>(absXpos, Val2Pos(0, Y_AXIS), absXpos + 100, absYpos + 10), table.getColor(0));

	_win.driver->draw2DRectangleOutline(recti(absXpos, absYpos, absXpos + width, absYpos + height), SColor(255, 255, 255, 255));
}

void Graph::UpdateInternal(Window &_win)
{
	if (cont)
	{
		if (xVal == nullptr)	return;
		if (yVal == nullptr)	return;

		vals.first.push(*xVal);
		vals.second.push(*yVal);

		while (vals.first.size() > maxVals)		vals.first.pop();
		while (vals.second.size() > maxVals)	vals.second.pop();
	}
}