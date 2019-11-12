/**
*
*   ULIS
*__________________
*
* @file     Application.Window.MainWindow.h
* @author   Clement Berthaud
* @brief    This file provides the declaration for the SMainWindow class.
*/
#pragma once

#include <QWidget>

namespace  nApplication { namespace  nWidgets { class SCanvas; } }
namespace  nApplication { namespace  nWidgets { class SSlider; } }
namespace  nApplication { namespace  nWidgets { class SGraph; } }
class QScrollArea;

namespace  nApplication {
namespace  nWindow {


class SMainWindow : public QWidget
{
    Q_OBJECT

    typedef  QWidget        tSuperClass;
    typedef  SMainWindow    tSelf;

public:
    // Construction / Destruction
    virtual  ~SMainWindow();
    SMainWindow( QWidget* iParent = nullptr );

protected:
    // Protected Qt event overrides
    virtual  void  resizeEvent( QResizeEvent*  event )  override;

private:
    // GUI utilities
    void  Init();
    void  Compose();
    void  Destroy();

private:
    // Private data members
    QScrollArea* mScrollArea;
    QWidget* mWrapper;
    QWidget* mCanvasWrapper;
    QWidget* mAnalyticsWrapper;
    nApplication::nWidgets::SCanvas* mCanvasA;
    nApplication::nWidgets::SCanvas* mCanvasB;
    nApplication::nWidgets::SGraph* mGraphA;
    nApplication::nWidgets::SGraph* mGraphB;
};


} // namespace  nWindow
} // namespace  nApplication

