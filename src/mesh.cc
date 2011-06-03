/*

    This file is part of the nemesis math library.

    mesh.cc
    Mesh

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

#include "mesh.h"

#include "defs.h"
#include "precision.h"
#include "vector.h"
#include "intinfo.h"

#ifdef __cplusplus
extern "C" {
#endif	/* __cplusplus */

#ifdef __cplusplus
}

/*	
	Vector3 a, b;
	a = v[2].position - v[0].position;
	b = v[1].position - v[0].position;
	normal = cross(b, a).normalized();
*/


Mesh::Mesh()
	: Geometry(GEOMETRY_MESH), smooth(false)
{}

Mesh::~Mesh()
{}

#include "triangle.h"

bool Mesh::intersection(const Ray &ray, IntInfo* i_info) const
{
	if(!aabb.intersection(ray))
	{
		return false;
	}

	bool found = false;

	IntInfo nearest;
	nearest.t = INFINITY;

	for(size_t i = 0; i < faces.size(); i++)
	{
		IntInfo inf;

		Triangle p;
		p.v[0] = vertices[faces[i].v[0]];
		p.v[1] = vertices[faces[i].v[1]];
		p.v[2] = vertices[faces[i].v[2]];
		p.calc_aabb();

		if(p.intersection(ray, &inf) && inf.t < nearest.t) 
		{
			nearest = inf;
			found = true;
		}
	}

	if(!found) 
	{
		return false;
	}

	if(i_info)
	{
		*i_info = nearest;
		i_info->geometry = this;
	}

	return true;
}

void Mesh::calc_aabb()
{
	aabb.min = Vector3(NM_INFINITY, NM_INFINITY, NM_INFINITY);
	aabb.max = Vector3(-NM_INFINITY, -NM_INFINITY, -NM_INFINITY);
		
	for(size_t i = 0; i < faces.size(); i++) 
	{
		for(int j = 0; j < 3; j++) 
		{
			Vector3 v = vertices[faces[i].v[j]].position; 

			// min
			if(v.x < aabb.min.x) aabb.min.x = v.x;
			if(v.y < aabb.min.y) aabb.min.y = v.y;
			if(v.z < aabb.min.z) aabb.min.z = v.z;

			// max
			if(v.x > aabb.max.x) aabb.max.x = v.x;
			if(v.y > aabb.max.y) aabb.max.y = v.y;
			if(v.z > aabb.max.z) aabb.max.z = v.z;
		}
	}
}

void Mesh::calc_vertex_normals()
{
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		

		// Calculate face normal
	/*	Vector3 a, b;
		a = (Mesh*(geo))->vertices[2].position - v[0].position;
		b = v[1].position - v[0].position;
		normal = cross(b, a).normalized();
*/
	}
}

#endif	/* __cplusplus */