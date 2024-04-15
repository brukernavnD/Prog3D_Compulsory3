#include "BezierCurve.h"

#include "Macros.h"

BezierCurve::BezierCurve(std::vector<Vertex> InControlPoints, /*std::vector<float> InControlVector,*/ const glm::vec3 InPosition, const glm::vec3 InSize) : WorldObject(InPosition, InSize, CREATE_NAME), ControlPoints(std::move(InControlPoints))/*, ControlVector(std::move(InControlVector))*/
{

}

std::vector<Vertex> BezierCurve::CreateVertices() const
{
	//storage for the vertices
	std::vector<Vertex> Vertices;

	//get the step size
	const float StepSize = 1.0f / float(LevelOfDetail);

	//loop through the curve
	for (int i = 0; i < LevelOfDetail; i++)
	{
		//get the parameter
		const float Param = float(i) * StepSize;

		//get the next parameter
		const float NextParam = (float(i) + 1) * StepSize;

		//get the points
		const Vertex P0 = Bezier(Param, ControlPoints);
		const Vertex P1 = Bezier(NextParam, ControlPoints);

		//add the points
		Vertices.push_back(P0);
		Vertices.push_back(P1);
	}

	//return the vertices
	return Vertices;
}

void BezierCurve::BeginPlay()
{
	//get the vertices in world space
	std::vector<Vertex> LocVertices = GetWorldVertices();

	//iterate through the world space vertices
	for (int Index = 0; Index < LocVertices.size(); ++Index)
	{
		//get the vertex
		Vertex& V = LocVertices[Index];

		//get the y value of the object right below this vertex's position
		const float YBelow = GetYBelow(V.Position);

		//check if the y below is not the default value
		if (YBelow != 0.0000000001f)
		{
			//set the y value of the vertex
			V.Position.y = YBelow /*+ 0.035f * Size.y*/;
		}
		else
		{
			//remove the vertex
			LocVertices.erase(LocVertices.begin() + Index);

			//decrement the index
			--Index;
		}
	}

	//get the model matrix
	glm::mat4 model = GetModelMatrix();

	//invert the model matrix
	model = inverse(model);

	//iterate through the world space vertices
	for (Vertex& V : LocVertices)
	{
		//get the position of the vertex
		glm::vec4 Position = glm::vec4(V.Position, 1.0f);

		//transform the position
		Position = model * Position;

		//set the position of the vertex
		V.Position = glm::vec3(Position);
	}

	//set the vertices
	Vertices = LocVertices;
}

void BezierCurve::Render()
{
	//get our model matrix
	const glm::mat4 model = GetModelMatrix();

	//get our VertexIndex
	const int VertexIndex = VERTEX_INDEX_REF;

	//set the model matrix
	glUniformMatrix4fv(glGetUniformLocation(SHADER_REF, MODEL_KEY_REF), 1, GL_FALSE, &model[0][0]);

	//draw our vertices
	glDrawArrays(GL_LINE_STRIP, VertexIndex, Vertices.size());
}

Vertex BezierCurve::GetPointOnCurve(const int Index) const
{
	//return the vertex
	return TranslateToWorldSpace(Vertices[Index]);
}
