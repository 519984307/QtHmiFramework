#include "CFreqTable.h"

CFreqTable::CFreqTable()
{

}

void CFreqTable::append(uint32_t key, int val)
{
    m_view_history.insert(std::pair<uint32_t, int>(key, val));
}

void CFreqTable::increase(uint32_t key)
{
    m_view_history[key]++;
}

void CFreqTable::reduce(uint32_t key)
{
    m_view_history[key]--;
    if(m_view_history[key] < 1) m_view_history[key] = 0;
}


