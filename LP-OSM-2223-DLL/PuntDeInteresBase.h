#pragma once

#include <string>
#include "Common.h"

static unsigned int COLOR_PISTACHO = 0xA5BE00;
static unsigned int COLOR_NARANJA = 0xFFAD69;
static unsigned int COLOR_ROJO = 0xE85D75;
static unsigned int COLOR_VERDE = 0x4CB944;
static unsigned int COLOR_DEFECTE = 0xEFD6AC;
static unsigned int COLOR_TURQUESA = 0x03FCBA;
static unsigned int COLOR_AZUL = 0xA6D9F7;
static unsigned int COLOR_PURPURA = 0x251351;

class PuntDeInteresBase {

	private:
		Coordinate m_coord;
		std::string m_name;

	public:		
		PuntDeInteresBase();
		PuntDeInteresBase(Coordinate coord, std::string name);

		virtual std::string getName();
		Coordinate getCoord();
		virtual unsigned int getColor();

};