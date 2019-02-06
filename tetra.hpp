
#ifndef TETRA_HPP_INCLUDED
#define TETRA_HPP_INCLUDED

#include <array>
#include <memory>

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
    Octagon(const Octagon& o) = delete;
    Octagon(Octagon&& o);
    ~Octagon();
    void operator=(Octagon o);

    bool contains(const Vec3d &p) const;
    bool contains(double x, double y, double z) const;
    

private:
    std::unique_ptr<__detail::_Octagon_Impl> oi;

    friend void swap(Octagon&, Octagon&);
};

} // namespace tetra

#endif

