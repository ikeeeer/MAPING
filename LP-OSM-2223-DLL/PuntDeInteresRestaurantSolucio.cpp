#include "pch.h"
#include "PuntDeInteresRestaurantSolucio.h"


unsigned int PuntDeInteresRestaurantSolucio::getColor()
{

    if (m_tipos == "chinese")
    {
        return 0xA6D9F7;
    }

    if (m_wheelchair == "yes")
    {

        if (m_tipos == "pizza")
        {
            return 0x03FCBA;
        }
        else {
            return 0x251351;
        }
    }


    return 0x0000FF;

}
