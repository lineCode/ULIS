// Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   ULIS2
*__________________
*
* @file         Pixel.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the Pixel classes.
* @copyright    Copyright © 2018-2019 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core.h"
#include <vector>

ULIS2_NAMESPACE_BEGIN
class IPixel;
class FPixelValue;
class FPixelProxy;
class FColorProfile;
/////////////////////////////////////////////////////
/// @class      IPixel
/// @brief      The IPixel class provides a mean of storing and manipulating pixels in various formats.
/// @details    The pixel format, type, layout, and other informations can be retrieved in the pixel format member.
class ULIS2_API IPixel
{
public:
    // Construction / Destruction
    virtual ~IPixel() = 0;
    IPixel( uint32 iFormat, FColorProfile* iProfile = nullptr );

public:
    // Public API
    tByte*          Ptr();
    void            AssignProfile( FColorProfile* iProfile );
    const tByte*    Ptr()               const;
    uint8           BytesPerSample()    const;
    uint8           Depth()             const;
    tFormat         Format()            const;
    eModelSig       Model()             const;
    eType           Type()              const;
    bool            HasAlpha()          const;
    bool            Swapped()           const;
    bool            Reversed()          const;
    uint8           NumSamples()        const;
    uint8           MaxSample()         const;
    uint8           NumColorChannels()  const;
    FColorProfile*  Profile()           const;

public:
    // Index Layout API
    uint8  RedIndex( uint8 iIndex ) const;
    uint8  AlphaIndex() const;

public:
    // Generic access API
    tByte*                              SamplePtr( uint8 iIndex );
    template< typename T > T*           SamplePtrT( uint8 iIndex );
    const tByte*                        SamplePtr( uint8 iIndex )               const;
    template< typename T > const T*     SamplePtrT( uint8 iIndex )              const;
    template< typename T > T            GetValueRaw( uint8 iIndex )             const;
    template< typename T > void         SetValueRaw( uint8 iIndex, T iValue  ) ;
    template< typename T > T&           GetRefRaw( uint8 iIndex );
    template< typename T > const T&     GetConstRefRaw( uint8 iIndex )          const;
    template< typename T > T            GetValue( uint8 iIndex )                const;
    template< typename T > T&           GetRef( uint8 iIndex );
    template< typename T > const T&     GetConstRef( uint8 iIndex )             const;
    template< typename T > void         SetValue( uint8 iIndex, T iValue );

public:
    // Model Access API
    template< typename T> ULIS2_FORCEINLINE T Alpha() const                     { ULIS2_ASSERT( HasAlpha(), "Bad Call" ); return  GetValueRaw< T >( AlphaIndex() ); }
    template< typename T> ULIS2_FORCEINLINE T A() const                         { ULIS2_ASSERT( HasAlpha(), "Bad Call" ); return  GetValueRaw< T >( AlphaIndex() ); }
    template< typename T> ULIS2_FORCEINLINE T Grey() const                      { return  GetValue< T >( 0 );       }
    template< typename T> ULIS2_FORCEINLINE T Red() const                       { return  GetValue< T >( 0 );       }
    template< typename T> ULIS2_FORCEINLINE T Green() const                     { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T Blue() const                      { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T R() const                         { return  GetValue< T >( 0 );       }
    template< typename T> ULIS2_FORCEINLINE T G() const                         { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T B() const                         { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T Hue() const                       { return  GetValue< T >( 0 );       }
    template< typename T> ULIS2_FORCEINLINE T Saturation() const                { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T Luminosity() const                { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T Value() const                     { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T Cyan() const                      { return  GetValue< T >( 0 );       }
    template< typename T> ULIS2_FORCEINLINE T Magenta() const                   { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T Yellow() const                    { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T Key() const                       { return  GetValue< T >( 3 );       }
    template< typename T> ULIS2_FORCEINLINE T Luma() const                      { return  GetValue< T >( 0 );       }
    template< typename T> ULIS2_FORCEINLINE T Cb() const                        { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T Cr() const                        { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T U() const                         { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T V() const                         { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T K() const                         { return  GetValue< T >( 3 );       }
    template< typename T> ULIS2_FORCEINLINE T X() const                         { return  GetValue< T >( 0 );       }
    template< typename T> ULIS2_FORCEINLINE T Y() const                         { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T Z() const                         { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T L() const                         { return  GetValue< T >( 0 );       }
    template< typename T> ULIS2_FORCEINLINE T a() const                         { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T b() const                         { return  GetValue< T >( 2 );       }
    template< typename T> ULIS2_FORCEINLINE T x() const                         { return  GetValue< T >( 1 );       }
    template< typename T> ULIS2_FORCEINLINE T y() const                         { return  GetValue< T >( 2 );       }
    ULIS2_FORCEINLINE uint8 Alpha8() const                                      { return  Alpha< uint8 >();         }
    ULIS2_FORCEINLINE uint8 A8() const                                          { return  A< uint8 >();             }
    ULIS2_FORCEINLINE uint8 Grey8() const                                       { return  Grey< uint8 >();          }
    ULIS2_FORCEINLINE uint8 Red8() const                                        { return  Red< uint8 >();           }
    ULIS2_FORCEINLINE uint8 Green8() const                                      { return  Green< uint8 >();         }
    ULIS2_FORCEINLINE uint8 Blue8() const                                       { return  Blue< uint8 >();          }
    ULIS2_FORCEINLINE uint8 R8() const                                          { return  R< uint8 >();             }
    ULIS2_FORCEINLINE uint8 G8() const                                          { return  G< uint8 >();             }
    ULIS2_FORCEINLINE uint8 B8() const                                          { return  B< uint8 >();             }
    ULIS2_FORCEINLINE uint8 Hue8() const                                        { return  Hue< uint8 >();           }
    ULIS2_FORCEINLINE uint8 Saturation8() const                                 { return  Saturation< uint8 >();    }
    ULIS2_FORCEINLINE uint8 Lightness8() const                                  { return  Luminosity< uint8 >();    }
    ULIS2_FORCEINLINE uint8 Value8() const                                      { return  Value< uint8 >();         }
    ULIS2_FORCEINLINE uint8 Cyan8() const                                       { return  Cyan< uint8 >();          }
    ULIS2_FORCEINLINE uint8 Magenta8() const                                    { return  Magenta< uint8 >();       }
    ULIS2_FORCEINLINE uint8 Yellow8() const                                     { return  Yellow< uint8 >();        }
    ULIS2_FORCEINLINE uint8 Key8() const                                        { return  Key< uint8 >();           }
    ULIS2_FORCEINLINE uint8 Luma8() const                                       { return  Luma< uint8 >();          }
    ULIS2_FORCEINLINE uint8 Cb8() const                                         { return  Cb< uint8 >();            }
    ULIS2_FORCEINLINE uint8 Cr8() const                                         { return  Cr< uint8 >();            }
    ULIS2_FORCEINLINE uint8 U8() const                                          { return  U< uint8 >();             }
    ULIS2_FORCEINLINE uint8 V8() const                                          { return  V< uint8 >();             }
    ULIS2_FORCEINLINE uint8 K8() const                                          { return  K< uint8 >();             }
    ULIS2_FORCEINLINE uint8 X8() const                                          { return  X< uint8 >();             }
    ULIS2_FORCEINLINE uint8 Y8() const                                          { return  Y< uint8 >();             }
    ULIS2_FORCEINLINE uint8 Z8() const                                          { return  Z< uint8 >();             }
    ULIS2_FORCEINLINE uint8 L8() const                                          { return  L< uint8 >();             }
    ULIS2_FORCEINLINE uint8 a8() const                                          { return  a< uint8 >();             }
    ULIS2_FORCEINLINE uint8 b8() const                                          { return  b< uint8 >();             }
    ULIS2_FORCEINLINE uint8 x8() const                                          { return  x< uint8 >();             }
    ULIS2_FORCEINLINE uint8 y8() const                                          { return  y< uint8 >();             }
    ULIS2_FORCEINLINE uint16 Alpha16() const                                    { return  Alpha< uint16 >();        }
    ULIS2_FORCEINLINE uint16 A16() const                                        { return  A< uint16 >();            }
    ULIS2_FORCEINLINE uint16 Grey16() const                                     { return  Grey< uint16 >();         }
    ULIS2_FORCEINLINE uint16 Red16() const                                      { return  Red< uint16 >();          }
    ULIS2_FORCEINLINE uint16 Green16() const                                    { return  Green< uint16 >();        }
    ULIS2_FORCEINLINE uint16 Blue16() const                                     { return  Blue< uint16 >();         }
    ULIS2_FORCEINLINE uint16 R16() const                                        { return  R< uint16 >();            }
    ULIS2_FORCEINLINE uint16 G16() const                                        { return  G< uint16 >();            }
    ULIS2_FORCEINLINE uint16 B16() const                                        { return  B< uint16 >();            }
    ULIS2_FORCEINLINE uint16 Hue16() const                                      { return  Hue< uint16 >();          }
    ULIS2_FORCEINLINE uint16 Saturation16() const                               { return  Saturation< uint16 >();   }
    ULIS2_FORCEINLINE uint16 Lightness16() const                                { return  Luminosity< uint16 >();   }
    ULIS2_FORCEINLINE uint16 Value16() const                                    { return  Value< uint16 >();        }
    ULIS2_FORCEINLINE uint16 Cyan16() const                                     { return  Cyan< uint16 >();         }
    ULIS2_FORCEINLINE uint16 Magenta16() const                                  { return  Magenta< uint16 >();      }
    ULIS2_FORCEINLINE uint16 Yellow16() const                                   { return  Yellow< uint16 >();       }
    ULIS2_FORCEINLINE uint16 Key16() const                                      { return  Key< uint16 >();          }
    ULIS2_FORCEINLINE uint16 Luma16() const                                     { return  Luma< uint16 >();         }
    ULIS2_FORCEINLINE uint16 Cb16() const                                       { return  Cb< uint16 >();           }
    ULIS2_FORCEINLINE uint16 Cr16() const                                       { return  Cr< uint16 >();           }
    ULIS2_FORCEINLINE uint16 U16() const                                        { return  U< uint16 >();            }
    ULIS2_FORCEINLINE uint16 V16() const                                        { return  V< uint16 >();            }
    ULIS2_FORCEINLINE uint16 K16() const                                        { return  K< uint16 >();            }
    ULIS2_FORCEINLINE uint16 X16() const                                        { return  X< uint16 >();            }
    ULIS2_FORCEINLINE uint16 Y16() const                                        { return  Y< uint16 >();            }
    ULIS2_FORCEINLINE uint16 Z16() const                                        { return  Z< uint16 >();            }
    ULIS2_FORCEINLINE uint16 L16() const                                        { return  L< uint16 >();            }
    ULIS2_FORCEINLINE uint16 a16() const                                        { return  a< uint16 >();            }
    ULIS2_FORCEINLINE uint16 b16() const                                        { return  b< uint16 >();            }
    ULIS2_FORCEINLINE uint16 x16() const                                        { return  x< uint16 >();            }
    ULIS2_FORCEINLINE uint16 y16() const                                        { return  y< uint16 >();            }
    ULIS2_FORCEINLINE uint32 Alpha32() const                                    { return  Alpha< uint32 >();        }
    ULIS2_FORCEINLINE uint32 A32() const                                        { return  A< uint32 >();            }
    ULIS2_FORCEINLINE uint32 Grey32() const                                     { return  Grey< uint32 >();         }
    ULIS2_FORCEINLINE uint32 Red32() const                                      { return  Red< uint32 >();          }
    ULIS2_FORCEINLINE uint32 Green32() const                                    { return  Green< uint32 >();        }
    ULIS2_FORCEINLINE uint32 Blue32() const                                     { return  Blue< uint32 >();         }
    ULIS2_FORCEINLINE uint32 R32() const                                        { return  R< uint32 >();            }
    ULIS2_FORCEINLINE uint32 G32() const                                        { return  G< uint32 >();            }
    ULIS2_FORCEINLINE uint32 B32() const                                        { return  B< uint32 >();            }
    ULIS2_FORCEINLINE uint32 Hue32() const                                      { return  Hue< uint32 >();          }
    ULIS2_FORCEINLINE uint32 Saturation32() const                               { return  Saturation< uint32 >();   }
    ULIS2_FORCEINLINE uint32 Lightness32() const                                { return  Luminosity< uint32 >();   }
    ULIS2_FORCEINLINE uint32 Value32() const                                    { return  Value< uint32 >();        }
    ULIS2_FORCEINLINE uint32 Cyan32() const                                     { return  Cyan< uint32 >();         }
    ULIS2_FORCEINLINE uint32 Magenta32() const                                  { return  Magenta< uint32 >();      }
    ULIS2_FORCEINLINE uint32 Yellow32() const                                   { return  Yellow< uint32 >();       }
    ULIS2_FORCEINLINE uint32 Key32() const                                      { return  Key< uint32 >();          }
    ULIS2_FORCEINLINE uint32 Luma32() const                                     { return  Luma< uint32 >();         }
    ULIS2_FORCEINLINE uint32 Cb32() const                                       { return  Cb< uint32 >();           }
    ULIS2_FORCEINLINE uint32 Cr32() const                                       { return  Cr< uint32 >();           }
    ULIS2_FORCEINLINE uint32 U32() const                                        { return  U< uint32 >();            }
    ULIS2_FORCEINLINE uint32 V32() const                                        { return  V< uint32 >();            }
    ULIS2_FORCEINLINE uint32 K32() const                                        { return  K< uint32 >();            }
    ULIS2_FORCEINLINE uint32 X32() const                                        { return  X< uint32 >();            }
    ULIS2_FORCEINLINE uint32 Y32() const                                        { return  Y< uint32 >();            }
    ULIS2_FORCEINLINE uint32 Z32() const                                        { return  Z< uint32 >();            }
    ULIS2_FORCEINLINE uint32 L32() const                                        { return  L< uint32 >();            }
    ULIS2_FORCEINLINE uint32 a32() const                                        { return  a< uint32 >();            }
    ULIS2_FORCEINLINE uint32 b32() const                                        { return  b< uint32 >();            }
    ULIS2_FORCEINLINE uint32 x32() const                                        { return  x< uint32 >();            }
    ULIS2_FORCEINLINE uint32 y32() const                                        { return  y< uint32 >();            }
    ULIS2_FORCEINLINE float AlphaF() const                                      { return  Alpha< float >();         }
    ULIS2_FORCEINLINE float AF() const                                          { return  A< float >();             }
    ULIS2_FORCEINLINE float GreyF() const                                       { return  Grey< float >();          }
    ULIS2_FORCEINLINE float RedF() const                                        { return  Red< float >();           }
    ULIS2_FORCEINLINE float GreenF() const                                      { return  Green< float >();         }
    ULIS2_FORCEINLINE float BlueF() const                                       { return  Blue< float >();          }
    ULIS2_FORCEINLINE float RF() const                                          { return  R< float >();             }
    ULIS2_FORCEINLINE float GF() const                                          { return  G< float >();             }
    ULIS2_FORCEINLINE float BF() const                                          { return  B< float >();             }
    ULIS2_FORCEINLINE float HueF() const                                        { return  Hue< float >();           }
    ULIS2_FORCEINLINE float SaturationF() const                                 { return  Saturation< float >();    }
    ULIS2_FORCEINLINE float LightnessF() const                                  { return  Luminosity< float >();    }
    ULIS2_FORCEINLINE float ValueF() const                                      { return  Value< float >();         }
    ULIS2_FORCEINLINE float CyanF() const                                       { return  Cyan< float >();          }
    ULIS2_FORCEINLINE float MagentaF() const                                    { return  Magenta< float >();       }
    ULIS2_FORCEINLINE float YellowF() const                                     { return  Yellow< float >();        }
    ULIS2_FORCEINLINE float KeyF() const                                        { return  Key< float >();           }
    ULIS2_FORCEINLINE float LumaF() const                                       { return  Luma< float >();          }
    ULIS2_FORCEINLINE float CbF() const                                         { return  Cb< float >();            }
    ULIS2_FORCEINLINE float CrF() const                                         { return  Cr< float >();            }
    ULIS2_FORCEINLINE float UF() const                                          { return  U< float >();             }
    ULIS2_FORCEINLINE float VF() const                                          { return  V< float >();             }
    ULIS2_FORCEINLINE float KF() const                                          { return  K< float >();             }
    ULIS2_FORCEINLINE float XF() const                                          { return  X< float >();             }
    ULIS2_FORCEINLINE float YF() const                                          { return  Y< float >();             }
    ULIS2_FORCEINLINE float ZF() const                                          { return  Z< float >();             }
    ULIS2_FORCEINLINE float LF() const                                          { return  L< float >();             }
    ULIS2_FORCEINLINE float aF() const                                          { return  a< float >();             }
    ULIS2_FORCEINLINE float bF() const                                          { return  b< float >();             }
    ULIS2_FORCEINLINE float xF() const                                          { return  x< float >();             }
    ULIS2_FORCEINLINE float yF() const                                          { return  y< float >();             }
    ULIS2_FORCEINLINE double AlphaD() const                                     { return  Alpha< double >();        }
    ULIS2_FORCEINLINE double AD() const                                         { return  A< double >();            }
    ULIS2_FORCEINLINE double GreyD() const                                      { return  Grey< double >();         }
    ULIS2_FORCEINLINE double RedD() const                                       { return  Red< double >();          }
    ULIS2_FORCEINLINE double GreenD() const                                     { return  Green< double >();        }
    ULIS2_FORCEINLINE double BlueD() const                                      { return  Blue< double >();         }
    ULIS2_FORCEINLINE double RD() const                                         { return  R< double >();            }
    ULIS2_FORCEINLINE double GD() const                                         { return  G< double >();            }
    ULIS2_FORCEINLINE double BD() const                                         { return  B< double >();            }
    ULIS2_FORCEINLINE double HueD() const                                       { return  Hue< double >();          }
    ULIS2_FORCEINLINE double SaturationD() const                                { return  Saturation< double >();   }
    ULIS2_FORCEINLINE double LightnessD() const                                 { return  Luminosity< double >();   }
    ULIS2_FORCEINLINE double ValueD() const                                     { return  Value< double >();        }
    ULIS2_FORCEINLINE double CyanD() const                                      { return  Cyan< double >();         }
    ULIS2_FORCEINLINE double MagentaD() const                                   { return  Magenta< double >();      }
    ULIS2_FORCEINLINE double YellowD() const                                    { return  Yellow< double >();       }
    ULIS2_FORCEINLINE double KeyD() const                                       { return  Key< double >();          }
    ULIS2_FORCEINLINE double LumaD() const                                      { return  Luma< double >();         }
    ULIS2_FORCEINLINE double CbD() const                                        { return  Cb< double >();           }
    ULIS2_FORCEINLINE double CrD() const                                        { return  Cr< double >();           }
    ULIS2_FORCEINLINE double UD() const                                         { return  U< double >();            }
    ULIS2_FORCEINLINE double VD() const                                         { return  V< double >();            }
    ULIS2_FORCEINLINE double KD() const                                         { return  K< double >();            }
    ULIS2_FORCEINLINE double XD() const                                         { return  X< double >();            }
    ULIS2_FORCEINLINE double YD() const                                         { return  Y< double >();            }
    ULIS2_FORCEINLINE double ZD() const                                         { return  Z< double >();            }
    ULIS2_FORCEINLINE double LD() const                                         { return  L< double >();            }
    ULIS2_FORCEINLINE double aD() const                                         { return  a< double >();            }
    ULIS2_FORCEINLINE double bD() const                                         { return  b< double >();            }
    ULIS2_FORCEINLINE double xD() const                                         { return  x< double >();            }
    ULIS2_FORCEINLINE double yD() const                                         { return  y< double >();            }

    template< typename T> ULIS2_FORCEINLINE void SetAlpha(        T iValue )    { ULIS2_ASSERT( HasAlpha(), "Bad Call" ); SetValueRaw< T >( AlphaIndex() ); }
    template< typename T> ULIS2_FORCEINLINE void SetA(            T iValue )    { ULIS2_ASSERT( HasAlpha(), "Bad Call" ); SetValueRaw< T >( AlphaIndex() ); }
    template< typename T> ULIS2_FORCEINLINE void SetGrey(         T iValue )    { SetValue< T >( 0 ); }
    template< typename T> ULIS2_FORCEINLINE void SetRed(          T iValue )    { SetValue< T >( 0 ); }
    template< typename T> ULIS2_FORCEINLINE void SetGreen(        T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void SetBlue(         T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void SetR(            T iValue )    { SetValue< T >( 0 ); }
    template< typename T> ULIS2_FORCEINLINE void SetG(            T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void SetB(            T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void SetHue(          T iValue )    { SetValue< T >( 0 ); }
    template< typename T> ULIS2_FORCEINLINE void SetSaturation(   T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void SetLuminosity(   T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void SetValue(        T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void SetCyan(         T iValue )    { SetValue< T >( 0 ); }
    template< typename T> ULIS2_FORCEINLINE void SetMagenta(      T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void SetYellow(       T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void SetKey(          T iValue )    { SetValue< T >( 3 ); }
    template< typename T> ULIS2_FORCEINLINE void SetLuma(         T iValue )    { SetValue< T >( 0 ); }
    template< typename T> ULIS2_FORCEINLINE void SetCb(           T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void SetCr(           T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void SetU(            T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void SetV(            T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void SetK(            T iValue )    { SetValue< T >( 3 ); }
    template< typename T> ULIS2_FORCEINLINE void SetX(            T iValue )    { SetValue< T >( 0 ); }
    template< typename T> ULIS2_FORCEINLINE void SetY(            T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void SetZ(            T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void SetL(            T iValue )    { SetValue< T >( 0 ); }
    template< typename T> ULIS2_FORCEINLINE void Seta(            T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void Setb(            T iValue )    { SetValue< T >( 2 ); }
    template< typename T> ULIS2_FORCEINLINE void Setx(            T iValue )    { SetValue< T >( 1 ); }
    template< typename T> ULIS2_FORCEINLINE void Sety(            T iValue )    { SetValue< T >( 2 ); }

protected:
    // Protected Data Members
    tByte*          mData;
    tFormat         mFormat;
    FColorProfile*  mProfile;
};


class ULIS2_API FPixelValue : public IPixel
{
    typedef IPixel tParent;

public:
    // Construction / Destruction
    virtual ~FPixelValue();
    FPixelValue( uint32 iFormat, FColorProfile* iProfile = nullptr );
    FPixelValue( const tByte* iData, tFormat iFormat, FColorProfile* iProfile = nullptr );
    FPixelValue( const FPixelProxy& iProxy );
};
typedef FPixelValue FPixel;

class ULIS2_API FPixelProxy : public IPixel
{
    typedef IPixel tParent;

public:
    // Construction / Destruction
    virtual ~FPixelProxy();
    FPixelProxy( tByte* iData, tFormat iFormat, FColorProfile* iProfile = nullptr );
};

ULIS2_NAMESPACE_END

