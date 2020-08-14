#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

int main(int argc, char *argv[])
{
  PyObject *pModule, *pModuleName;
  PyObject *pFunc, *pValue;

  PyObject *pSysPath, *pLibName;

  wchar_t *program = Py_DecodeLocale(argv[0], NULL);
  if (program == nullptr)
  {
    std::cerr << "Fatal error: cannot decode argv[0]\n";
    exit(1);
  }

  Py_SetProgramName(program);
  Py_Initialize();
  if (!Py_IsInitialized())
  {
    std::cerr << "Error initializing Python interpreter\n";
    exit(1);
  }

  PyRun_SimpleString("import sys;print(sys.path)\n");

  // Set the sys.path.
  pSysPath = PySys_GetObject("path");
  if (pSysPath == nullptr)
  {
    std::cerr << "Failed to import sys\n";
  }

  pLibName = PyUnicode_FromString("lib");
  if (PyList_Insert(pSysPath, 0, pLibName))
  {
    std::cerr << "Error inserting program library into sys.path\n";
  }
  Py_DECREF(pLibName);

  // Import the module.
  pModuleName = PyUnicode_DecodeFSDefault("helloworld");
  pModule = PyImport_Import(pModuleName);
  Py_DECREF(pModuleName);

  if (pModule != nullptr)
  {
    pFunc = PyObject_GetAttrString(pModule, "hello");

    if (pFunc && PyCallable_Check(pFunc))
    {
      pValue = PyObject_CallObject(pFunc, nullptr);
      Py_DECREF(pValue);
    }
    else
    {
      if (PyErr_Occurred())
        PyErr_Print();
      std::cerr << "Cannot find function \"hello\"\n";
    }
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);
  }
  else
  {
    PyErr_Print();
    std::cerr << "Failed to load \"helloworld\"\n";
    return 1;
  }

  PyRun_SimpleString("import sys;print(sys.path)\n");

  if (Py_FinalizeEx() < 0)
  {
    exit(120);
  }
  PyMem_RawFree(program);
  return EXIT_SUCCESS;
}
