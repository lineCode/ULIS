
/*************************************************************************
*
*   ULIS
*__________________
*
* ULIS.Interface.Conv.cpp
* Clement Berthaud - Layl
* Please refer to LICENSE.md
*/

#include "ULIS/Interface/ULIS.Interface.Transform.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"
#include "ULIS/Transform/ULIS.Transform.TransformContext.h"
#include "ULIS/Data/ULIS.Data.Block.h"

#include <glm/vec2.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ULIS {
/////////////////////////////////////////////////////
// FTransformContext
//--------------------------------------------------------------------------------------
//---------------------------------- Public API, static functions for matrix computation
//static
glm::mat3
FTransformContext::GetIdentityMatrix()
{
    return  glm::identity< glm::mat3 >();
}


//static
glm::mat3
FTransformContext::GetTranslationMatrix( float iX, float iY )
{
    return  glm::translate( GetIdentityMatrix(), glm::vec2( iX, iY ) );
}


//static
glm::mat3
FTransformContext::GetRotationMatrix( float iAngleRad )
{
    return  glm::rotate( GetIdentityMatrix(), iAngleRad );
}


//static
glm::mat3
FTransformContext::GetScaleMatrix( float iX, float iY )
{
    return  glm::scale( GetIdentityMatrix(), glm::vec2( iX, iY ) );
}
//static
glm::mat3
FTransformContext::GetShearMatrix( float iX, float iY )
{
    return  glm::shearY( glm::shearX( GetIdentityMatrix(), iX ), iY );
}


//--------------------------------------------------------------------------------------
//------------------------------------ Public API, static functions for image transforms
//static
IBlock*
FTransformContext::GetTransformed( const IBlock* iBlockSrc, const  glm::mat3& imat, const FPerfStrat& iPerfStrat )
{
    return  nullptr;
}

} // namespace ULIS

