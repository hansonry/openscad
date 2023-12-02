#pragma once

#include "node.h"
#include "Value.h"

#ifdef ENABLE_PYTHON
#include <src/python/python_public.h>
#endif
class RotateExtrudeNode : public AbstractPolyNode
{
public:
  VISITABLE();
  RotateExtrudeNode(const ModuleInstantiation *mi) : AbstractPolyNode(mi) {
    convexity = 0;
    fn = fs = fa = 0;
    origin_x = origin_y = scale = offset_x = offset_y = 0;
    angle = 360;
  }
  std::string toString() const override;
  std::string name() const override { return "rotate_extrude"; }

  int convexity;
  double fn, fs, fa;
  double origin_x, origin_y, scale, offset_x, offset_y, angle;
  double twist;
  Filename filename;
  std::string layername;
 #ifdef ENABLE_PYTHON
  void *profile_func;
  void *twist_func;
 #endif  
};
