#include <cstdlib>
#include <cmath>

#include "fab.h"
#include "tree/tree.h"
#include "tree/parser.h"

#include "fab/types/shape.h"

Shape::Shape()
    : math(""), bounds(Bounds()), tree(NULL)
{
    // Nothing to do here
}

Shape::Shape(std::string math)
    : Shape(math, Bounds())
{
    // Nothing to do here
}

Shape::Shape(std::string math, float xmin, float ymin,
                     float xmax, float ymax)
    : Shape(math, Bounds(xmin, ymin, xmax, ymax))
{
    // Nothing to do here
}

Shape::Shape(std::string math, float xmin, float ymin, float zmin,
                     float xmax, float ymax, float zmax)
    : Shape(math, Bounds(xmin, ymin, zmin, xmax, ymax, zmax))
{
    // Nothing to do here
}

Shape::Shape(std::string math, Bounds bounds)
    : math(math), bounds(bounds), tree(parse(math.c_str()), free_tree)
{
    if (tree == NULL)
    {
        throw fab::ParseError();
    }
}

Shape Shape::map(Transform t) const
{
    return Shape("m" + (t.x_forward.length() ? t.x_forward : " ")
                     + (t.y_forward.length() ? t.y_forward : " ")
                     + (t.z_forward.length() ? t.z_forward : " ") + math,
                 bounds.map(t));
}

Shape operator~(const Shape& a)
{
    return Shape("n" + a.math);
}


Shape operator&(const Shape& a, const Shape& b)
{
    return Shape("a" + a.math + b.math,
                     fmax(a.bounds.xmin, b.bounds.xmin),
                     fmax(a.bounds.ymin, b.bounds.ymin),
                     fmax(a.bounds.zmin, b.bounds.zmin),
                     fmin(a.bounds.xmax, b.bounds.xmax),
                     fmin(a.bounds.ymax, b.bounds.ymax),
                     fmin(a.bounds.zmax, b.bounds.zmax));
}

Shape operator|(const Shape& a, const Shape& b)
{
    return Shape("i" + a.math + b.math,
                     fmin(a.bounds.xmin, b.bounds.xmin),
                     fmin(a.bounds.ymin, b.bounds.ymin),
                     fmin(a.bounds.zmin, b.bounds.zmin),
                     fmax(a.bounds.xmax, b.bounds.xmax),
                     fmax(a.bounds.ymax, b.bounds.ymax),
                     fmax(a.bounds.zmax, b.bounds.zmax));

}
