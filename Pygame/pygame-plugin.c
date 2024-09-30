#include <Python.h>
#include <stdio.h>
#include <stdlib.h>

// Function to initialize the plugin
void init_plugin() {
    // Initialize Python interpreter if not already initialized
    if (!Py_IsInitialized()) {
        Py_Initialize();
        if (!Py_IsInitialized()) {
            fprintf(stderr, "Error: `Py_Initialize` failed\n");
            exit(EXIT_FAILURE);
        }
    }

    // Import the pygame module
    PyObject *pName = PyUnicode_DecodeFSDefault("pygame");
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        // Initialize pygame
        PyObject *pFunc = PyObject_GetAttrString(pModule, "init");
        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject *pValue = PyObject_CallObject(pFunc, NULL);
            if (pValue != NULL) {
                Py_DECREF(pValue);
            } else {
                PyErr_Print();
                fprintf(stderr, "Call to pygame.init failed\n");
            }
        } else {
            if (PyErr_Occurred()) PyErr_Print();
            fprintf(stderr, "Cannot find function pygame.init\n");
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        fprintf(stderr, "Failed to load pygame module\n");
    }

    // Finalize Python interpreter if it was initialized by this plugin
    if (Py_IsInitialized()) {
        Py_Finalize();
    }
}