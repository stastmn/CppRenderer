#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>

class Model {
private:
	std::vector<DirectX::XMFLOAT3> verts_;
	std::vector<std::vector<int> > faces_;
public:
	Model(const char *filename);
	~Model();
	int nverts();
	int nfaces();
	DirectX::XMFLOAT3 vert(int i);
	std::vector<int> face(int idx);
};

