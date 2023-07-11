#ifndef COMMONSTRUCTS_H
#define COMMONSTRUCTS_H

#include <QtGlobal>
#include <cstdint>
#include <QString>
#include <vector>
#include "CommonEnums.h"


/**
 * @brief The S_VIEW_EVENT class
 *
 *  uchar                       event;
 *  void                        (*fn)();
 *  uint32_t                    dest_screen;
 */
struct S_VIEW_EVENT
{
    uint32_t                    view;
    uchar                       event;
    void                        (*fn)();
    uint32_t                    destination;
};

/**
 * @brief The S_VIEW_INFORMATION class
 *
 *  uint32_t                    id;
 *  void                        (*fnEntry)();
 *  std::vector<S_VIEW_EVENT>   events;
 *  void                        (*fnExit)();
 *  E_DURATION                  duration{E_DURATION::NONE};
 *  E_VIEW_TYPE                 type{E_VIEW_TYPE::SCREEN_TYPE};
 *  QString                     path;
 */
struct S_VIEW_INFORMATION
{
    uint32_t                    id;
    void                        (*fnEntry)();
    void                        (*fnExit)();
    E_DURATION                  duration{E_DURATION::NONE};
    E_VIEW_TYPE                 type{E_VIEW_TYPE::SCREEN_TYPE};
    QString                     path;
};

#endif // COMMONSTRUCTS_H
