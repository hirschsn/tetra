
#include "tetra.hpp"

#define CGAL_DISABLE_ROUNDING_MATH_CHECK
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Triangulation_3.h>
#include <boost/iterator/transform_iterator.hpp>

namespace tetra
{

namespace __detail {

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef CGAL::Triangulation_3<K>      Triangulation;
typedef Triangulation::Point          Point;
typedef Triangulation::Locate_type    Locate_type;

static Point vec2point(const Vec3d& v)
{
    return Point(v[0], v[1], v[2]);
}

struct _Octagon_Impl
{
    _Octagon_Impl(const std::array<Vec3d, 8> &vertices);
    const Triangulation T;
};

_Octagon_Impl::_Octagon_Impl(const std::array<Vec3d, 8> &vertices)
    : T(boost::make_transform_iterator(vertices.begin(), vec2point),
        boost::make_transform_iterator(vertices.end(), vec2point)) {}

static bool contains(const _Octagon_Impl &oi, const Vec3d &v)
{
    Point p = vec2point(v);
    Locate_type lt;
    int li, lj;
    oi.T.locate(p, lt, li, lj);
    return lt <= Triangulation::CELL;
}

} // namespace __detail


// These are declared here because _Octagon_Impl is an imcomplete type in the header.
Octagon::Octagon() = default;
Octagon::~Octagon() = default;
Octagon::Octagon(Octagon&& o) = default;

Octagon::Octagon(const std::array<Vec3d, 8> &vertices)
    : oi( std::make_unique<__detail::_Octagon_Impl>(vertices)) {}

bool Octagon::contains(const Vec3d &p) const
{
    if (!oi)
        throw std::runtime_error("contains() on empty octagon");
    return __detail::contains(*oi, p);
}

bool Octagon::contains(double x, double y, double z) const
{
    return contains({{x, y, z}});
}

void Octagon::operator=(Octagon o)
{
    swap(*this, o);
}

void swap(Octagon& a, Octagon& b) {
    std::swap(a.oi, b.oi);
}

} // namespace tetra

