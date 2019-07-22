/*************************************************************************
*
*   ULIS
*__________________
*
* Vignette.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include <QWidget>

namespace ULIS { class IBlock; }
class cVignette;

/////////////////////////////////////////////////////
// cTriVignette
class cTriVignette : public QWidget
{
    Q_OBJECT

    typedef QWidget     tSuperClass;
    typedef cTriVignette   tSelf;

public:
    // Construction / Destruction
    cTriVignette( ::ULIS::IBlock* iSurface, ::ULIS::IBlock* iComp, QWidget* iParent = nullptr );
    ~cTriVignette();

protected:
    // Protected Qt event overrides
    virtual void resizeEvent(QResizeEvent *event) override;

private:
    // GUI utilities
    void  Init();
    void  Build();
    void  Compose();
    void  Destroy();

private:
    ::ULIS::IBlock* mSurface;
    ::ULIS::IBlock* mComp;
    cVignette* mUlisVignette;
    cVignette* mPsVignette;
    cVignette* mDiffVignette;
};

