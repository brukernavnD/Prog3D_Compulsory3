#include "VertexWriter.h"

#include <fstream>
#include <iostream>
#include <ostream>

#include "GameplayStatics.h"

void VertexWriter::WriteVertexData(std::string Path, std::vector<Vertex> Vertices, const bool Append)
{
	//open the file
	std::ofstream File;

	//check whether or not we should append to the file or not
	if (Append)
	{
		File.open(Path, std::ios::app);
	}
	else
	{
		File.open(Path, std::ios::out | std::ios::trunc);	
	}

	//check if opening the file was successful
	if (File.is_open())
	{
		//write first line
		File << "Vertices: " << Vertices.size() << std::endl;

		//iterate through each vertex
		for (const auto & LocVertex : Vertices)
		{
			//write the vertex's data to the file
			File << LocVertex.Position.x << "	" << LocVertex.Position.y << "	" << LocVertex.Position.z << "	" << LocVertex.Normal.r << "	" << LocVertex.Normal.g << "	" << LocVertex.Normal.b << "	" << std::endl;
		}
	}
	else
	{
		//print an error message
		std::cout << "Error: Could not open file " << Path << std::endl;
	}

	//close the file
	File.close();
}

std::vector<Vertex> VertexWriter::WriteVertexDataFromFunc(Vertex(* VertexFunction)(float Param), const int StartIndex, const int LastIndex, const int LevelOfDetail)
{
	//vector to store the vertices
	std::vector<Vertex> Vertices;

	//iterate through each index
	for (int LocIndex = StartIndex; LocIndex < LastIndex * LevelOfDetail + 1; LocIndex += 1)
	{

		//get the mathematical function's output for the current index
		Vertex CurrentVertex = VertexFunction(float(LocIndex) / float(LevelOfDetail));

		//add the vertex to the vector
		Vertices.push_back(CurrentVertex);

		////print the vertex
		//std::cout << CurrentVertex.Position.x << "	" << CurrentVertex.Position.y << "	" << CurrentVertex.Position.z << "	" << CurrentVertex.RGB.r << "	" << CurrentVertex.RGB.g << "	" << CurrentVertex.RGB.b << std::endl;
	}

	return Vertices;
}
