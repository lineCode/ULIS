/**
*
*   ULIS
*__________________
*
* @file     Application.Widgets.GraphScene.h
* @author   Clement Berthaud
* @brief    This file provides the declaration for the SGraphScene class.
*/
#pragma once

#include <QGraphicsScene>

namespace  nApplication {
namespace  nWidgets {


class SGraphScene : public QGraphicsScene
{
    Q_OBJECT

    typedef  QGraphicsScene tSuperClass;
    typedef  SGraphScene    tSelf;

public:
    // Construction / Destruction
    virtual  ~SGraphScene();
    SGraphScene( QObject* iParent = NULL );

};


} // namespace  nWidgets
} // namespace  nApplication

