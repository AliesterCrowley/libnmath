/*

    This file is part of the nemesis math library.

    plane.cc
	Plane

    Copyright (C) 2008, 2010
    Papadopoulos Nikolaos

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General
    Public License along with this library; if not, write to the
    Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301 USA

*/

#include <math.h>
#include "plane.h"

#include "defs.h"
#include "vector.h"
#include "intinfo.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef __cplusplus
}

Plane::Plane()
	: distance(NMATH_PLANE_DEFAULT_DISTANCE)
{}

Plane::Plane(const Vector3 &norm, double distance)
	: normal(norm), distance(distance > 0 ? distance : NMATH_PLANE_DEFAULT_DISTANCE)
{}

bool Plane::intersection(const Ray &ray, IntInfo* inf) const
{
	// algebraic solution

	// check if the ray is travelling parallel to the plane.
	// if the ray is in the plane then we ignore it.
	double n_dot_dir = dot(ray.direction, normal);

	// we use two-sided planes so we ignore the sign of n_dot_dir
	if (fabs(n_dot_dir) < EPSILON) 
	{
		return false;
	}
	
	Vector3 v = normal * distance;
	Vector3 vorigin = v - ray.origin;

	double n_dot_vo = dot(vorigin, normal);
	double t = n_dot_vo / n_dot_dir; 

	if (t < EPSILON || t > 1.0) 
	{
		return false;
	}

	if (inf) 
	{
		inf->t = t;
		inf->point = ray.origin + ray.direction * t;
		inf->normal = normal;
		inf->geometry = this;
	}

	return true;
}

void Plane::calc_bbox()
{
	// The plane is infinite so the bounding box is infinity as well
	bbox.max = Vector3(NM_INFINITY, NM_INFINITY, NM_INFINITY);
	bbox.min = -bbox.max;
}

#endif	/* __cplusplus */