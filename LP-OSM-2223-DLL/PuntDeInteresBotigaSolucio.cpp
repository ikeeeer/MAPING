#include "pch.h"
#include "PuntDeInteresBotigaSolucio.h"


unsigned int PuntDeInteresBotigaSolucio::getColor()
{
    
    if (m_shop == "supermarket")
    {
        //amarillo pudiento
        return COLOR_PISTACHO;

    }

    if (m_shop == "tobacco")
    {
        //naranja debil
        return COLOR_NARANJA;

    }

    if (m_shop == "bakery")
    {
        std::size_t found = m_horari.find("06:00-22:00");
        if (found!=std::string::npos && m_wheelchair == "yes")
        {
            //verde brillante
            return COLOR_VERDE;
        }

        //rojo fresa
        return COLOR_ROJO;
    }

    //carne humano 
    return COLOR_DEFECTE;
    

}
