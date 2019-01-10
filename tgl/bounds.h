#pragma once
#ifndef _BOUNDS_H_
#define _BOUNDS_H_

namespace tgl
{

class Bounds
{
public:
	enum bounds_type_enum
	{
		BOX,
		CYLINDER
	};
	bounds_type_enum bounds_type;
};

class CylinderBounds : public Bounds
{
public:
	CylinderBounds(double in_radius, double in_height) { bounds_type = CYLINDER; radius = in_radius; height = in_height; }
	double radius;
	double height;
};

class BlockBounds : public Bounds
{
public:
	BlockBounds(double in_width, double in_height, double in_depth) { bounds_type = CYLINDER; width = in_width; height = in_height; depth = in_depth; }
	double width;
	double height;
	double depth;
};

} // namespace 

#endif