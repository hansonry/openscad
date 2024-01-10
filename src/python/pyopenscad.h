#include <Python.h>
#include <memory>
#include "python_public.h"
#include "node.h"
#include <geometry/Polygon2d.h>
#include "src/core/function.h"

#pragma GCC diagnostic ignored "-Wwrite-strings"

#define DECLARE_INSTANCE	std::string instance_name; \
	AssignmentList inst_asslist;\
	ModuleInstantiation *instance = new ModuleInstantiation(instance_name,inst_asslist, Location::NONE);


typedef struct {
  PyObject_HEAD
  std::shared_ptr<AbstractNode> node;
  PyObject *dict;
  /* Type-specific fields go here. */
} PyOpenSCADObject;

PyMODINIT_FUNC PyInit_PyOpenSCAD(void);

extern PyTypeObject PyOpenSCADType;

extern std::shared_ptr<AbstractNode> python_result_node;
extern std::vector<SelectedObject> python_result_handle;

extern bool python_active;
extern std::string trusted_edit_document_name;
extern std::string untrusted_edit_document_name;
bool trust_python_file(const std::string &file, const std::string &content);
PyObject *PyOpenSCADObjectFromNode(PyTypeObject *type, const std::shared_ptr<AbstractNode> &node);
std::shared_ptr<AbstractNode> PyOpenSCADObjectToNode(PyObject *object, PyObject **dict );
std::shared_ptr<AbstractNode> PyOpenSCADObjectToNodeMulti(PyObject *object, PyObject **dict);
int python_more_obj(std::vector<std::shared_ptr<AbstractNode>>& children, PyObject *more_obj);
Outline2d python_getprofile(void *cbfunc, int fn, double arg);
double python_doublefunc(void *cbfunc, double arg);
std::shared_ptr<AbstractNode> python_modulefunc(const ModuleInstantiation *module,const std::shared_ptr<const Context> &context, int *modulefound);

Value python_functionfunc(const FunctionCall *call,const std::shared_ptr<const Context> &context);
int python_vectorval(PyObject *vec, double *x, double *y, double *z, double *w=NULL);
int python_numberval(PyObject *number, double *result);
void get_fnas(double& fn, double& fa, double& fs);
void python_retrieve_pyname(const std::shared_ptr<AbstractNode> &node);
void python_build_hashmap(const std::shared_ptr<AbstractNode> &node);

extern std::vector<std::string> mapping_name;
extern std::vector<std::string> mapping_code;
extern std::vector<int> mapping_level;

PyObject *python_str(PyObject *self);

extern PyNumberMethods PyOpenSCADNumbers;
extern PyMappingMethods PyOpenSCADMapping;
extern PyMethodDef PyOpenSCADFunctions[];
extern PyMethodDef PyOpenSCADMethods[];

extern PyObject *pythonMainModule;
extern PyObject *pythonInitDict;
