#pragma once
#include "PuntDeInteresBase.h"
class PuntDeInteresBotigaSolucio :public PuntDeInteresBase
{
public:
	PuntDeInteresBotigaSolucio() : m_shop(""), m_horari(""), m_wheelchair("no") {};
	PuntDeInteresBotigaSolucio(Coordinate coord, std::string name,const std::string shop, const std::string horari, const std::string wheelchair) :
		m_shop(shop), m_horari(horari), m_wheelchair(wheelchair),PuntDeInteresBase(coord,name) {};

	~PuntDeInteresBotigaSolucio() {};
	unsigned int getColor() override;

private:
	std::string m_shop;
	std::string m_horari;
	std::string m_wheelchair;
};

