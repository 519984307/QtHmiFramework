#ifndef CFREQTABLE_H
#define CFREQTABLE_H

#include <stdint.h>
#include <map>
#include "CommonDefine.h"

BEGIN_NAMESPACE(HmiNgin)
class CFreqTable
{
public:
    CFreqTable();
    void append(uint32_t, int);
    void increase(uint32_t);
    void reduce(uint32_t);
    int get(uint32_t);

private:
    std::map<uint32_t, int> m_view_history;
};

END_NAMESPACE

#endif // CFREQTABLE_H
