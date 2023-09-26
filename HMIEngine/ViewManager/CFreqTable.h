#ifndef CFREQTABLE_H
#define CFREQTABLE_H

#include <stdint.h>
#include <map>

class CFreqTable
{
public:
    static CFreqTable *instance();

    void append(uint32_t, int);
    void increase(uint32_t);
    void reduce(uint32_t);

private:
    CFreqTable();
    static CFreqTable *s_instance;

private:
    std::map<uint32_t, int>   m_view_history;

};

#endif // CFREQTABLE_H
