// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   PyULIS2
*__________________
*
* @file         _PyULIS2_AbstractPixel.ipp
* @author       Clement Berthaud
* @brief        Python3 module for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include <ULIS2>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

/////////////////////////////////////////////////////
/// Object Structure
typedef struct {
    PyObject_HEAD
    ::ul2::IPixel* _mPixel;
} _PyULIS2Object_AbstractPixel;

/////////////////////////////////////////////////////
/// Dealloc
static void
_PyULIS2Object_AbstractPixel_dealloc( _PyULIS2Object_AbstractPixel* self ) {
    Py_TYPE( self )->tp_free( ( PyObject * ) self );
}

/////////////////////////////////////////////////////
/// Alloc
static PyObject* _PyULIS2Object_AbstractPixel_new( PyTypeObject* type, PyObject* args, PyObject* kwds )
{
    _PyULIS2Object_AbstractPixel *self;
    self = (_PyULIS2Object_AbstractPixel*)type->tp_alloc( type, 0 );
    if (self != NULL) self->_mPixel = nullptr;
    return (PyObject *) self;
}

/////////////////////////////////////////////////////
/// Init
static int
_PyULIS2Object_AbstractPixel_init( _PyULIS2Object_AbstractPixel* self, PyObject* args, PyObject* kwds )
{
    return 0;
}

/////////////////////////////////////////////////////
// Methods
#define _PyULIS2Object_AbstractPixel_GetterMethod_Begin( iName )                                                        \
    static PyObject *                                                                                                   \
    _PyULIS2Object_AbstractPixel_ ## iName ( _PyULIS2Object_AbstractPixel* self, PyObject* Py_UNUSED( ignored ) )       \
    {                                                                                                                   \
        if (self->_mPixel == nullptr) {                                                                                 \
            PyErr_SetString( PyExc_AttributeError, "Bad Access to uninitialized _PyULIS2Object_AbstractPixel object" ); \
            return NULL;                                                                                                \
        }
#define _PyULIS2Object_AbstractPixel_GetterMethod_End }
#define _PyULIS2Object_AbstractPixel_CheckError_SelfNULL if( self->_mPixel == nullptr ) { PyErr_SetString( PyExc_AttributeError, "Bad Access to uninitialized _PyULIS2Object_AbstractPixel object" ); return NULL; }

_PyULIS2Object_AbstractPixel_GetterMethod_Begin( BytesPerSample     )   return  PyLong_FromLong( self->_mPixel->BytesPerSample() );    _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( Depth              )   return  PyLong_FromLong( self->_mPixel->Depth() );             _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( Format             )   return  PyLong_FromLong( self->_mPixel->Format() );            _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( Model              )   return  PyLong_FromLong( self->_mPixel->Model() );             _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( Type               )   return  PyLong_FromLong( self->_mPixel->Type() );              _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( HasAlpha           )   return  PyLong_FromLong( self->_mPixel->HasAlpha() );          _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( Swapped            )   return  PyLong_FromLong( self->_mPixel->Swapped() );           _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( Reversed           )   return  PyLong_FromLong( self->_mPixel->Reversed() );          _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( NumSamples         )   return  PyLong_FromLong( self->_mPixel->NumSamples() );        _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( NumColorChannels   )   return  PyLong_FromLong( self->_mPixel->NumColorChannels() );  _PyULIS2Object_AbstractPixel_GetterMethod_End
_PyULIS2Object_AbstractPixel_GetterMethod_Begin( AlphaIndex         )   return  PyLong_FromLong( self->_mPixel->AlphaIndex() );        _PyULIS2Object_AbstractPixel_GetterMethod_End

//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Getters
static PyObject* _PyULIS2Object_AbstractPixel_GetValue8( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyLong_FromLong( self->_mPixel->GetValue< ::ul2::uint8 >( i ) );
}
static PyObject* _PyULIS2Object_AbstractPixel_GetValue16( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyLong_FromLong( self->_mPixel->GetValue< ::ul2::uint16 >( i ) );
}
static PyObject* _PyULIS2Object_AbstractPixel_GetValue32( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->GetValue< ::ul2::uint32 >( i ) );
}
static PyObject* _PyULIS2Object_AbstractPixel_GetValueF( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->GetValue< ::ul2::ufloat >( i ) );
}
static PyObject* _PyULIS2Object_AbstractPixel_GetValueD( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->GetValue< ::ul2::udouble >( i ) );
}
//Raw
static PyObject* _PyULIS2Object_AbstractPixel_GetValueRaw8( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyLong_FromLong( self->_mPixel->GetValueRaw< ::ul2::uint8 >( i ) );
}
static PyObject* _PyULIS2Object_AbstractPixel_GetValueRaw16( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyLong_FromLong( self->_mPixel->GetValueRaw< ::ul2::uint16 >( i ) );
}
static PyObject* _PyULIS2Object_AbstractPixel_GetValueRaw32( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->GetValueRaw< ::ul2::uint32 >( i ) );
}
static PyObject* _PyULIS2Object_AbstractPixel_GetValueRawF( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->GetValueRaw< ::ul2::ufloat >( i ) );
}
static PyObject* _PyULIS2Object_AbstractPixel_GetValueRawD( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->GetValueRaw< ::ul2::udouble >( i ) );
}
//Alpha
static PyObject* _PyULIS2Object_AbstractPixel_Alpha8( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyLong_FromLong( self->_mPixel->Alpha< ::ul2::uint8 >() );
}
static PyObject* _PyULIS2Object_AbstractPixel_Alpha16( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyLong_FromLong( self->_mPixel->Alpha< ::ul2::uint16 >() );
}
static PyObject* _PyULIS2Object_AbstractPixel_Alpha32( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->Alpha< ::ul2::uint32 >() );
}
static PyObject* _PyULIS2Object_AbstractPixel_AlphaF( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->Alpha< ::ul2::ufloat >() );
}
static PyObject* _PyULIS2Object_AbstractPixel_AlphaD( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i; if( !PyArg_ParseTuple( args, "i", &i ) ) return  NULL;
    return  PyFloat_FromDouble( self->_mPixel->Alpha< ::ul2::udouble >() );
}
//--------------------------------------------------------------------------------------
//------------------------------------------------------------------------------ Setters
static PyObject* _PyULIS2Object_AbstractPixel_SetValue8( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint8 val = static_cast< ::ul2::uint8 >( ::ul2::FMaths::Clamp( v, 0, 0xFF ) );
    self->_mPixel->SetValue< ::ul2::uint8 >( i, val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetValue16( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint16 val = static_cast< ::ul2::uint16 >( ::ul2::FMaths::Clamp( v, 0, 0xFFFF ) );
    self->_mPixel->SetValue< ::ul2::uint16 >( i, val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetValue32( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint32 val = static_cast< ::ul2::uint32 >( ::ul2::FMaths::Min( static_cast< ::ul2::uint32 >( ::ul2::FMaths::Max( v, 0 ) ), UINT32_MAX ) );
    self->_mPixel->SetValue< ::ul2::uint32 >( i, val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetValueF( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i;
    float v;
    if( !PyArg_ParseTuple( args, "if", &i, &v ) ) return  NULL;
    v = ::ul2::FMaths::Clamp( v, 0.f, 1.f );
    self->_mPixel->SetValue< ::ul2::ufloat >( i, v );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetValueD( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i;
    double v;
    if( !PyArg_ParseTuple( args, "id", &i, &v ) ) return  NULL;
    v = ::ul2::FMaths::Clamp( v, 0.0, 1.0 );
    self->_mPixel->SetValue< ::ul2::udouble >( i, v );
    return  Py_None;
}
// Raw
static PyObject* _PyULIS2Object_AbstractPixel_SetValueRaw8( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint8 val = static_cast< ::ul2::uint8 >( ::ul2::FMaths::Clamp( v, 0, 0xFF ) );
    self->_mPixel->SetValueRaw< ::ul2::uint8 >( i, val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetValueRaw16( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint16 val = static_cast< ::ul2::uint16 >( ::ul2::FMaths::Clamp( v, 0, 0xFFFF ) );
    self->_mPixel->SetValueRaw< ::ul2::uint16 >( i, val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetValueRaw32( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint32 val = static_cast< ::ul2::uint32 >( ::ul2::FMaths::Min( static_cast< ::ul2::uint32 >( ::ul2::FMaths::Max( v, 0 ) ), UINT32_MAX ) );
    self->_mPixel->SetValueRaw< ::ul2::uint32 >( i, val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetValueRawF( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i;
    float v;
    if( !PyArg_ParseTuple( args, "if", &i, &v ) ) return  NULL;
    v = ::ul2::FMaths::Clamp( v, 0.f, 1.f );
    self->_mPixel->SetValueRaw< ::ul2::ufloat >( i, v );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetValueRawD( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i;
    double v;
    if( !PyArg_ParseTuple( args, "id", &i, &v ) ) return  NULL;
    v = ::ul2::FMaths::Clamp( v, 0.0, 1.0 );
    self->_mPixel->SetValueRaw< ::ul2::udouble >( i, v );
    return  Py_None;
}
// Alpha
static PyObject* _PyULIS2Object_AbstractPixel_SetAlpha8( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint8 val = static_cast< ::ul2::uint8 >( ::ul2::FMaths::Clamp( v, 0, 0xFF ) );
    self->_mPixel->SetAlpha< ::ul2::uint8 >( val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetAlpha16( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint16 val = static_cast< ::ul2::uint16 >( ::ul2::FMaths::Clamp( v, 0, 0xFFFF ) );
    self->_mPixel->SetAlpha< ::ul2::uint16 >( val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetAlpha32( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i, v;
    if( !PyArg_ParseTuple( args, "ii", &i, &v ) ) return  NULL;
    ::ul2::uint32 val = static_cast< ::ul2::uint32 >( ::ul2::FMaths::Min( static_cast< ::ul2::uint32 >( ::ul2::FMaths::Max( v, 0 ) ), UINT32_MAX ) );
    self->_mPixel->SetAlpha< ::ul2::uint32 >( val );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetAlphaF( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i;
    float v;
    if( !PyArg_ParseTuple( args, "if", &i, &v ) ) return  NULL;
    v = ::ul2::FMaths::Clamp( v, 0.f, 1.f );
    self->_mPixel->SetAlpha< ::ul2::ufloat >( v );
    return  Py_None;
}
static PyObject* _PyULIS2Object_AbstractPixel_SetAlphaD( _PyULIS2Object_AbstractPixel* self, PyObject* args ) {
    _PyULIS2Object_AbstractPixel_CheckError_SelfNULL
    int i;
    double v;
    if( !PyArg_ParseTuple( args, "id", &i, &v ) ) return  NULL;
    v = ::ul2::FMaths::Clamp( v, 0.0, 1.0 );
    self->_mPixel->SetAlpha< ::ul2::udouble >( v );
    return  Py_None;
}

/////////////////////////////////////////////////////
/// Meta Methods
static PyMethodDef _PyULIS2Object_AbstractPixel_methods[] = {
    { "BytesPerSample"      , (PyCFunction)_PyULIS2Object_AbstractPixel_BytesPerSample      , METH_NOARGS, "BytesPerSample"     },
    { "Depth"               , (PyCFunction)_PyULIS2Object_AbstractPixel_Depth               , METH_NOARGS, "Depth"              },
    { "Format"              , (PyCFunction)_PyULIS2Object_AbstractPixel_Format              , METH_NOARGS, "Format"             },
    { "Model"               , (PyCFunction)_PyULIS2Object_AbstractPixel_Model               , METH_NOARGS, "Model"              },
    { "Type"                , (PyCFunction)_PyULIS2Object_AbstractPixel_Type                , METH_NOARGS, "Type"               },
    { "HasAlpha"            , (PyCFunction)_PyULIS2Object_AbstractPixel_HasAlpha            , METH_NOARGS, "HasAlpha"           },
    { "Swapped"             , (PyCFunction)_PyULIS2Object_AbstractPixel_Swapped             , METH_NOARGS, "Swapped"            },
    { "Reversed"            , (PyCFunction)_PyULIS2Object_AbstractPixel_Reversed            , METH_NOARGS, "Reversed"           },
    { "NumSamples"          , (PyCFunction)_PyULIS2Object_AbstractPixel_NumSamples          , METH_NOARGS, "NumSamples"         },
    { "NumColorChannels"    , (PyCFunction)_PyULIS2Object_AbstractPixel_NumColorChannels    , METH_NOARGS, "NumColorChannels"   },
    { "AlphaIndex"          , (PyCFunction)_PyULIS2Object_AbstractPixel_AlphaIndex          , METH_NOARGS, "AlphaIndex"         },
    { "GetValue8"           , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValue8           , METH_VARARGS, "GetValue8"         },
    { "GetValue16"          , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValue16          , METH_VARARGS, "GetValue16"        },
    { "GetValue32"          , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValue32          , METH_VARARGS, "GetValue32"        },
    { "GetValueF"           , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValueF           , METH_VARARGS, "GetValueF"         },
    { "GetValueD"           , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValueD           , METH_VARARGS, "GetValueD"         },
    { "GetValueRaw8"        , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValueRaw8        , METH_VARARGS, "GetValue8"         },
    { "GetValueRaw16"       , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValueRaw16       , METH_VARARGS, "GetValue16"        },
    { "GetValueRaw32"       , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValueRaw32       , METH_VARARGS, "GetValue32"        },
    { "GetValueRawF"        , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValueRawF        , METH_VARARGS, "GetValueF"         },
    { "GetValueRawD"        , (PyCFunction)_PyULIS2Object_AbstractPixel_GetValueRawD        , METH_VARARGS, "GetValueD"         },
    { "Alpha8"              , (PyCFunction)_PyULIS2Object_AbstractPixel_Alpha8              , METH_VARARGS, "GetValue8"         },
    { "Alpha16"             , (PyCFunction)_PyULIS2Object_AbstractPixel_Alpha16             , METH_VARARGS, "GetValue16"        },
    { "Alpha32"             , (PyCFunction)_PyULIS2Object_AbstractPixel_Alpha32             , METH_VARARGS, "GetValue32"        },
    { "AlphaF"              , (PyCFunction)_PyULIS2Object_AbstractPixel_AlphaF              , METH_VARARGS, "GetValueF"         },
    { "AlphaD"              , (PyCFunction)_PyULIS2Object_AbstractPixel_AlphaD              , METH_VARARGS, "GetValueD"         },
    { "SetValue8"           , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValue8           , METH_VARARGS, "GetValue8"         },
    { "SetValue16"          , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValue16          , METH_VARARGS, "GetValue16"        },
    { "SetValue32"          , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValue32          , METH_VARARGS, "GetValue32"        },
    { "SetValueF"           , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValueF           , METH_VARARGS, "GetValueF"         },
    { "SetValueD"           , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValueD           , METH_VARARGS, "GetValueD"         },
    { "SetValueRaw8"        , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValueRaw8        , METH_VARARGS, "GetValue8"         },
    { "SetValueRaw16"       , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValueRaw16       , METH_VARARGS, "GetValue16"        },
    { "SetValueRaw32"       , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValueRaw32       , METH_VARARGS, "GetValue32"        },
    { "SetValueRawF"        , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValueRawF        , METH_VARARGS, "GetValueF"         },
    { "SetValueRawD"        , (PyCFunction)_PyULIS2Object_AbstractPixel_SetValueRawD        , METH_VARARGS, "GetValueD"         },
    { "SetValueRaw8"        , (PyCFunction)_PyULIS2Object_AbstractPixel_SetAlpha8           , METH_VARARGS, "GetValue8"         },
    { "SetValueRaw16"       , (PyCFunction)_PyULIS2Object_AbstractPixel_SetAlpha16          , METH_VARARGS, "GetValue16"        },
    { "SetValueRaw32"       , (PyCFunction)_PyULIS2Object_AbstractPixel_SetAlpha32          , METH_VARARGS, "GetValue32"        },
    { "SetValueRawF"        , (PyCFunction)_PyULIS2Object_AbstractPixel_SetAlphaF           , METH_VARARGS, "GetValueF"         },
    { "SetValueRawD"        , (PyCFunction)_PyULIS2Object_AbstractPixel_SetAlphaD           , METH_VARARGS, "GetValueD"         },
    { NULL } // Sentinel
};

/////////////////////////////////////////////////////
/// Meta Types
static PyTypeObject IPixel = {
PyVarObject_HEAD_INIT(NULL, 0)
    "PyULIS2.IPixel", /* tp_name */
    sizeof( _PyULIS2Object_AbstractPixel ), /* tp_basicsize */
    0, /* tp_itemsize */
    (destructor)_PyULIS2Object_AbstractPixel_dealloc, /* tp_dealloc */
    0, /* tp_print */
    0, /* tp_getattr */
    0, /* tp_setattr */
    0, /* tp_as_async */
    0, /* tp_repr */
    0, /* tp_as_number */
    0, /* tp_as_sequence */
    0, /* tp_as_mapping */
    0, /* tp_hash */
    0, /* tp_call */
    0, /* tp_str */
    0, /* tp_getattro */
    0, /* tp_setattro */
    0, /* tp_as_buffer */
    Py_TPFLAGS_BASETYPE | Py_TPFLAGS_DEFAULT, /* tp_flags */
    "ULIS2 Pixel Value Object.", /* tp_doc */
    0, /* tp_traverse */
    0, /* tp_clear */
    0, /* tp_richcompare */
    0, /* tp_weaklistoffset */
    0, /* tp_iter */
    0, /* tp_iternext */
    _PyULIS2Object_AbstractPixel_methods, /* tp_methods */
    0, /* tp_members */
    0, /* tp_getset */
    0, /* tp_base */
    0, /* tp_dict */
    0, /* tp_descr_get */
    0, /* tp_descr_set */
    0, /* tp_dictoffset */
    (initproc)_PyULIS2Object_AbstractPixel_init, /* tp_init */
    0, /* tp_alloc */
    _PyULIS2Object_AbstractPixel_new, /* tp_new */
    0, /* tp_free */
    0, /* tp_is_gc */
    0, /* tp_bases */
    0, /* tp_mro */
    0, /* tp_cache */
    0, /* tp_subclasses */
    0, /* tp_weaklist */
    0, /* tp_del */
    0, /* tp_version_tag */
    0, /* tp_finalize */
};

