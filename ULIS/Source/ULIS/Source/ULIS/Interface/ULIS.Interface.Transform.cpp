/**
*
*   ULIS
*__________________
*
* @file     ULIS.Interface.Transform.cpp
* @author   Clement Berthaud
* @brief    This file provides the definitions for the FTransformContext class.
*/
#include "ULIS/Interface/ULIS.Interface.Transform.h"
#include "ULIS/Interface/ULIS.Interface.Decl.h"
#include "ULIS/Data/ULIS.Data.Block.h"
#include "ULIS/Transform/ULIS.Transform.TransformContext.h"
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/vec2.hpp>

namespace ULIS {
/////////////////////////////////////////////////////
// FTransformContext
//--------------------------------------------------------------------------------------
//------------------------------------------------------------- Public Static Matrix API
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
//-------------------------------------------------------------------- Public Static API
//static
IBlock*
FTransformContext::GetTransformed( const IBlock* iBlockSrc
                                 , const  glm::mat3& iMat
                                 , const FPerformanceOptions& iPerformanceOptions )
{
    switch( iBlockSrc->Id() )
    {
        #define ULIS_REG_SWITCH_OP( z, n, data )                                                                                            \
            case ULIS_REG[ n ]:                                                                                                             \
            {                                                                                                                               \
                return  TTransformContext::GetTransformedBlock< ULIS_REG[ n ] >( (::ULIS::TBlock< ULIS_REG[ n ] >*)iBlockSrc                \
                                                                               , iMat, iPerformanceOptions );                               \
            }
        ULIS_REPEAT( ULIS_REG_SIZE, ULIS_REG_SWITCH_OP, void )
        #undef ULIS_REG_SWITCH_OP
    }

    return  nullptr;
}

} // namespace ULIS

