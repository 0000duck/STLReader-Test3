#pragma once
#ifndef MESH_H
#define MESH_H

#include "CompFab.h"

#include <map>
#include <vector>
#include <fstream>

//this library is used to import and export stl files


class Mesh {
public:
	/// triangle list
	std::vector<CompFab::Triangle> triangles;
	Mesh() {};
	Mesh & operator= (const Mesh& m);
	float parse_float(std::ifstream& s);
	CompFab::Vec3 parse_point(std::ifstream& s);
	Mesh(const std::string&, bool normalize);
	void load_mesh(const std::string& filename, bool normalize = true);
	void export_stl(const std::string& filename);
};
///@brief cube [0,1]^3
extern Mesh UNIT_CUBE;
void BBox(const Mesh & m, CompFab::Vec3 & mn,
	CompFab::Vec3 & mx);

void BBox(const std::vector<CompFab::Triangle >& triangles, CompFab::Vec3 & mn,
	CompFab::Vec3 & mx);
#endif


