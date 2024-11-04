#include "pch.h"
#include "MapaSolucio.h"

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements)
{
	int contador = 0;
	int posicionXmlElement= 1;
	//iteramos vector
	for (std::vector<XmlElement>::iterator it = xmlElements.begin(); it!= xmlElements.end(); it++)
	{

		//comprovamos que es un node
		if (it->id_element == "node")
		{
			Coordinate a;
			a.lat = 0;
			a.lon = 0;

			//iteramos dentro de los atributos nodes para coordenadas 
			for (int i = 0; i < it->atributs.size(); i++)
			{

				if (it->atributs[i].first == "lat")
				{
					a.lat = stod(it->atributs[i].second);
				}
				if (it->atributs[i].first == "lon")
				{
					a.lon = stod(it->atributs[i].second);
				}
			}

			//iteramos sobre los hijos para extraer otras información
			std::string name = "";
			std::string name2 = "";
			std::string cuisine = "";
			std::string tipus = "";
			std::string horari = "";
			std::string wheelchair = "";
			for (int i = 0; i < it->fills.size(); i++)
			{
				
				//avaluem si son tags
				if (it->fills[i].first == "tag")
				{
					std::pair<std::string, std::string>valorTag = Util::kvDeTag(it->fills[i].second);
					
					if (valorTag.first == "name")
					{
						name = valorTag.second;

					}

					if (valorTag.first == "shop")
					{
						tipus = "shop";
						name2 = valorTag.second;
					}

					if (valorTag.first == "cuisine")
					{
						tipus = "cuisine";
						cuisine = valorTag.second;
					}

					if (valorTag.first == "opening_hours")
					{
						horari = valorTag.second;

					}

					if (valorTag.first == "wheelchair")
					{
						wheelchair = valorTag.second;

					}

				}
			}

			if (tipus == "shop")
			{
				m_llistaDePunts.push_back(new PuntDeInteresBotigaSolucio(a, name, name2, horari, wheelchair));
			}

			if (tipus == "cuisine")
			{
				m_llistaDePunts.push_back(new PuntDeInteresRestaurantSolucio(a, name, cuisine, wheelchair));

			}

		}

		// comprovem que la dada sigui way
		if (it->id_element == "way")
		{
			//funció que busca si existeix el tag highway
			if (existeixHighway(it->fills))
			{
				m_llistaCamins.push_back(new CamiSolucio());
				for (int i = 0; i < it->fills.size(); i++)
				{
					if (it->fills[i].first == "nd") {
						// Emmagatzemem el valor d’aquest tag
						std::vector<std::pair<std::string, std::string>>::iterator valorTag = it->fills[i].second.begin();

						//guardem el valor per després buscar les coordenades
						if (valorTag->first == "ref") {
							// en el futuro mirar parchecito
							//guardamos los id
							m_llistaCamins[contador]->afegirIdNode(valorTag->second);
							
						}
					}
				}
				//ahora buscara los nodos que contiene las coordenadas y lo guardada dentro de camiSolucio
				buscarCamiCoord(xmlElements,contador,posicionXmlElement);
				//cuenta cuantas clase CamiSolucio hemos creado
				contador++;

			}
		}
		posicionXmlElement++;
	}
}

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis)
{
	pdis = m_llistaDePunts;
	

}

void MapaSolucio::getCamins(std::vector<CamiBase*>& camins)
{
	camins = m_llistaCamins;
}

// nos da el rango donde buscar 
void MapaSolucio::buscarCamiCoord(std::vector<XmlElement>& xmlElements, int posicion,int posXMLMax)
{
	std::vector<std::string> listaIdNode = m_llistaCamins[posicion]->getVector();
	std::vector<XmlElement>::iterator it = xmlElements.begin();
	for (int i = 0; i < listaIdNode.size(); i++)
	{
		bool trobat = false;

		while (it != xmlElements.end() && !trobat)
		{
			if (it->id_element == "node")
			{
				Coordinate c;
				c.lat = 0;
				c.lon = 0;

				for (int j = 0; j < it->atributs.size(); j++)
				{
					if (it->atributs[j].first == "id")
					{
						if (listaIdNode[i] == it->atributs[j].second)
						{
							trobat = true;
						}
						//trobat = existeixId(listaIdNode, it->atributs[j].second);

					}

					if (it->atributs[j].first == "lat")
					{
						c.lat = stod(it->atributs[j].second);
					}
					if (it->atributs[j].first == "lon")
					{
						c.lon = stod(it->atributs[j].second);
					}

				}

				if (trobat == true)
				{
					m_llistaCamins[posicion]->afegirCoordinada(c);
				}
			}
			it++;
		}

	}
	/*
	for (int i=0; i < posXMLMax; i++)
	{

		bool trobat = false;
		Coordinate c;
		c.lat = 0;
		c.lon = 0;
		if (it->id_element == "node")
		{
			

			if (trobat == true)
			{
				m_llistaCamins[posicion]->afegirCoordinada(c);
			}
		}
		it++;
	}
	*/
}

bool MapaSolucio::existeixId(const std::vector<std::string> v, const std::string id)
{
	int i = 0;
	bool existeix = false;
	while ((i < v.size()) && !existeix)
	{
		if (id == v[i])
		{
			existeix = true;
		}
		else
		{
			i++;
		}
	}
	return existeix;
}

bool MapaSolucio::existeixHighway(std::vector<CHILD_NODE> childNode)
{
	bool existeixHigh = false;

	for (int i = 0; i<childNode.size();i++)
	{
		if (childNode[i].first == "tag") {
			// Emmagatzemem el valor d’aquest tag
			std::pair<std::string, std::string> valorTag =
				Util::kvDeTag(childNode[i].second);
			// Comprovem que es el tag que busquem
			if (valorTag.first == "highway") {
				existeixHigh = true;
			}
		}
	}

	return existeixHigh;
}