/**
*
*   ULIS
*__________________
*
* @file     Application.Widgets.Graph.h
* @author   Clement Berthaud
* @brief    This file provides the declaration for the SGraph class.
*/
#pragma once

#include <QWidget>

namespace  nApplication { namespace  nWidgets { class SGraphView; } }
namespace  nApplication { namespace  nWidgets { class SGraphScene; } }

namespace  nApplication {
namespace  nWidgets {


class SGraph : public QWidget
{
    Q_OBJECT

    typedef  QWidget    tSuperClass;
    typedef  SGraph      tSelf;

public:
    // Construction / Destruction
    virtual  ~SGraph();
    SGraph( QWidget* iParent = NULL );

protected:
    // Event
    virtual  void  resizeEvent( QResizeEvent*   event )  override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    // Private Data Members
    SGraphView*     mView;
    SGraphScene*    mScene;

};


} // namespace  nWidgets
} // namespace  nApplication
