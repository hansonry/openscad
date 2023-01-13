/*
 *  OpenSCAD (www.openscad.org)
 *  Copyright (C) 2009-2011 Clifford Wolf <clifford@clifford.at> and
 *                          Marius Kintel <marius@kintel.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  As a special exception, you have permission to link this program
 *  with the CGAL library and distribute executables, as long as you
 *  follow the requirements of the GNU GPL in regard to all of the
 *  software in the executable aside from CGAL.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include "ProjectionNode.h"
#include "module.h"
#include "ModuleInstantiation.h"
#include "Children.h"
#include "Parameters.h"
#include "Builtins.h"
#include <Python.h>
#include "pyopenscad.h"

#include <cassert>
#include <boost/assign/std/vector.hpp>
using namespace boost::assign; // bring 'operator+=()' into scope

static std::shared_ptr<AbstractNode> builtin_projection(const ModuleInstantiation *inst, Arguments arguments, const Children& children)
{
  auto node = std::make_shared<ProjectionNode>(inst);

  Parameters parameters = Parameters::parse(std::move(arguments), inst->location(), {"cut"}, {"convexity"});
  node->convexity = static_cast<int>(parameters["convexity"].toDouble());
  if (parameters["cut"].type() == Value::Type::BOOL) {
    node->cut_mode = parameters["cut"].toBool();
  }

  return children.instantiate(node);
}


PyObject* python_projection(PyObject *self, PyObject *args, PyObject *kwargs)
{
  std::shared_ptr<AbstractNode> child;

  auto node = std::make_shared<ProjectionNode>(&todo_fix_inst);

  char * kwlist[] ={"obj","cut","convexity",NULL};
  PyObject *obj = NULL;
  const char *cutmode = NULL;
  long convexity = 2;
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "O!|sl", kwlist, 
                          &PyOpenSCADType, &obj,
			  &cutmode, &convexity
                          )) {
        PyErr_SetString(PyExc_TypeError,"error duing parsing\n");
        return NULL;
  }
  child = PyOpenSCADObjectToNode(obj);

  node->convexity = convexity;
  node->cut_mode = 0;
  if(cutmode != NULL && !strcasecmp(cutmode,"cut")) node->cut_mode=1;

  node->children.push_back(child);
  return PyOpenSCADObjectFromNode(&PyOpenSCADType,node);       
}

PyObject* python_projection_oo(PyObject *self, PyObject *args, PyObject *kwargs)
{
        PyObject *new_args=python_oo_args(self,args);
        PyObject *result = python_projection(self,new_args,kwargs);
//      Py_DECREF(&new_args);
        return result;
}
  

std::string ProjectionNode::toString() const
{
  return STR("projection(cut = ", (this->cut_mode ? "true" : "false"),
                                 ", convexity = ", this->convexity, ")");
}

void register_builtin_projection()
{
  Builtins::init("projection", new BuiltinModule(builtin_projection),
  {
    "projection(cut = false)",
  });
}
