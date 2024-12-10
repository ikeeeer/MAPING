#pragma once
#include "PuntDeInteresBotigaSolucio.h"
#include "PuntDeInteresRestaurantSolucio.h"
#include "PuntInteresAltres.h"
#include "CamiSolucio.h"
#include "MapaBase.h"
#include "Util.h"
class MapaSolucio:public MapaBase
{
public:
	MapaSolucio() {};
	void getPdis(std::vector<PuntDeInteresBase*>& v) override;
	void getCamins(std::vector<CamiBase*>& c) override;
	void buscarCamiCoord(std::vector<XmlElement>& xmlElements);
	bool existeixHighway(std::vector<CHILD_NODE> childNode);
	bool existeixId(const std::vector<std::string> v, const std::string id);
	bool buscarAtribut(std::vector<PAIR_ATTR_VALUE> attributes, std::string atrBuscat, std::string& valor);
	void borrarContigut();
	void parsejaXmlElements(std::vector<XmlElement>& xmlElements) override;
	std::vector<PuntDeInteresBase*> getPOV() const { return m_llistaDePunts; }
	std::vector<CamiBase*> getHighWay() const { return m_llistaCamins; }

private:
	std::vector<PuntDeInteresBase*> m_llistaDePunts;
	std::vector<CamiBase*> m_llistaCamins;
};

