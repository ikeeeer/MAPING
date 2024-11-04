#pragma once
#include"CamiBase.h"

class CamiSolucio:public CamiBase
{
public:
	CamiSolucio(): CamiBase() {};
	~CamiSolucio() {};
	void afegirCoordinada(const Coordinate& c) override { m_llistaCoordenades.push_back(c); };
	void afegirIdNode(const std::string& node) override { m_llistaDeNodes.push_back(node); };
	int getSize() override { 
		girarVector();
		return m_llistaDeNodes.size(); 
	};
	std::vector<std::string> getVector() override { return m_llistaDeNodes; };
	void girarVector();

	 std::vector<Coordinate> getCamiCoords() override;

private:
	std::vector<std::string>m_llistaDeNodes;
	std::vector<Coordinate> m_llistaCoordenades;
};

