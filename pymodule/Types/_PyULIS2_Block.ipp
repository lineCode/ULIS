// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   PyULIS2
*__________________
*
* @file         _PyULIS2_Block.ipp
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
    ::ul2::FBlock* _mBlock;
} _PyULIS2Object_Block;

/////////////////////////////////////////////////////
/// Dealloc
static void
_PyULIS2Object_Block_dealloc( _PyULIS2Object_Block* self ) {
    Py_TYPE( self )->tp_free( ( PyObject * ) self );
}

/////////////////////////////////////////////////////
/// Alloc
static PyObject* _PyULIS2Object_Block_new( PyTypeObject* type, PyObject* args, PyObject* kwds )
{
    _PyULIS2Object_Block *self;
    self = (_PyULIS2Object_Block*)type->tp_alloc( type, 0 );
    if (self != NULL) self->_mBlock = nullptr;
    return (PyObject *) self;
}

/////////////////////////////////////////////////////
/// Init
static int
_PyULIS2Object_Block_init( _PyULIS2Object_Block* self, PyObject* args, PyObject* kwds )
{
    static char *kwlist[] = { "width", "height", "format", NULL };
    int w, h;
    w = h = 0;
    ::ul2::tFormat fmt = 0;

    if( !PyArg_ParseTupleAndKeywords( args, kwds, "iik", kwlist, &w, &h, &fmt ) ) {
        PyErr_SetString( PyExc_TypeError, "Bad input argmuents in init" );
        return -1;
    }

    self->_mBlock = new ::ul2::FBlock( w, h, fmt );
    return 0;
}

/////////////////////////////////////////////////////
/// Accessors
#define _PyULIS2Object_Block_GetterMethod_Begin( iName )                                                                \
    static PyObject *                                                                                                   \
    _PyULIS2Object_Block_ ## iName ( _PyULIS2Object_Block* self, PyObject* Py_UNUSED( ignored ) )                       \
    {                                                                                                                   \
        if (self->_mBlock == nullptr) {                                                                                 \
            PyErr_SetString( PyExc_AttributeError, "Bad Access to uninitialized _PyULIS2Object_Block object" );         \
            return NULL;                                                                                                \
        }
#define _PyULIS2Object_Block_GetterMethod_End }

// Width
_PyULIS2Object_Block_GetterMethod_Begin( Width )
    return  PyLong_FromLong( self->_mBlock->Width() );
_PyULIS2Object_Block_GetterMethod_End

// Height
_PyULIS2Object_Block_GetterMethod_Begin( Height )
    return  PyLong_FromLong( self->_mBlock->Height() );
_PyULIS2Object_Block_GetterMethod_End

// Format
_PyULIS2Object_Block_GetterMethod_Begin( Format )
    return  PyLong_FromLong( self->_mBlock->Format() );
_PyULIS2Object_Block_GetterMethod_End

/////////////////////////////////////////////////////
/// Meta Methods
static PyMethodDef Custom_methods[] = {
    { "Width", (PyCFunction)_PyULIS2Object_Block_Width,     METH_NOARGS, "Return the Width of the Block."   },
    { "Height", (PyCFunction)_PyULIS2Object_Block_Height,   METH_NOARGS, "Return the Height of the Block."  },
    { "Format", (PyCFunction)_PyULIS2Object_Block_Format,   METH_NOARGS, "Return the Format of the Block."  },
    { NULL } // Sentinel
};

/////////////////////////////////////////////////////
/// Meta Types
static PyTypeObject _PyULIS2Type_Block = {
PyVarObject_HEAD_INIT(NULL, 0)
    "_PyULIS2._PyULIS2Object_Block", /* tp_name */
    sizeof( _PyULIS2Object_Block ), /* tp_basicsize */
    0, /* tp_itemsize */
    (destructor)_PyULIS2Object_Block_dealloc, /* tp_dealloc */
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
    Py_TPFLAGS_DEFAULT, /* tp_flags */
    "ULIS2 Block Object.", /* tp_doc */
    0, /* tp_traverse */
    0, /* tp_clear */
    0, /* tp_richcompare */
    0, /* tp_weaklistoffset */
    0, /* tp_iter */
    0, /* tp_iternext */
    Custom_methods, /* tp_methods */
    0, /* tp_members */
    0, /* tp_getset */
    0, /* tp_base */
    0, /* tp_dict */
    0, /* tp_descr_get */
    0, /* tp_descr_set */
    0, /* tp_dictoffset */
    (initproc)_PyULIS2Object_Block_init, /* tp_init */
    0, /* tp_alloc */
    _PyULIS2Object_Block_new, /* tp_new */
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

