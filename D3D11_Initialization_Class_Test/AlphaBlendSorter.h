#include <vector>
#include "VertexTypes.h"
#include <DirectXMath.h>

class AlphaBlendSorter{

public:

	std::vector<VertexTypes::VertexBasic> vertices;
	AlphaBlendSorter(std::vector<VertexTypes::VertexBasic> vertices);
	AlphaBlendSorter(){};
	void sortVertices(std::vector<VertexTypes::VertexBasic>& vertices, const DirectX::XMFLOAT4X4 &World,
		const DirectX::XMFLOAT4X4 &View, const DirectX::XMFLOAT4X4 &Projection);
};