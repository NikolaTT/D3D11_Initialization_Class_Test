#include "ObjModelParser.h"
#include <DirectXMath.h>

using namespace DirectX;
using std::stoi;

void ObjModelParser::parseFaceVertex(std::string input, std::vector<UINT>& faceVertices,
	std::vector<UINT>& faceUV, std::vector<UINT>& faceNormals){
	
	int k = 0;
	int p = 0;

	std::string subString;

	//std::ofstream output("parseFaceVertex.txt");
	//output << "Begin\n";

	while (input[k] != '/' && k != input.length()){
		k++;
	}

	subString = input.substr(p, k - p);
	//output << k << " " << subString << 's\n';
	k++;
	p = k;

	faceVertices.push_back(std::stoi(subString));


	while (input[k] != '/' && k != input.length()){
		k++;
	}

	subString = input.substr(p, k - p);
	k++;
	p = k;

	faceUV.push_back(std::stoi(subString));



	while (input[k] != '/' && k != input.length()){
		k++;
	}

	subString = input.substr(p, k - p);
	
	faceNormals.push_back(std::stoi(subString));
}

void ObjModelParser::parseFaces(std::string input, std::vector<UINT>& faceVertices, 
	std::vector<UINT>& faceUV, std::vector<UINT>& faceNormals){

	std::string currentSubstring;
	
	int i = 0;
	int j = 0;

	while (input[j] != ' ' && j != input.length()){
		j++;
	}

	currentSubstring = input.substr(i, j - i);
	j++;
	i = j;

	parseFaceVertex(currentSubstring, faceVertices, faceUV, faceNormals);

	while (input[j] != ' ' && j != input.length()){
		j++;
	}

	currentSubstring = input.substr(i, j - i);
	j++;
	i = j;

	parseFaceVertex(currentSubstring, faceVertices, faceUV, faceNormals);

	while (input[j] != ' ' && j != input.length()){
		j++;
	}

	currentSubstring = input.substr(i, j - i);
	parseFaceVertex(currentSubstring, faceVertices, faceUV, faceNormals);
}

bool ObjModelParser::LoadObj(Object& object){

	std::ifstream fin(object.fileName);
	std::ofstream fout("debugLoadingObj.txt");

	//UINT numMaterials = 0;
	UINT numVertices = 0;
	UINT numTriangles = 0;
	UINT numIndices = 0;
	//UINT numBones = 0;
	//UINT numAnimationClips = 0;

	delete object.indices;
	object.indices = new USHORT[numIndices];

	std::string ignore;

	int end = fin.end;
	fin.beg;

	int addPos = 0;

	if (fin)
	{
		//get name of object
		std::getline(fin, ignore);
		object.objectName = ignore.substr(5, ignore.size());
		//get object rendering technique
		std::getline(fin, ignore);
		object.techniqueName = ignore.substr(10, ignore.size());
		//get object vertex count;
		std:getline(fin, ignore);
		numVertices = stoi(ignore.substr(16, ignore.size()));
		//get object index count
		std::getline(fin, ignore);
		numIndices = stoi(ignore.substr(15, ignore.size()));
		
		for (int i = 0; i < numVertices; i++){
			VertexTypes::VertexBasic tempVB;
			
			fin >> tempVB.Pos.x;
			fin >> tempVB.Pos.y;
			fin >> tempVB.Pos.z;
			tempVB.Pos.w = 1.00f;

			fin >> tempVB.Normal.x;
			fin >> tempVB.Normal.y;
			fin >> tempVB.Normal.z;

			fin >> tempVB.Tex.x;
			fin >> tempVB.Tex.y;			
		}

		for (int i = 0; i < numIndices; i++){
			fin >> object.indices[i];
		}
		
		
		/*while (std::getline(fin, ignore)){
			
			
			int i = 0;
			if (ignore[i] == 'v'){
				i++;
				if (ignore[i] == 't'){

					i += 2;
					int j = i;
					XMFLOAT2 UV2;

					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}

					std::string numF = ignore.substr(i, j - i);
					UV2.x = std::stof(numF);
					j++;
					i = j;

					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}

					std::ofstream truck("truck.txt", std::ios_base::app);
					truck << "File name : " << object.fileName << "\n";
					truck << "ignore: " << ignore << '\n';
					truck << "NumF : " << numF << "   " <<  i << "  " << j << "\n";
					truck.close();

					numF = ignore.substr(i, j - i);
					UV2.y = std::stof(numF);
					UV.push_back(UV2);
				}
				else if (ignore[i] == 'n'){

					i += 2;
					int j = i;
					XMFLOAT3 normal2;

					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}

					std::string numF = ignore.substr(i, j - i);
					normal2.x = std::stof(numF);
					j++;
					i = j;

					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}

					numF = ignore.substr(i, j - i);
					normal2.y = std::stof(numF);
					j++;
					i = j;

					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}

					numF = ignore.substr(i, j - i);
					normal2.z = std::stof(numF);
					normals.push_back(normal2);
				}
				else{

					i++;
					int j = i;
					XMFLOAT4 vertex;
					vertex.w = 1.0f;

					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}

					std::string numF = ignore.substr(i, j - i);
					vertex.x = std::stof(numF);

					j++;
					i = j;

					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}

					numF = ignore.substr(i, j - i);
					vertex.y = std::stof(numF);
					j++;
					i = j;

					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}

					numF = ignore.substr(i, j - i);
					vertex.z = std::stof(numF);
					vertices.push_back(vertex);

				}
			}
			else if (ignore[i] == 'f'){
				i += 2;
				parseFaces(ignore.substr(i, ignore.length()), faceVertices, faceUV, faceNormals);
			}
		}*/

		/*for (int i = 0; i < faceVertices.size(); i++){
			VertexTypes::VertexBasic V;
			V.Pos = vertices.at(faceVertices[i] - 1);
			V.Tex = UV.at(faceUV[i] - 1);
			V.Normal = normals.at(faceNormals[i] - 1);
			V.Tangent = XMFLOAT3(1.0f, 1.0f, 1.0f);
			V.DisplacementTex = UV.at(faceUV[i] - 1);
			object.vertices.push_back(V);
		}*/

		for (int i = 0; i < object.vertices.size(); i++){
			fout << '\n' << i << ": " << object.vertices[i].Pos.x << " " << object.vertices[i].Pos.y << " " << object.vertices[i].Pos.z << '\n';
		}

		return true;
	}
	return false;




}

bool ObjModelParser::LoadObj(const std::string& filename,
	std::vector<VertexTypes::VertexBasic>& verticesFunc,
	std::vector<USHORT>& indices){
	
	std::ifstream fin(filename);
	std::ofstream fout("debugLoadingObj.txt");

	//UINT numMaterials = 0;
	UINT numVertices = 0;
	UINT numTriangles = 0;
	//UINT numBones = 0;
	//UINT numAnimationClips = 0;

	std::string ignore;

	int end = fin.end;
	fin.beg;

	int addPos = 0;

	if (fin)
	{
		/*fin >> ignore; // file header text
		fin >> ignore >> numMaterials;
		fin >> ignore >> numVertices;
		fin >> ignore >> numTriangles;
		fin >> ignore >> numBones;
		fin >> ignore >> numAnimationClips;*/

		std::getline(fin, ignore);
		std::getline(fin, ignore);
		std::getline(fin, ignore);
		std::getline(fin, ignore);

		std::vector<XMFLOAT4> vertices;
		std::vector<XMFLOAT2> UV;
		std::vector<XMFLOAT3> normals;
		std::vector<UINT> faceVertices;
		std::vector<UINT> faceUV;
		std::vector<UINT> faceNormals;

		while (std::getline(fin, ignore)){
			int i = 0;
			if (ignore[i] == 'v'){
				i++;
				if (ignore[i] == 't'){
					
					i += 2;
					int j = i;
					XMFLOAT2 UV2;
					
					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}
					
					std::string numF = ignore.substr(i, j - i);
					UV2.x = std::stof(numF);
					j++;
					i = j;
					
					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}
					
					numF = ignore.substr(i, j - i);
					UV2.y = std::stof(numF);
					UV.push_back(UV2);
				}
				else if (ignore[i] == 'n'){
					
					i += 2;
					int j = i;
					XMFLOAT3 normal2;
					
					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}
					
					std::string numF = ignore.substr(i, j - i);
					normal2.x = std::stof(numF);
					j++;
					i = j;
					
					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}
					
					numF = ignore.substr(i, j - i);
					normal2.y = std::stof(numF);
					j++;
					i = j;
					
					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}
					
					numF = ignore.substr(i, j - i);
					normal2.z = std::stof(numF);
					normals.push_back(normal2);
				}
				else{
					
					i++;
					int j = i;
					XMFLOAT4 vertex;
					vertex.w = 1.0f;
					
					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}
					
					std::string numF = ignore.substr(i, j-i);
					vertex.x = std::stof(numF);
					
					j++;
					i = j;
					
					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}
					
					numF = ignore.substr(i, j-i);
					vertex.y = std::stof(numF);
					j++;
					i = j;
					
					while (ignore[j] != ' ' && j != ignore.length()){
						j++;
					}
					
					numF = ignore.substr(i, j-i);
					vertex.z = std::stof(numF);
					vertices.push_back(vertex);

				}
			}
			else if (ignore[i] == 'f'){
				i += 2;
				parseFaces(ignore.substr(i, ignore.length()), faceVertices, faceUV, faceNormals);
			}
		}
		
		for (int i = 0; i < faceVertices.size(); i++){
			VertexTypes::VertexBasic V;
			V.Pos = vertices.at(faceVertices[i]-1);
			V.Tex = UV.at(faceUV[i]-1);
			V.Normal = normals.at(faceNormals[i]-1);
			V.Tangent = XMFLOAT3(1.0f, 1.0f, 1.0f);
			V.DisplacementTex = UV.at(faceUV[i] - 1);
			verticesFunc.push_back(V);
		}

		for(int i = 0; i < verticesFunc.size(); i++){
			fout << '\n' << i << ": " << verticesFunc[i].Pos.x << " " << verticesFunc[i].Pos.y << " " << verticesFunc[i].Pos.z << '\n';
		}

		return true;
	}
	return false;




}