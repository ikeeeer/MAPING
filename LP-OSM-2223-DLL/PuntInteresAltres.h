#pragma once
#include "PuntDeInteresBase.h"

class PuntInteresAltres: public PuntDeInteresBase
{
public:
	PuntInteresAltres() :m_amenity("") { };
	PuntInteresAltres(Coordinate coord, std::string name, std::string amenity) : PuntDeInteresBase(coord, name), m_amenity(amenity) {};
private:
	std::string m_amenity;
};

