
#include "tetra.hpp"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_3.h>

namespace tetra
{

namespace __detail {

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_3<K>      Triangulation;
typedef Triangulation::Point          Point;
//typedef Triangulation::Cell_handle    Cell_handle;
typedef Triangulation::Locate_type    Locate_type;

struct _Octagon_Impl
{
    _Octagon_Impl(const std::array<Point, 8> &vertices);
    bool contains(const Point &p);

private:
    const Triangulation T;
};

_Octagon_Impl::_Octagon_Impl(const std::array<Point, 8> &vertices)
    : T(vertices.begin(), vertices.end()) {}

bool _Octagon_Impl::contains(const Point &p)
{
    Locate_type lt;
    int li, lj;
    //Cell_handle c = T.locate(p, lt, li, lj);
    T.locate(p, lt, li, lj);
    return lt <= Triangulation::CELL;
}


static Point to_cgal(const Vec3d& v)
{
    return Point(v[0], v[1], v[2]);
}

// Deep copy of front end interface dtype to cgal data
template <std::size_t N>
static std::array<Point, N> to_cgal(const std::array<Vec3d, N> &vs)
{
    std::array<Point, N> cs;
    std::size_t i = 0;
    for (const auto& v: vs)
        cs[i++] = to_cgal(v);
    return cs;
}

} // namespace __detail


Octagon::Octagon(const std::array<Vec3d, 8> &vertices) {
    oi = new __detail::_Octagon_Impl(__detail::to_cgal(vertices));
}

Octagon::~Octagon() {
    delete oi;
}

bool Octagon::contains(const Vec3d &p)
{
    return oi->contains(__detail::to_cgal(p));
}

} // namespace tetra
