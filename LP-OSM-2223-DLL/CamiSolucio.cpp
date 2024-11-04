#include "pch.h"
#include "CamiSolucio.h"

void CamiSolucio::girarVector()
{
    int n = m_llistaDeNodes.size();
    for (int i = 0; i < n / 2; ++i) {
        std::swap(m_llistaDeNodes[i], m_llistaDeNodes[n - i - 1]);
    }
}

std::vector<Coordinate> CamiSolucio::getCamiCoords()
{
    return m_llistaCoordenades;
}

