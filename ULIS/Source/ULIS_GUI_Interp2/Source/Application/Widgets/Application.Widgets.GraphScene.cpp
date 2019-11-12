/**
*
*   ULIS
*__________________
*
* @file     Application.Widgets.GraphScene.cpp
* @author   Clement Berthaud
* @brief    This file provides the definition for the SGraphScene class.
*/

#include "Application/Widgets/Application.Widgets.GraphScene.h"

namespace  nApplication {
namespace  nWidgets {


//--------------------------------------------------------------------------------------
//----------------------------------------------------------- Construction / Destruction


SGraphScene::~SGraphScene()
{
}


SGraphScene::SGraphScene( QObject* iParent ) :
    tSuperClass( iParent )
{
    setObjectName( "SGraphScene" );
}


} // namespace  nWidgets
} // namespace  nApplication

