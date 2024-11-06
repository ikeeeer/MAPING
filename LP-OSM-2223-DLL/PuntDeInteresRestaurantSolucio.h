#pragma once
#include "PuntDeInteresBase.h"

class PuntDeInteresRestaurantSolucio : public PuntDeInteresBase
{
public:
	PuntDeInteresRestaurantSolucio() :m_tipos(""), m_wheelchair("no") {};
	~PuntDeInteresRestaurantSolucio() {};
	PuntDeInteresRestaurantSolucio(Coordinate coord, std::string name,const std::string tipos, const std::string wheelchair) :
		m_tipos(tipos), m_wheelchair(wheelchair), PuntDeInteresBase(coord, name) {};


	unsigned int getColor() override;
private:
	std::string m_tipos;
	std::string m_wheelchair;
};

