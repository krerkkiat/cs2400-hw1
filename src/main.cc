#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <iostream>

int main(int argc, char *argv[])
{
  PyObject *pSysPath, *pLibName;
  PyObject *shop_module, *pModuleName;
  PyObject *function, *return_value, *func_args;
  char choice, hard_drive_type;
  int amount;
  int is_ohio_resident = false;

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
    Py_XDECREF(function);

    std::cout << "Select the item you want (W, L, S or q to exit): ";
    std::cin >> choice;

    while (choice != 'W' && choice != 'L' && choice != 'S' && choice != 'q')
    {
      std::cout << "Select the item you want (W, L, S or q to exit): ";
      std::cin >> choice;
    }

    if (choice == 'q')
    {
      break;
    }
    else if (choice == 'W')
    {
      std::cout << "How many do you want?: ";
      std::cin >> amount;
    }
    else if (choice == 'L')
    {
      std::cout << "How many do you want?: ";
      std::cin >> amount;
    }
    else if (choice == 'S')
    {
      std::cout << "How many do you want?: ";
      std::cin >> amount;
    }
    hard_drive_type = choice;

    std::cout << "Are you Ohio resident? (y/n): ";
    std::cin >> choice;
    while (choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
    {
      std::cout << "Are you Ohio resident? (y/n): ";
      std::cin >> choice;
    }
    if (choice == 'y' || choice == 'Y')
    {
      is_ohio_resident = 1;
    }
    else
    {
      is_ohio_resident = 0;
    }

    function = PyObject_GetAttrString(shop_module, "place_order");
    if (function && PyCallable_Check(function))
    {
      func_args = Py_BuildValue("(Cii)", hard_drive_type, amount, is_ohio_resident);
      return_value = PyObject_CallObject(function, func_args);
      Py_DECREF(return_value);
    }
    Py_XDECREF(function);
  } while (true);

  Py_XDECREF(function);
  Py_DECREF(shop_module);

  if (Py_FinalizeEx() < 0)
  {
    exit(120);
  }
  PyMem_RawFree(program);
  return EXIT_SUCCESS;
}
