#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

int main(int argc, char *argv[])
{
  PyObject *pSysPath, *pLibName;
  PyObject *shop_module, *pModuleName;
  PyObject *function, *return_value;
  bool is_continue;
  char choice;

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

  // Set the sys.path.
  pSysPath = PySys_GetObject("path");
  if (pSysPath == nullptr)
  {
    std::cerr << "Failed to import sys\n";
  }

  pLibName = PyUnicode_FromString("pylib");
  if (PyList_Insert(pSysPath, 0, pLibName))
  {
    std::cerr << "Error inserting program library into sys.path\n";
  }
  Py_DECREF(pLibName);

  // Import the module.
  pModuleName = PyUnicode_DecodeFSDefault("shop");
  shop_module = PyImport_Import(pModuleName);
  Py_DECREF(pModuleName);

  if (shop_module == nullptr)
  {
    PyErr_Print();
    std::cerr << "Failed to load \"shop\"\n";
    return 1;
  }

  is_continue = true;
  do
  {
    function = PyObject_GetAttrString(shop_module, "show_items");
    if (function && PyCallable_Check(function))
    {
      return_value = PyObject_CallObject(function, nullptr);
      Py_DECREF(return_value);
    }
    else
    {
      if (PyErr_Occurred())
        PyErr_Print();
      std::cerr << "Cannot find function \"show_items\"";
    }

    std::cout << "Select the item you want (W, L, S or q to exit): ";
    std::cin >> choice;

    if (choice == 'q')
    {
      is_continue = false;
    }
    else if (choice == 'W')
    {
    }
    else if (choice == 'L')
    {
    }
    else if (choice == 'S')
    {
    }
    else
    {
      // Invalid choice.
    }

  } while (is_continue);

  Py_XDECREF(function);
  Py_DECREF(shop_module);

  if (Py_FinalizeEx() < 0)
  {
    exit(120);
  }
  PyMem_RawFree(program);
  return EXIT_SUCCESS;
}
