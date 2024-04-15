#pragma once
#include <string>
#include <vector>

#include "Vertex.h"

class VertexWriter
{
	public:

	//function to write vertex data to a file
	static void WriteVertexData(std::string Path, std::vector<Vertex> Vertices, bool Append = false);

	//function to write vertex data to a file from a mathematical function
	static std::vector<Vertex> WriteVertexDataFromFunc(Vertex(* VertexFunction)(float Param), int StartIndex, int LastIndex, int LevelOfDetail);
};


