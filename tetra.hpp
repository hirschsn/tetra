
#ifndef TETRA_HPP_INCLUDED
#define TETRA_HPP_INCLUDED

#include <array>

namespace tetra
{

namespace __detail {
// Opaque struct to reduce compile times on include site
struct _Octagon_Impl;
}


typedef std::array<double, 3> Vec3d;

inline Vec3d make_vec3d(double p[3]) {
    return {{p[0], p[1], p[2]}};
}

struct Octagon {
    Octagon();
    Octagon(const std::array<Vec3d, 8> &vertices);
    ~Octagon();
    bool contains(const Vec3d &p) const;

private:
    __detail::_Octagon_Impl *oi;
};

} // namespace tetra

#endif
