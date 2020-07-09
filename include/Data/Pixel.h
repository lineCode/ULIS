// Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/*
*
*   ULIS3
*__________________
*
* @file         Pixel.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Pixel and Color
*               related classes.
* @copyright    Copyright 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Data/ColorSpace.h"
#include "Data/Format.h"

ULIS3_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      IHasChannels
/// @brief      The IHasChannels class is an abstract interface allowing to
///             store and manipulate pixels or colors in various formats.
/// @details    IHasChannels is a pure virtual class that provides a common
///             interface for the FPixel and FColor classes.
///
///             The IHasChannels has a format which specifies the type, memory
///             layout, color model, and other informations about the pixel
///             data. The underlying pixel data is always a regular contiguous
///             buffer storage that lives on RAM with no alignment requirement.
///             It is usually very small, ranging from 1 byte to 40 bytes,
///             depending on the format.
///
///             The IHasChannels interface provides a way to access individualy
///             named samples or channels components. If accessing a channel
///             from a named component that is not compatible with the initial
///             format of the IHasChannels, the returned value could make
///             little sense to the caller, but it is properly defined and is
///             safe to call unless accessing a named component that is out of
///             range and from another color model with a greater number of
///             channels than the true color model of the data, according to
///             the format.
///
///             There are many named components that can be accessed with a
///             suffix indicating which type is required. If accessing such
///             components with a type suffix that is not the appropriate type
///             according to the format, the function will trigger an assert and
///             crash in debug build, but it will fail silently and access the
///             buffer out of bounds in release builds, leading to potential
///             memory corruption or crashes further down the line.
///
///             \sa FColor
///             \sa FPixel
class ULIS3_API IHasChannels
    : public IHasFormat
    , public IHasColorSpace
{
public:
    /*! Virtual destructor in order to allow polymorphic manipulation of subtypes. */
    virtual ~IHasChannels() = 0;

    /*! Construct a IHasChannels interface in a derived class */
    IHasChannels( uint32 iFormat, FColorSpace* iColorSpace = nullptr );

    /*! Comparison strict equal operator */
    bool operator==( const IHasChannels& iOther ) const;

    /*! Comparison strict not equal operator */
    bool operator!=( const IHasChannels& iOther ) const;

    /*!
    Obtain a pointer to the raw data at the base element of the underlying
    buffer.

    The data is accessible through the returned pointer and can be modified
    safely, as long as you don't dereference elements outside of the buffer
    boundaries.

    \sa SampleData()
    */
    uint8* Data();

    /*!
    Obtain a const pointer to the raw data at the base element of the underlying
    buffer.

    The data is accessible through the returned pointer and can be read
    safely, as long as you don't dereference elements outside of the buffer
    boundaries.

    \sa SampleData()
    */
    const uint8* Data() const;

    /*!
    Obtain a pointer to the data at the specified sample index in the
    underlying buffer, without using the format index redirection.

    This method is aware of the format depth though, and the returned pointer
    can be modified safely, as long as you don't dereference elements outside of
    the buffer boundaries.

    \sa Data()
    */
    uint8* SampleDataRaw( uint8 iIndex );

    /*!
    Obtain a pointer to the data at the specified sample index in the
    underlying buffer, without using the format index redirection.

    This method is aware of the format depth though, and the returned pointer
    can be read safely, as long as you don't dereference elements outside of
    the buffer boundaries.

    \sa Data()
    */
    const uint8* SampleDataRaw( uint8 iIndex ) const;

    template< typename T > T* SampleDataT( uint8 iIndex );
    template< typename T > const T* SampleDataT( uint8 iIndex ) const;
    template< typename T > T ValueRaw( uint8 iIndex ) const;
    template< typename T > void SetValueRaw( uint8 iIndex, T iValue  ) ;
    template< typename T > T& RefRaw( uint8 iIndex );
    template< typename T > const T& RefRaw( uint8 iIndex ) const;
    template< typename T > T Value( uint8 iIndex ) const;
    template< typename T > T& Ref( uint8 iIndex );
    template< typename T > const T& Ref( uint8 iIndex ) const;
    template< typename T > void SetValue( uint8 iIndex, T iValue );

    template< typename T >  ULIS3_FORCEINLINE T Alpha()         const { return  HasAlpha() ? GetValueRaw< T >( AlphaIndex() ) : MaxType< T >(); }
    template< typename T >  ULIS3_FORCEINLINE T A()             const { return  HasAlpha() ? GetValueRaw< T >( AlphaIndex() ) : MaxType< T >(); }
    template< typename T >  ULIS3_FORCEINLINE T Grey()          const { return  GetValue< T >( 0 ); }
    template< typename T >  ULIS3_FORCEINLINE T Red()           const { return  GetValue< T >( 0 ); }
    template< typename T >  ULIS3_FORCEINLINE T Green()         const { return  GetValue< T >( 1 ); }
    template< typename T >  ULIS3_FORCEINLINE T Blue()          const { return  GetValue< T >( 2 ); }
    template< typename T >  ULIS3_FORCEINLINE T R()             const { return  GetValue< T >( 0 ); }
    template< typename T >  ULIS3_FORCEINLINE T G()             const { return  GetValue< T >( 1 ); }
    template< typename T >  ULIS3_FORCEINLINE T B()             const { return  GetValue< T >( 2 ); }
    template< typename T >  ULIS3_FORCEINLINE T Hue()           const { return  GetValue< T >( 0 ); }
    template< typename T >  ULIS3_FORCEINLINE T Saturation()    const { return  GetValue< T >( 1 ); }
    template< typename T >  ULIS3_FORCEINLINE T Lightness()     const { return  GetValue< T >( 2 ); }
    template< typename T >  ULIS3_FORCEINLINE T Value()         const { return  GetValue< T >( 2 ); }
    template< typename T >  ULIS3_FORCEINLINE T Cyan()          const { return  GetValue< T >( 0 ); }
    template< typename T >  ULIS3_FORCEINLINE T Magenta()       const { return  GetValue< T >( 1 ); }
    template< typename T >  ULIS3_FORCEINLINE T Yellow()        const { return  GetValue< T >( 2 ); }
    template< typename T >  ULIS3_FORCEINLINE T Key()           const { return  GetValue< T >( 3 ); }
    template< typename T >  ULIS3_FORCEINLINE T Luma()          const { return  GetValue< T >( 0 ); }
    template< typename T >  ULIS3_FORCEINLINE T U()             const { return  GetValue< T >( 1 ); }
    template< typename T >  ULIS3_FORCEINLINE T V()             const { return  GetValue< T >( 2 ); }
    template< typename T >  ULIS3_FORCEINLINE T K()             const { return  GetValue< T >( 3 ); }
    template< typename T >  ULIS3_FORCEINLINE T X()             const { return  GetValue< T >( 0 ); }
    template< typename T >  ULIS3_FORCEINLINE T Y()             const { return  GetValue< T >( 1 ); }
    template< typename T >  ULIS3_FORCEINLINE T Z()             const { return  GetValue< T >( 2 ); }
    template< typename T >  ULIS3_FORCEINLINE T L()             const { return  GetValue< T >( 0 ); }
    template< typename T >  ULIS3_FORCEINLINE T a()             const { return  GetValue< T >( 1 ); }
    template< typename T >  ULIS3_FORCEINLINE T b()             const { return  GetValue< T >( 2 ); }
    template< typename T >  ULIS3_FORCEINLINE T x()             const { return  GetValue< T >( 1 ); }
    template< typename T >  ULIS3_FORCEINLINE T y()             const { return  GetValue< T >( 2 ); }
    ULIS3_FORCEINLINE uint8 Alpha8()        const { return  Alpha< uint8 >();       }
    ULIS3_FORCEINLINE uint8 A8()            const { return  A< uint8 >();           }
    ULIS3_FORCEINLINE uint8 Grey8()         const { return  Grey< uint8 >();        }
    ULIS3_FORCEINLINE uint8 Red8()          const { return  Red< uint8 >();         }
    ULIS3_FORCEINLINE uint8 Green8()        const { return  Green< uint8 >();       }
    ULIS3_FORCEINLINE uint8 Blue8()         const { return  Blue< uint8 >();        }
    ULIS3_FORCEINLINE uint8 R8()            const { return  R< uint8 >();           }
    ULIS3_FORCEINLINE uint8 G8()            const { return  G< uint8 >();           }
    ULIS3_FORCEINLINE uint8 B8()            const { return  B< uint8 >();           }
    ULIS3_FORCEINLINE uint8 Hue8()          const { return  Hue< uint8 >();         }
    ULIS3_FORCEINLINE uint8 Saturation8()   const { return  Saturation< uint8 >();  }
    ULIS3_FORCEINLINE uint8 Lightness8()    const { return  Lightness< uint8 >();   }
    ULIS3_FORCEINLINE uint8 Value8()        const { return  Value< uint8 >();       }
    ULIS3_FORCEINLINE uint8 Cyan8()         const { return  Cyan< uint8 >();        }
    ULIS3_FORCEINLINE uint8 Magenta8()      const { return  Magenta< uint8 >();     }
    ULIS3_FORCEINLINE uint8 Yellow8()       const { return  Yellow< uint8 >();      }
    ULIS3_FORCEINLINE uint8 Key8()          const { return  Key< uint8 >();         }
    ULIS3_FORCEINLINE uint8 Luma8()         const { return  Luma< uint8 >();        }
    ULIS3_FORCEINLINE uint8 U8()            const { return  U< uint8 >();           }
    ULIS3_FORCEINLINE uint8 V8()            const { return  V< uint8 >();           }
    ULIS3_FORCEINLINE uint8 K8()            const { return  K< uint8 >();           }
    ULIS3_FORCEINLINE uint8 X8()            const { return  X< uint8 >();           }
    ULIS3_FORCEINLINE uint8 Y8()            const { return  Y< uint8 >();           }
    ULIS3_FORCEINLINE uint8 Z8()            const { return  Z< uint8 >();           }
    ULIS3_FORCEINLINE uint8 L8()            const { return  L< uint8 >();           }
    ULIS3_FORCEINLINE uint8 a8()            const { return  a< uint8 >();           }
    ULIS3_FORCEINLINE uint8 b8()            const { return  b< uint8 >();           }
    ULIS3_FORCEINLINE uint8 x8()            const { return  x< uint8 >();           }
    ULIS3_FORCEINLINE uint8 y8()            const { return  y< uint8 >();           }
    ULIS3_FORCEINLINE uint16 Alpha16()      const { return  Alpha< uint16 >();      }
    ULIS3_FORCEINLINE uint16 A16()          const { return  A< uint16 >();          }
    ULIS3_FORCEINLINE uint16 Grey16()       const { return  Grey< uint16 >();       }
    ULIS3_FORCEINLINE uint16 Red16()        const { return  Red< uint16 >();        }
    ULIS3_FORCEINLINE uint16 Green16()      const { return  Green< uint16 >();      }
    ULIS3_FORCEINLINE uint16 Blue16()       const { return  Blue< uint16 >();       }
    ULIS3_FORCEINLINE uint16 R16()          const { return  R< uint16 >();          }
    ULIS3_FORCEINLINE uint16 G16()          const { return  G< uint16 >();          }
    ULIS3_FORCEINLINE uint16 B16()          const { return  B< uint16 >();          }
    ULIS3_FORCEINLINE uint16 Hue16()        const { return  Hue< uint16 >();        }
    ULIS3_FORCEINLINE uint16 Saturation16() const { return  Saturation< uint16 >(); }
    ULIS3_FORCEINLINE uint16 Lightness16()  const { return  Lightness< uint16 >();  }
    ULIS3_FORCEINLINE uint16 Value16()      const { return  Value< uint16 >();      }
    ULIS3_FORCEINLINE uint16 Cyan16()       const { return  Cyan< uint16 >();       }
    ULIS3_FORCEINLINE uint16 Magenta16()    const { return  Magenta< uint16 >();    }
    ULIS3_FORCEINLINE uint16 Yellow16()     const { return  Yellow< uint16 >();     }
    ULIS3_FORCEINLINE uint16 Key16()        const { return  Key< uint16 >();        }
    ULIS3_FORCEINLINE uint16 Luma16()       const { return  Luma< uint16 >();       }
    ULIS3_FORCEINLINE uint16 U16()          const { return  U< uint16 >();          }
    ULIS3_FORCEINLINE uint16 V16()          const { return  V< uint16 >();          }
    ULIS3_FORCEINLINE uint16 K16()          const { return  K< uint16 >();          }
    ULIS3_FORCEINLINE uint16 X16()          const { return  X< uint16 >();          }
    ULIS3_FORCEINLINE uint16 Y16()          const { return  Y< uint16 >();          }
    ULIS3_FORCEINLINE uint16 Z16()          const { return  Z< uint16 >();          }
    ULIS3_FORCEINLINE uint16 L16()          const { return  L< uint16 >();          }
    ULIS3_FORCEINLINE uint16 a16()          const { return  a< uint16 >();          }
    ULIS3_FORCEINLINE uint16 b16()          const { return  b< uint16 >();          }
    ULIS3_FORCEINLINE uint16 x16()          const { return  x< uint16 >();          }
    ULIS3_FORCEINLINE uint16 y16()          const { return  y< uint16 >();          }
    ULIS3_FORCEINLINE uint32 Alpha32()      const { return  Alpha< uint32 >();      }
    ULIS3_FORCEINLINE uint32 A32()          const { return  A< uint32 >();          }
    ULIS3_FORCEINLINE uint32 Grey32()       const { return  Grey< uint32 >();       }
    ULIS3_FORCEINLINE uint32 Red32()        const { return  Red< uint32 >();        }
    ULIS3_FORCEINLINE uint32 Green32()      const { return  Green< uint32 >();      }
    ULIS3_FORCEINLINE uint32 Blue32()       const { return  Blue< uint32 >();       }
    ULIS3_FORCEINLINE uint32 R32()          const { return  R< uint32 >();          }
    ULIS3_FORCEINLINE uint32 G32()          const { return  G< uint32 >();          }
    ULIS3_FORCEINLINE uint32 B32()          const { return  B< uint32 >();          }
    ULIS3_FORCEINLINE uint32 Hue32()        const { return  Hue< uint32 >();        }
    ULIS3_FORCEINLINE uint32 Saturation32() const { return  Saturation< uint32 >(); }
    ULIS3_FORCEINLINE uint32 Lightness32()  const { return  Lightness< uint32 >();  }
    ULIS3_FORCEINLINE uint32 Value32()      const { return  Value< uint32 >();      }
    ULIS3_FORCEINLINE uint32 Cyan32()       const { return  Cyan< uint32 >();       }
    ULIS3_FORCEINLINE uint32 Magenta32()    const { return  Magenta< uint32 >();    }
    ULIS3_FORCEINLINE uint32 Yellow32()     const { return  Yellow< uint32 >();     }
    ULIS3_FORCEINLINE uint32 Key32()        const { return  Key< uint32 >();        }
    ULIS3_FORCEINLINE uint32 Luma32()       const { return  Luma< uint32 >();       }
    ULIS3_FORCEINLINE uint32 U32()          const { return  U< uint32 >();          }
    ULIS3_FORCEINLINE uint32 V32()          const { return  V< uint32 >();          }
    ULIS3_FORCEINLINE uint32 K32()          const { return  K< uint32 >();          }
    ULIS3_FORCEINLINE uint32 X32()          const { return  X< uint32 >();          }
    ULIS3_FORCEINLINE uint32 Y32()          const { return  Y< uint32 >();          }
    ULIS3_FORCEINLINE uint32 Z32()          const { return  Z< uint32 >();          }
    ULIS3_FORCEINLINE uint32 L32()          const { return  L< uint32 >();          }
    ULIS3_FORCEINLINE uint32 a32()          const { return  a< uint32 >();          }
    ULIS3_FORCEINLINE uint32 b32()          const { return  b< uint32 >();          }
    ULIS3_FORCEINLINE uint32 x32()          const { return  x< uint32 >();          }
    ULIS3_FORCEINLINE uint32 y32()          const { return  y< uint32 >();          }
    ULIS3_FORCEINLINE float AlphaF()        const { return  Alpha< float >();       }
    ULIS3_FORCEINLINE float AF()            const { return  A< float >();           }
    ULIS3_FORCEINLINE float GreyF()         const { return  Grey< float >();        }
    ULIS3_FORCEINLINE float RedF()          const { return  Red< float >();         }
    ULIS3_FORCEINLINE float GreenF()        const { return  Green< float >();       }
    ULIS3_FORCEINLINE float BlueF()         const { return  Blue< float >();        }
    ULIS3_FORCEINLINE float RF()            const { return  R< float >();           }
    ULIS3_FORCEINLINE float GF()            const { return  G< float >();           }
    ULIS3_FORCEINLINE float BF()            const { return  B< float >();           }
    ULIS3_FORCEINLINE float HueF()          const { return  Hue< float >();         }
    ULIS3_FORCEINLINE float SaturationF()   const { return  Saturation< float >();  }
    ULIS3_FORCEINLINE float LightnessF()    const { return  Lightness< float >();   }
    ULIS3_FORCEINLINE float ValueF()        const { return  Value< float >();       }
    ULIS3_FORCEINLINE float CyanF()         const { return  Cyan< float >();        }
    ULIS3_FORCEINLINE float MagentaF()      const { return  Magenta< float >();     }
    ULIS3_FORCEINLINE float YellowF()       const { return  Yellow< float >();      }
    ULIS3_FORCEINLINE float KeyF()          const { return  Key< float >();         }
    ULIS3_FORCEINLINE float LumaF()         const { return  Luma< float >();        }
    ULIS3_FORCEINLINE float UF()            const { return  U< float >();           }
    ULIS3_FORCEINLINE float VF()            const { return  V< float >();           }
    ULIS3_FORCEINLINE float KF()            const { return  K< float >();           }
    ULIS3_FORCEINLINE float XF()            const { return  X< float >();           }
    ULIS3_FORCEINLINE float YF()            const { return  Y< float >();           }
    ULIS3_FORCEINLINE float ZF()            const { return  Z< float >();           }
    ULIS3_FORCEINLINE float LF()            const { return  L< float >();           }
    ULIS3_FORCEINLINE float aF()            const { return  a< float >();           }
    ULIS3_FORCEINLINE float bF()            const { return  b< float >();           }
    ULIS3_FORCEINLINE float xF()            const { return  x< float >();           }
    ULIS3_FORCEINLINE float yF()            const { return  y< float >();           }
    ULIS3_FORCEINLINE double AlphaD()       const { return  Alpha< double >();      }
    ULIS3_FORCEINLINE double AD()           const { return  A< double >();          }
    ULIS3_FORCEINLINE double GreyD()        const { return  Grey< double >();       }
    ULIS3_FORCEINLINE double RedD()         const { return  Red< double >();        }
    ULIS3_FORCEINLINE double GreenD()       const { return  Green< double >();      }
    ULIS3_FORCEINLINE double BlueD()        const { return  Blue< double >();       }
    ULIS3_FORCEINLINE double RD()           const { return  R< double >();          }
    ULIS3_FORCEINLINE double GD()           const { return  G< double >();          }
    ULIS3_FORCEINLINE double BD()           const { return  B< double >();          }
    ULIS3_FORCEINLINE double HueD()         const { return  Hue< double >();        }
    ULIS3_FORCEINLINE double SaturationD()  const { return  Saturation< double >(); }
    ULIS3_FORCEINLINE double LightnessD()   const { return  Lightness< double >();  }
    ULIS3_FORCEINLINE double ValueD()       const { return  Value< double >();      }
    ULIS3_FORCEINLINE double CyanD()        const { return  Cyan< double >();       }
    ULIS3_FORCEINLINE double MagentaD()     const { return  Magenta< double >();    }
    ULIS3_FORCEINLINE double YellowD()      const { return  Yellow< double >();     }
    ULIS3_FORCEINLINE double KeyD()         const { return  Key< double >();        }
    ULIS3_FORCEINLINE double LumaD()        const { return  Luma< double >();       }
    ULIS3_FORCEINLINE double UD()           const { return  U< double >();          }
    ULIS3_FORCEINLINE double VD()           const { return  V< double >();          }
    ULIS3_FORCEINLINE double KD()           const { return  K< double >();          }
    ULIS3_FORCEINLINE double XD()           const { return  X< double >();          }
    ULIS3_FORCEINLINE double YD()           const { return  Y< double >();          }
    ULIS3_FORCEINLINE double ZD()           const { return  Z< double >();          }
    ULIS3_FORCEINLINE double LD()           const { return  L< double >();          }
    ULIS3_FORCEINLINE double aD()           const { return  a< double >();          }
    ULIS3_FORCEINLINE double bD()           const { return  b< double >();          }
    ULIS3_FORCEINLINE double xD()           const { return  x< double >();          }
    ULIS3_FORCEINLINE double yD()           const { return  y< double >();          }

    template< typename T > ULIS3_FORCEINLINE void SetAlpha(         T iValue ){ if( HasAlpha() ) SetValueRaw< T >( AlphaIndex(), iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetA(             T iValue ){ if( HasAlpha() ) SetValueRaw< T >( AlphaIndex(), iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetGrey(          T iValue ){ SetValue< T >( 0, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetRed(           T iValue ){ SetValue< T >( 0, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetGreen(         T iValue ){ SetValue< T >( 1, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetBlue(          T iValue ){ SetValue< T >( 2, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetR(             T iValue ){ SetValue< T >( 0, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetG(             T iValue ){ SetValue< T >( 1, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetB(             T iValue ){ SetValue< T >( 2, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetHue(           T iValue ){ SetValue< T >( 0, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetSaturation(    T iValue ){ SetValue< T >( 1, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetLightness(     T iValue ){ SetValue< T >( 2, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetValue(         T iValue ){ SetValue< T >( 2, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetCyan(          T iValue ){ SetValue< T >( 0, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetMagenta(       T iValue ){ SetValue< T >( 1, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetYellow(        T iValue ){ SetValue< T >( 2, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetKey(           T iValue ){ SetValue< T >( 3, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetLuma(          T iValue ){ SetValue< T >( 0, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetU(             T iValue ){ SetValue< T >( 1, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetV(             T iValue ){ SetValue< T >( 2, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetK(             T iValue ){ SetValue< T >( 3, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetX(             T iValue ){ SetValue< T >( 0, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetY(             T iValue ){ SetValue< T >( 1, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetZ(             T iValue ){ SetValue< T >( 2, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void SetL(             T iValue ){ SetValue< T >( 0, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void Seta(             T iValue ){ SetValue< T >( 1, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void Setb(             T iValue ){ SetValue< T >( 2, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void Setx(             T iValue ){ SetValue< T >( 1, iValue ); }
    template< typename T > ULIS3_FORCEINLINE void Sety(             T iValue ){ SetValue< T >( 2, iValue ); }
    ULIS3_FORCEINLINE void SetAlpha8(       uint8 iValue )  { SetAlpha< uint8 >( iValue );      }
    ULIS3_FORCEINLINE void SetA8(           uint8 iValue )  { SetA< uint8 >( iValue );          }
    ULIS3_FORCEINLINE void SetGrey8(        uint8 iValue )  { SetValue< uint8 >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetRed8(         uint8 iValue )  { SetValue< uint8 >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetGreen8(       uint8 iValue )  { SetValue< uint8 >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetBlue8(        uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetR8(           uint8 iValue )  { SetValue< uint8 >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetG8(           uint8 iValue )  { SetValue< uint8 >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetB8(           uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetHue8(         uint8 iValue )  { SetValue< uint8 >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetSaturation8(  uint8 iValue )  { SetValue< uint8 >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetLightness8(   uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetValue8(       uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetCyan8(        uint8 iValue )  { SetValue< uint8 >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetMagenta8(     uint8 iValue )  { SetValue< uint8 >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetYellow8(      uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetKey8(         uint8 iValue )  { SetValue< uint8 >( 3, iValue );   }
    ULIS3_FORCEINLINE void SetLuma8(        uint8 iValue )  { SetValue< uint8 >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetU8(           uint8 iValue )  { SetValue< uint8 >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetV8(           uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetK8(           uint8 iValue )  { SetValue< uint8 >( 3, iValue );   }
    ULIS3_FORCEINLINE void SetX8(           uint8 iValue )  { SetValue< uint8 >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetY8(           uint8 iValue )  { SetValue< uint8 >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetZ8(           uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetL8(           uint8 iValue )  { SetValue< uint8 >( 0, iValue );   }
    ULIS3_FORCEINLINE void Seta8(           uint8 iValue )  { SetValue< uint8 >( 1, iValue );   }
    ULIS3_FORCEINLINE void Setb8(           uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void Setx8(           uint8 iValue )  { SetValue< uint8 >( 1, iValue );   }
    ULIS3_FORCEINLINE void Sety8(           uint8 iValue )  { SetValue< uint8 >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetAlpha16(      uint16 iValue ) { SetAlpha< uint16 >( iValue );     }
    ULIS3_FORCEINLINE void SetA16(          uint16 iValue ) { SetA< uint16 >( iValue );         }
    ULIS3_FORCEINLINE void SetGrey16(       uint16 iValue ) { SetValue< uint16 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetRed16(        uint16 iValue ) { SetValue< uint16 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetGreen16(      uint16 iValue ) { SetValue< uint16 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetBlue16(       uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetR16(          uint16 iValue ) { SetValue< uint16 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetG16(          uint16 iValue ) { SetValue< uint16 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetB16(          uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetHue16(        uint16 iValue ) { SetValue< uint16 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetSaturation16( uint16 iValue ) { SetValue< uint16 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetLightness16(  uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetValue16(      uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetCyan16(       uint16 iValue ) { SetValue< uint16 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetMagenta16(    uint16 iValue ) { SetValue< uint16 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetYellow16(     uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetKey16(        uint16 iValue ) { SetValue< uint16 >( 3, iValue );  }
    ULIS3_FORCEINLINE void SetLuma16(       uint16 iValue ) { SetValue< uint16 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetU16(          uint16 iValue ) { SetValue< uint16 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetV16(          uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetK16(          uint16 iValue ) { SetValue< uint16 >( 3, iValue );  }
    ULIS3_FORCEINLINE void SetX16(          uint16 iValue ) { SetValue< uint16 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetY16(          uint16 iValue ) { SetValue< uint16 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetZ16(          uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetL16(          uint16 iValue ) { SetValue< uint16 >( 0, iValue );  }
    ULIS3_FORCEINLINE void Seta16(          uint16 iValue ) { SetValue< uint16 >( 1, iValue );  }
    ULIS3_FORCEINLINE void Setb16(          uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void Setx16(          uint16 iValue ) { SetValue< uint16 >( 1, iValue );  }
    ULIS3_FORCEINLINE void Sety16(          uint16 iValue ) { SetValue< uint16 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetAlpha32(      uint32 iValue ) { SetAlpha< uint32 >( iValue );     }
    ULIS3_FORCEINLINE void SetA32(          uint32 iValue ) { SetA< uint32 >( iValue );         }
    ULIS3_FORCEINLINE void SetGrey32(       uint32 iValue ) { SetValue< uint32 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetRed32(        uint32 iValue ) { SetValue< uint32 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetGreen32(      uint32 iValue ) { SetValue< uint32 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetBlue32(       uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetR32(          uint32 iValue ) { SetValue< uint32 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetG32(          uint32 iValue ) { SetValue< uint32 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetB32(          uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetHue32(        uint32 iValue ) { SetValue< uint32 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetSaturation32( uint32 iValue ) { SetValue< uint32 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetLightness32(  uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetValue32(      uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetCyan32(       uint32 iValue ) { SetValue< uint32 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetMagenta32(    uint32 iValue ) { SetValue< uint32 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetYellow32(     uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetKey32(        uint32 iValue ) { SetValue< uint32 >( 3, iValue );  }
    ULIS3_FORCEINLINE void SetLuma32(       uint32 iValue ) { SetValue< uint32 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetU32(          uint32 iValue ) { SetValue< uint32 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetV32(          uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetK32(          uint32 iValue ) { SetValue< uint32 >( 3, iValue );  }
    ULIS3_FORCEINLINE void SetX32(          uint32 iValue ) { SetValue< uint32 >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetY32(          uint32 iValue ) { SetValue< uint32 >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetZ32(          uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetL32(          uint32 iValue ) { SetValue< uint32 >( 0, iValue );  }
    ULIS3_FORCEINLINE void Seta32(          uint32 iValue ) { SetValue< uint32 >( 1, iValue );  }
    ULIS3_FORCEINLINE void Setb32(          uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void Setx32(          uint32 iValue ) { SetValue< uint32 >( 1, iValue );  }
    ULIS3_FORCEINLINE void Sety32(          uint32 iValue ) { SetValue< uint32 >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetAlphaF(       float iValue )  { SetAlpha< float >( iValue );      }
    ULIS3_FORCEINLINE void SetAF(           float iValue )  { SetA< float >( iValue );          }
    ULIS3_FORCEINLINE void SetGreyF(        float iValue )  { SetValue< float >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetRedF(         float iValue )  { SetValue< float >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetGreenF(       float iValue )  { SetValue< float >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetBlueF(        float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetRF(           float iValue )  { SetValue< float >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetGF(           float iValue )  { SetValue< float >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetBF(           float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetHueF(         float iValue )  { SetValue< float >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetSaturationF(  float iValue )  { SetValue< float >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetLightnessF(   float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetValueF(       float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetCyanF(        float iValue )  { SetValue< float >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetMagentaF(     float iValue )  { SetValue< float >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetYellowF(      float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetKeyF(         float iValue )  { SetValue< float >( 3, iValue );   }
    ULIS3_FORCEINLINE void SetLumaF(        float iValue )  { SetValue< float >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetUF(           float iValue )  { SetValue< float >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetVF(           float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetKF(           float iValue )  { SetValue< float >( 3, iValue );   }
    ULIS3_FORCEINLINE void SetXF(           float iValue )  { SetValue< float >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetYF(           float iValue )  { SetValue< float >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetZF(           float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetLF(           float iValue )  { SetValue< float >( 0, iValue );   }
    ULIS3_FORCEINLINE void SetaF(           float iValue )  { SetValue< float >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetbF(           float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetxF(           float iValue )  { SetValue< float >( 1, iValue );   }
    ULIS3_FORCEINLINE void SetyF(           float iValue )  { SetValue< float >( 2, iValue );   }
    ULIS3_FORCEINLINE void SetAlphaD(       double iValue ) { SetAlpha< double >( iValue );     }
    ULIS3_FORCEINLINE void SetAD(           double iValue ) { SetA< double >( iValue );         }
    ULIS3_FORCEINLINE void SetGreyD(        double iValue ) { SetValue< double >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetRedD(         double iValue ) { SetValue< double >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetGreenD(       double iValue ) { SetValue< double >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetBlueD(        double iValue ) { SetValue< double >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetRD(           double iValue ) { SetValue< double >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetGD(           double iValue ) { SetValue< double >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetBD(           double iValue ) { SetValue< double >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetHueD(         double iValue ) { SetValue< double >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetSaturationD(  double iValue ) { SetValue< double >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetLightnessD(   double iValue ) { SetValue< double >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetValueD(       double iValue ) { SetValue< double >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetCyanD(        double iValue ) { SetValue< double >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetMagentaD(     double iValue ) { SetValue< double >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetYellowD(      double iValue ) { SetValue< double >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetKeyD(         double iValue ) { SetValue< double >( 3, iValue );  }
    ULIS3_FORCEINLINE void SetLumaD(        double iValue ) { SetValue< double >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetUD(           double iValue ) { SetValue< double >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetVD(           double iValue ) { SetValue< double >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetKD(           double iValue ) { SetValue< double >( 3, iValue );  }
    ULIS3_FORCEINLINE void SetXD(           double iValue ) { SetValue< double >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetYD(           double iValue ) { SetValue< double >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetZD(           double iValue ) { SetValue< double >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetLD(           double iValue ) { SetValue< double >( 0, iValue );  }
    ULIS3_FORCEINLINE void SetaD(           double iValue ) { SetValue< double >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetbD(           double iValue ) { SetValue< double >( 2, iValue );  }
    ULIS3_FORCEINLINE void SetxD(           double iValue ) { SetValue< double >( 1, iValue );  }
    ULIS3_FORCEINLINE void SetyD(           double iValue ) { SetValue< double >( 2, iValue );  }

protected:
    uint8* mData;
};

/////////////////////////////////////////////////////
/// @class      FColor
/// @brief      The FColor class provides a mean of storing and manipulating pixels value in various formats.
/// @details    A pixel value allocates its own storage space and is responsible for its memory.
class ULIS3_API FColor : public IHasChannels
{
public:
    // Construction / Destruction
    virtual ~FColor();
    FColor();
    FColor( uint32 iFormat, FColorSpace* iColorSpace = nullptr );
    FColor( const uint8* iData, tFormat iFormat, FColorSpace* iColorSpace = nullptr );
    FColor( const FPixel& iProxy );
    FColor( const FColor& iValue );
    FColor( FColor&& iValue );

    FColor& operator=( const FColor& iOther );
    template< typename T > FColor( uint32 iFormat, std::initializer_list< T > iValues, FColorSpace* iColorSpace = nullptr );

private:
    template< typename T1, typename T2 >
    ULIS3_FORCEINLINE void Set_imp( const std::initializer_list< T1 > iValues )
    {
        ULIS3_ASSERT( iValues.size() == NumSamples(), "Bad input values" );
        for( int i = 0; i < iValues.size(); ++i )
            SetValue< T2 >( i, ConvType< T1, T2 >( *(iValues.begin() + i) ) );
    }

public:
    // Named static constructors
    static FColor FromGreyA8(   uint8  iGrey,   uint8  iA = UINT8_MAX  );
    static FColor FromGreyA16(  uint16 iGrey,   uint16 iA = UINT16_MAX );
    static FColor FromGreyA32(  uint32 iGrey,   uint32 iA = UINT32_MAX );
    static FColor FromGreyAF(   float  iGrey,   float  iA = 1.f        );
    static FColor FromGreyAD(   double iGrey,   double iA = 1.0        );
    static FColor FromRGBA8(    uint8  iR,  uint8  iG,  uint8  iB,  uint8  iA = UINT8_MAX  );
    static FColor FromRGBA16(   uint16 iR,  uint16 iG,  uint16 iB,  uint16 iA = UINT16_MAX );
    static FColor FromRGBA32(   uint32 iR,  uint32 iG,  uint32 iB,  uint32 iA = UINT32_MAX );
    static FColor FromRGBAF(    float  iR,  float  iG,  float  iB,  float  iA = 1.f        );
    static FColor FromRGBAD(    double iR,  double iG,  double iB,  double iA = 1.0        );
    static FColor FromHSVA8(    uint8  iH,  uint8  iS,  uint8  iV,  uint8  iA = UINT8_MAX  );
    static FColor FromHSVA16(   uint16 iH,  uint16 iS,  uint16 iV,  uint16 iA = UINT16_MAX );
    static FColor FromHSVA32(   uint32 iH,  uint32 iS,  uint32 iV,  uint32 iA = UINT32_MAX );
    static FColor FromHSVAF(    float  iH,  float  iS,  float  iV,  float  iA = 1.f        );
    static FColor FromHSVAD(    double iH,  double iS,  double iV,  double iA = 1.0        );
    static FColor FromHSLA8(    uint8  iH,  uint8  iS,  uint8  iL,  uint8  iA = UINT8_MAX  );
    static FColor FromHSLA16(   uint16 iH,  uint16 iS,  uint16 iL,  uint16 iA = UINT16_MAX );
    static FColor FromHSLA32(   uint32 iH,  uint32 iS,  uint32 iL,  uint32 iA = UINT32_MAX );
    static FColor FromHSLAF(    float  iH,  float  iS,  float  iL,  float  iA = 1.f        );
    static FColor FromHSLAD(    double iH,  double iS,  double iL,  double iA = 1.0        );
    static FColor FromCMYA8(    uint8  iC,  uint8  iM,  uint8  iY,  uint8  iA = UINT8_MAX  );
    static FColor FromCMYA16(   uint16 iC,  uint16 iM,  uint16 iY,  uint16 iA = UINT16_MAX );
    static FColor FromCMYA32(   uint32 iC,  uint32 iM,  uint32 iY,  uint32 iA = UINT32_MAX );
    static FColor FromCMYAF(    float  iC,  float  iM,  float  iY,  float  iA = 1.f        );
    static FColor FromCMYAD(    double iC,  double iM,  double iY,  double iA = 1.0        );
    static FColor FromCMYKA8(   uint8  iC,  uint8  iM,  uint8  iY,  uint8  iK,  uint8  iA = UINT8_MAX  );
    static FColor FromCMYKA16(  uint16 iC,  uint16 iM,  uint16 iY,  uint16 iK,  uint16 iA = UINT16_MAX );
    static FColor FromCMYKA32(  uint32 iC,  uint32 iM,  uint32 iY,  uint32 iK,  uint32 iA = UINT32_MAX );
    static FColor FromCMYKAF(   float  iC,  float  iM,  float  iY,  float  iK,  float  iA = 1.f        );
    static FColor FromCMYKAD(   double iC,  double iM,  double iY,  double iK,  double iA = 1.0        );
    static FColor FromYUVA8(    uint8  iY,  uint8  iU,  uint8  iV,  uint8  iA = UINT8_MAX  );
    static FColor FromYUVA16(   uint16 iY,  uint16 iU,  uint16 iV,  uint16 iA = UINT16_MAX );
    static FColor FromYUVA32(   uint32 iY,  uint32 iU,  uint32 iV,  uint32 iA = UINT32_MAX );
    static FColor FromYUVAF(    float  iY,  float  iU,  float  iV,  float  iA = 1.f        );
    static FColor FromYUVAD(    double iY,  double iU,  double iV,  double iA = 1.0        );
    static FColor FromLabA8(    uint8  iL,  uint8  ia,  uint8  ib,  uint8  iA = UINT8_MAX  );
    static FColor FromLabA16(   uint16 iL,  uint16 ia,  uint16 ib,  uint16 iA = UINT16_MAX );
    static FColor FromLabA32(   uint32 iL,  uint32 ia,  uint32 ib,  uint32 iA = UINT32_MAX );
    static FColor FromLabAF(    float  iL,  float  ia,  float  ib,  float  iA = 1.f        );
    static FColor FromLabAD(    double iL,  double ia,  double ib,  double iA = 1.0        );
    static FColor FromXYZA8(    uint8  iX,  uint8  iY,  uint8  iZ,  uint8  iA = UINT8_MAX  );
    static FColor FromXYZA16(   uint16 iX,  uint16 iY,  uint16 iZ,  uint16 iA = UINT16_MAX );
    static FColor FromXYZA32(   uint32 iX,  uint32 iY,  uint32 iZ,  uint32 iA = UINT32_MAX );
    static FColor FromXYZAF(    float  iX,  float  iY,  float  iZ,  float  iA = 1.f        );
    static FColor FromXYZAD(    double iX,  double iY,  double iZ,  double iA = 1.0        );
    static FColor FromYxyA8(    uint8  iY,  uint8  ix,  uint8  iy,  uint8  iA = UINT8_MAX  );
    static FColor FromYxyA16(   uint16 iY,  uint16 ix,  uint16 iy,  uint16 iA = UINT16_MAX );
    static FColor FromYxyA32(   uint32 iY,  uint32 ix,  uint32 iy,  uint32 iA = UINT32_MAX );
    static FColor FromYxyAF(    float  iY,  float  ix,  float  iy,  float  iA = 1.f        );
    static FColor FromYxyAD(    double iY,  double ix,  double iy,  double iA = 1.0        );
};

/////////////////////////////////////////////////////
/// @class      FPixel
/// @brief      The FPixel class provides a mean of storing and manipulating pixels value in various formats.
/// @details    A pixel proxy is a view to a block memory space and is not responsible for this memory.
class ULIS3_API FPixel : public IHasChannels
{
public:
    // Construction / Destruction
    virtual ~FPixel();
    FPixel( tFormat iFormat, FColorSpace* iColorSpace = nullptr );
    FPixel( uint8* iData, tFormat iFormat, FColorSpace* iColorSpace = nullptr );
    FPixel( const uint8* iData, tFormat iFormat, FColorSpace* iColorSpace = nullptr );
    FPixel( const FPixel& iValue );
    FPixel( FPixel&& iValue );
    FPixel& operator=( const FPixel& iValue );
    void SetPtr( uint8* iPtr );
    void SetPtr( const uint8* iPtr );
};

extern template FColor::FColor( uint32, std::initializer_list< int >, FColorSpace* );
extern template FColor::FColor( uint32, std::initializer_list< float >, FColorSpace* );
extern template FColor::FColor( uint32, std::initializer_list< double >, FColorSpace* );
extern template FColor::FColor( uint32, std::initializer_list< uint8 >, FColorSpace* );
extern template FColor::FColor( uint32, std::initializer_list< uint16 >, FColorSpace* );
extern template FColor::FColor( uint32, std::initializer_list< uint32 >, FColorSpace* );
extern template FColor::FColor( uint32, std::initializer_list< uint64 >, FColorSpace* );

ULIS3_NAMESPACE_END

