#include "stdafx.h"
#include "Mesh.h"
#include "CompFab.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#ifdef _WIN32
#define NOMINMAX //Stop errors with std::max
#include <windows.h>
#endif
#include <stdio.h>
#include <cstdlib>
#include <utility>
#include <map>
#include <sstream>
#include <string.h>


Mesh::Mesh(const std::string& filename, bool normalize)
{
	load_mesh(filename, normalize);
}

// read stl file data into algorithm
//Binary Stl format
//UINT8[80] – Header
//UINT32 – Number of triangles
//foreach triangle
//REAL32[3] – Normal vector
//REAL32[3] – Vertex 1
//REAL32[3] – Vertex 2
//REAL32[3] – Vertex 3
//UINT16 – Attribute byte count
//end

void Mesh::load_mesh(const std::string& filename, bool normalize){
	//read binary file
	//file open for reading
	//operations are performed in binary mode rather than text
	std::ifstream f(filename, std::ios::in | std::ios::binary);
	if (!f.good()) {
		std::cout << "Error: cannot open mesh " << filename << "\n";
		return;
	}
	//header
	char header_info[80] = "";
	char n_triangles[4];
	f.read(header_info, 80);
	f.read(n_triangles, 4);
	unsigned int* r = (unsigned int*)n_triangles;
	unsigned int num_triangles = *r;
	//number of triangles
	std::cout << "Num Triangles: " << num_triangles << "\n";
	for (unsigned int i = 0; i < num_triangles; i++) {
		//normal vector of triangle
		auto normal = parse_point(f);
		//vertice of triangle
		auto v1 = parse_point(f);
		//vertice of triangle
		auto v2 = parse_point(f);
		//vertice of triangle
		auto v3 = parse_point(f);
		//push into triangle list
		triangles.push_back(CompFab::Triangle(normal, v1, v2, v3));
		//attributes
		char dummy[2];

		f.read(dummy, 2);
	}
	std::cout << "Successfully import stl file"<< "\n";
}

//parse the binary data and convert to float 
float Mesh::parse_float(std::ifstream& s) {

	char f_buf[sizeof(float)];

	s.read(f_buf, 4);

	float* fptr = (float*)f_buf;

	return *fptr;
};

//parse the vector
CompFab::Vec3 Mesh::parse_point(std::ifstream& s) {

	CompFab::Vec3 vec;

	vec[0] = parse_float(s);

	vec[1] = parse_float(s);

	vec[2] = parse_float(s);

	return  vec;
};

//export binary stl file 
//Binary Stl format
//UINT8[80] – Header
//UINT32 – Number of triangles
//foreach triangle
//REAL32[3] – Normal vector
//REAL32[3] – Vertex 1
//REAL32[3] – Vertex 2
//REAL32[3] – Vertex 3
//UINT16 – Attribute byte count
//end

void Mesh::export_stl(const std::string& filename) {
	//binary file
	std::string header_info = "solid " + filename + "-output";
	char head[80];
	std::strncpy(head, header_info.c_str(), sizeof(head));
	//attributes
	char attribute[2] = "0";
	//number of triangles
	int nTrilong = triangles.size();
	std::ofstream ofs(filename, std::ofstream::binary | std::ofstream::trunc);
	if (!ofs.good()) {
		std::cout << "cannot open output file" << filename << "\n";
	}
	//write header into stl file
	ofs.write(head, sizeof(head));
	//write number of triangles into stl file
	ofs.write((char*) &nTrilong,sizeof(int));
	for (unsigned int ii = 0; ii < triangles.size(); ++ii) {
		// normal vector coordinates

		ofs.write((char*)&triangles[ii].normal.m_x, sizeof(float));
		ofs.write((char*)&triangles[ii].normal.m_y, sizeof(float));
		ofs.write((char*)&triangles[ii].normal.m_z, sizeof(float));

		//vertex 1 coordinates
		ofs.write((char*)&triangles[ii].m_v1.m_x, sizeof(float));
		ofs.write((char*)&triangles[ii].m_v1.m_y, sizeof(float));
		ofs.write((char*)&triangles[ii].m_v1.m_z, sizeof(float));

		//vertex 2 coordinates
		ofs.write((char*)&triangles[ii].m_v2.m_x, sizeof(float));
		ofs.write((char*)&triangles[ii].m_v2.m_y, sizeof(float));
		ofs.write((char*)&triangles[ii].m_v2.m_z, sizeof(float));

		//vertex 3 coordinates
		ofs.write((char*)&triangles[ii].m_v3.m_x, sizeof(float));
		ofs.write((char*)&triangles[ii].m_v3.m_y, sizeof(float));
		ofs.write((char*)&triangles[ii].m_v3.m_z, sizeof(float));

		//Attibutes
		ofs.write(attribute, sizeof(short));
	}
	
	ofs.close();
	std::cout << "Successfully export stl file." << std::endl;
};

Mesh & Mesh::operator= (const Mesh& m)
{
	triangles = m.triangles;
	return *this;
}

void BBox(const Mesh & m,
	CompFab::Vec3 & mn, CompFab::Vec3 & mx)
{
	BBox(m.triangles, mn, mx);
}

void BBox(const std::vector<CompFab::Triangle >& triangles,
	CompFab::Vec3 & mn, CompFab::Vec3 & mx)
{
	mn = triangles[0].m_v1;
	mx = triangles[0].m_v1;
	for (unsigned int ii = 1; ii < triangles.size(); ii++) {
		for (int dim = 0; dim < 3; dim++) {
			if (triangles[ii].m_v1[dim] < mn[dim]) {
				mn[dim] = triangles[ii].m_v1[dim];
			}
			if (triangles[ii].m_v2[dim] < mn[dim]) {
				mn[dim] = triangles[ii].m_v2[dim];
			}
			if (triangles[ii].m_v3[dim] < mn[dim]) {
				mn[dim] = triangles[ii].m_v3[dim];
			}
			if (triangles[ii].m_v1[dim] > mx[dim]) {
				mx[dim] = triangles[ii].m_v1[dim];
			}
			if (triangles[ii].m_v2[dim] > mx[dim]) {
				mx[dim] = triangles[ii].m_v2[dim];
			}
			if (triangles[ii].m_v3[dim] > mx[dim]) {
				mx[dim] = triangles[ii].m_v3[dim];
			}
		}
	}
	float distance;
	distance = sqrt(pow((mx[0] - mn[0]), 2) + pow((mx[1] - mn[1]), 2) + pow((mx[2] - mn[2]), 2));
	std::cout << "the smallest x: " << mn[0] << std::endl;
	std::cout << "the smallest y: " << mn[1] << std::endl;
	std::cout << "the smallest z: " << mn[2] << std::endl;
	std::cout << "the largest x: " << mx[0] << std::endl;
	std::cout << "the largest y: " << mx[1] << std::endl;
	std::cout << "the largest z: " << mx[2] << std::endl;
	std::cout << "the largest distance is: " << distance << std::endl;
}