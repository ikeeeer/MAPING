#include "pch.h"
#include "PuntDeInteresRestaurantSolucio.h"

std::string PuntDeInteresRestaurantSolucio::getName()
{
    return m_tipos;
}

unsigned int PuntDeInteresRestaurantSolucio::getColor()
{
    
    if (m_wheelchair == "yes")
    {

        if (m_tipos == "pizza")
        {
            return COLOR_TURQUESA;
        }
        else {
            return COLOR_PURPURA;
        }
    }
    if (m_tipos == "chinese")
    {
        return COLOR_AZUL;
    }
        
    return COLOR_DEFECTE;
    
}
