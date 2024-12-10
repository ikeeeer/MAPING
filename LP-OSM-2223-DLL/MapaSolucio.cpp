#include "pch.h"
#include "MapaSolucio.h"

void MapaSolucio::parsejaXmlElements(std::vector<XmlElement>& xmlElements)
{
	int contador = 0;
	int posicionXmlElement= 1;
	borrarContigut();
	//iteramos vector
	for (std::vector<XmlElement>::iterator it = xmlElements.begin(); it!= xmlElements.end(); it++)
	{

		//comprovamos que es un node
		if (it->id_element == "node")
		{
			Coordinate a;
			a.lat = 0;
			a.lon = 0;
			//guardamos la coordenadas
			std::string valor = "";
			buscarAtribut(it->atributs, "lat", valor);
			a.lat = stod(valor);
			buscarAtribut(it->atributs, "lon", valor);
			a.lon = stod(valor);

			//iteramos sobre los hijos para extraer otras información
			std::string name = "";
			std::string name2 = "";
			std::string cuisine = "";
			std::string tipus = "";
			std::string horari = "";
			std::string wheelchair = "";
			std::string amenity = "";
			for (int i = 0; i < it->fills.size(); i++)
			{
				
				//avaluem si son tags
				if (it->fills[i].first == "tag")
				{
					std::pair<std::string, std::string>valorTag = Util::kvDeTag(it->fills[i].second);
					
					if (valorTag.first == "amenity")
					{
						amenity = valorTag.second;
					}

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

			if (tipus == "shop" && name!="")
			{
				m_llistaDePunts.push_back(new PuntDeInteresBotigaSolucio(a, name, name2, horari, wheelchair));
			}
			else if (amenity != "" && name != "")
			{
				if (tipus == "cuisine")
				{
					m_llistaDePunts.push_back(new PuntDeInteresRestaurantSolucio(a, name, cuisine, wheelchair));

				}
				else {
					m_llistaDePunts.push_back(new PuntInteresAltres(a, name, amenity));
				}
			}

		
		}

		// comprovem que la dada sigui way
		if (it->id_element == "way")
		{
			//funció que busca si existeix el tag highway
			if (existeixHighway(it->fills))
			{
				//creamos un nuevo camino
				m_llistaCamins.push_back(new CamiSolucio());
				//guardamos los id de los nodos
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
				//cuenta cuantas clase CamiSolucio hemos creado
				contador++;

			}
		}
	}

	buscarCamiCoord(xmlElements);

}

void MapaSolucio::getPdis(std::vector<PuntDeInteresBase*>& pdis)
{
	
	for (auto& it : m_llistaDePunts)
	{
		pdis.push_back(it);
	}
}

void MapaSolucio::getCamins(std::vector<CamiBase*>& camins)
{
	for (auto& it : m_llistaCamins)
	{
		camins.push_back(it);
	}
}

//busca el atributo indicado por atrBuscat y nos devuelve el valor en valor además la función devolvera un bool de si ha encontrado el valor
bool MapaSolucio::buscarAtribut(std::vector<PAIR_ATTR_VALUE> attributes, std::string atrBuscat, std::string& valor)
{

	bool trobat = false;
	int i = 0;
	while (i < attributes.size() && !trobat)
	{
		if (attributes[i].first == atrBuscat)
		{
			trobat = true;
			valor = attributes[i].second;
		}
		else {
			i++;
		}
	}

	return trobat;
}

void MapaSolucio::borrarContigut()
{
	m_llistaCamins.clear();
	m_llistaDePunts.clear();
}

// nos da el rango donde buscar 
void MapaSolucio::buscarCamiCoord(std::vector<XmlElement>& xmlElements)
{
	for (int i = 0; i < m_llistaCamins.size(); i++)
	{
		std::vector<std::string> listaIdNode = m_llistaCamins[i]->getVector();
		for (int j = 0; j < listaIdNode.size(); j++)
		{
			std::vector<XmlElement>::iterator it = xmlElements.begin();
			bool trobat = false;

			while (it != xmlElements.end() && !trobat)
			{
				std::string valor = "";

				if (it->id_element == "node" && buscarAtribut(it->atributs, "id", valor) && (listaIdNode[j] == valor))
				{
					Coordinate c;
					c.lat = 0;
					c.lon = 0;
					buscarAtribut(it->atributs, "lat", valor);
					c.lat = stod(valor);
					buscarAtribut(it->atributs, "lon", valor);
					c.lon = stod(valor);
					m_llistaCamins[i]->afegirCoordinada(c);

					trobat = true;	
					
				}
				else {
					it++;
				}
			}
		}
	}
	/*
		for (std::vector<XmlElement>::iterator it = xmlElements.begin(); it != xmlElements.end(); it++)
		{


					int j = 0;

					while (j < listaIdNode.size() && !trobat)
					{
						if (listaIdNode[j] == valor)
						{
							trobat = true;
						}
						else {
							j++;
						}
					}

					if (trobat)
					{

					}

				}


			}

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