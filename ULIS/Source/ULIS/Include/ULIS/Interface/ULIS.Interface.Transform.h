
/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Transform.h
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#pragma once

#include "ULIS/Base/ULIS.Base.BaseTypes.h"
#include "ULIS/Base/ULIS.Base.PerfStrat.h"

#include <glm/matrix.hpp>

namespace ULIS { class IBlock; }

namespace ULIS {
/////////////////////////////////////////////////////
// FTransformContext
class FTransformContext
{

public:
    // Public API, static functions for matrix computation
    static glm::mat3 GetIdentityMatrix();
    static glm::mat3 GetTranslationMatrix( float iX, float iY );
    static glm::mat3 GetRotationMatrix( float iAngleRad );
    static glm::mat3 GetScaleMatrix( float iX, float iY );
    static glm::mat3 GetShearMatrix( float iX, float iY );

public:
    // Public API, static functions for image transforms
    static IBlock* GetTransformed( const IBlock* iBlockSrc, const  glm::mat3& imat, const FPerfStrat& iPerfStrat = FPerfStrat() );
};

} // namespace ULIS

