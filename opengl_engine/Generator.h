#pragma once


class Generator
{
public:


	virtual float get_point(int in_x, int in_y, int in_z);
	virtual float get_point_2d(int in_x, int in_y);
	virtual float * get_points(int in_x, int in_y, int in_z, int division);
	virtual float * get_points_2d(int in_x, int in_y, int division);

};

