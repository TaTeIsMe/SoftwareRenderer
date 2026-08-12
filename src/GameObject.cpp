#include "GameObject.h"
#include<fstream>
#include<sstream>
#include<string>
#include<algorithm>
#include "Vertex3.h"
GameObject::GameObject():rotation(3,3),position(0,0,0) {
	rotation = Matrix::xRotation(0) * Matrix::yRotation(0) * Matrix::zRotation(0);

}

const std::vector<Triangle3>& GameObject::GetShape() const {
	return shape;
}

Matrix GameObject::getRotation()const {
	return rotation;
}


Vector3 GameObject::getPosition()const {
	return position;
}

void GameObject::extrinsicRotate(Matrix rotation) {
	setRotation(rotation * this->rotation);
}

void GameObject::setRotation(Matrix rotation)
{
	this->rotation = rotation;
}

void GameObject::setPosition(Vector3 position)
{
	this->position = position;
}

void GameObject::rotate(Matrix rotation){
	this->rotation *= rotation;
}

void GameObject::move(Vector3 movement) {
	position += movement;
}


SDL_Surface* loadSurface(std::string path)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	return loadedSurface;
}

std::vector<std::string> seperateLine(std::string line, char seperatingChar) {
	std::stringstream test(line);
	std::string segment;
	std::vector<std::string> seglist;

	while (std::getline(test, segment, seperatingChar))
	{
		seglist.push_back(segment);
	}
	return seglist;
}

struct uvs {
	double u;
	double v;
	uvs(double u, double v) :u(u), v(v) {}
};

GameObject loadGameObject(std::string objectPath, std::string texturePath,double scale)
{
	SDL_Surface* texture = loadSurface(texturePath);
	//load object at specified path
	std::ifstream myfile(objectPath);
	GameObject loadedGO;
	std::vector<Vector3> objectVerteces;
	std::vector<uvs> objectuvs;
	std::vector<Vector3> objectNormals;
	std::string line;
	std::vector<std::string> seperatedLine;

	do
	{
		std::getline(myfile, line);
		seperatedLine = seperateLine(line, ' ');
	} while (seperatedLine[0] != "v");

	while (seperatedLine[0] == "v")
	{
		objectVerteces.push_back(Vector3(
			stod(seperatedLine[1]) * scale,
			stod(seperatedLine[2]) * scale,
			stod(seperatedLine[3]) * scale
		));
		getline(myfile, line);
		seperatedLine = seperateLine(line, ' ');
	}

	while (seperatedLine[0] != "vn") {
		getline(myfile, line);
		seperatedLine = seperateLine(line, ' ');
	}

	while (seperatedLine[0] == "vn")
	{
		objectNormals.push_back(Vector3(
			stod(seperatedLine[1]),
			stod(seperatedLine[2]),
			stod(seperatedLine[3])
		));
		getline(myfile, line);
		seperatedLine = seperateLine(line, ' ');
	}

	while (seperatedLine[0] != "vt") {
		getline(myfile, line);
		seperatedLine = seperateLine(line, ' ');
	}

	while (seperatedLine[0] == "vt")
	{
		objectuvs.push_back(uvs(
			stod(seperatedLine[1]),
			stod(seperatedLine[2])
		));
		getline(myfile, line);
		seperatedLine = seperateLine(line, ' ');
	}

	while (seperatedLine[0] != "f") {
		getline(myfile, line);
		seperatedLine = seperateLine(line, ' ');
	}

	std::vector<std::string> vertex1data;
	std::vector<std::string> vertex2data;
	std::vector<std::string> vertex3data;
	while (!seperatedLine.empty())
	{
		if (seperatedLine[0] == "s") {
			getline(myfile, line);
			seperatedLine = seperateLine(line, ' ');
			continue;
		};

		/*if (seperatedLine[0] == "usemtl") {
			texture = loadSurface(seperatedLine[1]+".bmp");

			getline(myfile, line);
			seperatedLine = seperateLine(line, ' ');
			continue;
		};*/
		vertex1data = seperateLine(seperatedLine[1], '/');
		vertex2data = seperateLine(seperatedLine[2], '/');
		vertex3data = seperateLine(seperatedLine[3], '/');
		loadedGO.shape.push_back(Triangle3(
			Vertex3(
				objectVerteces[stoi(vertex1data[0]) - 1],
				objectuvs[stoi(vertex1data[1]) - 1].u,
				1 - objectuvs[stoi(vertex1data[1]) - 1].v
			),
			Vertex3(
				objectVerteces[stoi(vertex2data[0]) - 1],
				objectuvs[stoi(vertex2data[1]) - 1].u,
				1 - objectuvs[stoi(vertex2data[1]) - 1].v
			),
			Vertex3(
				objectVerteces[stoi(vertex3data[0]) - 1],
				objectuvs[stoi(vertex3data[1]) - 1].u,
				1 - objectuvs[stoi(vertex3data[1]) - 1].v
			),
			Vector3(Vector3::crossProduct(objectVerteces[stoi(vertex2data[0]) - 1] - (objectVerteces[stoi(vertex1data[0]) - 1]), (objectVerteces[stoi(vertex3data[0]) - 1]) - (objectVerteces[stoi(vertex1data[0]) - 1]))),
			texture
		));


		getline(myfile, line);
		seperatedLine = seperateLine(line, ' ');
	}

	return loadedGO;
}
