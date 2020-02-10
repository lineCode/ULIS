// Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
// IDDN FR.001.250001.002.S.P.2019.000.00000
/**
*
*   PyULIS2
*__________________
*
* @file         PyULIS2.cpp
* @author       Clement Berthaud
* @brief        Python3 module for ULIS2.
* @copyright    Copyright © 2018-2020 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include <ULIS2>
#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyObject *PyULIS2Error;

PyObject*
spam_system(PyObject *self, PyObject *args)
{
    const char *command;
    int sts;

    if (!PyArg_ParseTuple(args, "s", &command))
        return NULL;
    sts = system(command);
    if (sts < 0) {
        PyErr_SetString(PyULIS2Error, "System command failed");
        return NULL;
    }
    return PyLong_FromLong(sts);
}


static PyMethodDef PyULIS2Methods[] = {
    { "system",  spam_system, METH_VARARGS, "Execute a shell command." },
    { NULL, NULL, 0, NULL } /* Sentinel */
};

static struct PyModuleDef PyULIS2Module  = {
      PyModuleDef_HEAD_INIT
    , "PyULIS2"                 /* name of module */
    , NULL                      /* module documentation, may be NULL */
    , -1                        /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    , PyULIS2Methods
};

PyMODINIT_FUNC
PyInit_PyULIS2(void)
{
    PyObject *m;

    m = PyModule_Create( &PyULIS2Module );
    if( m == NULL )
        return  NULL;

    PyULIS2Error = PyErr_NewException(" PyULIS2.error", NULL, NULL );
    Py_XINCREF( PyULIS2Error );
    if( PyModule_AddObject( m, "error", PyULIS2Error ) < 0 ) {
        Py_XDECREF( PyULIS2Error );
        Py_CLEAR( PyULIS2Error );
        Py_DECREF( m );
        return  NULL;
    }

    return  m;
}
