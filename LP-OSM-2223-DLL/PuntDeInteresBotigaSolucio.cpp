#include "pch.h"
#include "PuntDeInteresBotigaSolucio.h"



unsigned int PuntDeInteresBotigaSolucio::getColor()
{

    if (m_shop == "supermarket")
    {
        //amarillo pudiento
        return 0xA5BE00;

    }

    if (m_shop == "tobacco")
    {
        //naranja debil
        return 0xFFAD69;

    }

    if (m_shop == "bakery")
    {
        std::size_t found = m_horari.find("06:00-22:00");
        if (found != std::string::npos && m_wheelchair == "yes")
        {
            //verde brillante
            return 0x4CB944;
        }

        //rojo fresa
        return 0xE85D75;
    }

    //carne humano 
    return 0xEFD6AC;


}
