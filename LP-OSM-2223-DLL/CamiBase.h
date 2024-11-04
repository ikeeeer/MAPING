#pragma once

#include "Common.h"
#include <vector>

class CamiBase {
	public:
		CamiBase() {};
		~CamiBase() {};
		virtual void afegirCoordinada(const Coordinate &c)=0;
		virtual void afegirIdNode(const std::string& node)=0;
		virtual int getSize() = 0;
		virtual std::vector<std::string> getVector() = 0;
		virtual std::vector<Coordinate> getCamiCoords() = 0;
};

