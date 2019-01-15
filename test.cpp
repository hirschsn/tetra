
#include <cstdio>
#include <chrono>
#include <random>
#include "tetra.hpp"

struct Randgen
{
    Randgen()
        : mt(std::chrono::high_resolution_clock::now()
                 .time_since_epoch()
                 .count()),
          d(0, 1) {}
    //Randgen(Randintgen &&other)
    //    : mt(std::move(other.mt)), d(std::move(other.d)) {}
    double operator()() { return d(mt); }

  private:
    std::mt19937 mt;
    std::uniform_real_distribution<> d;
};


int ninside(const std::array<tetra::Vec3d, 8>& cs, int N)
{
    auto o = tetra::Octagon{cs};
    auto rnd = Randgen{};
    int n = 0;

    for (int i = 0; i < N; ++i) {
        tetra::Vec3d p = tetra::Vec3d{rnd(), rnd(), rnd()};
        if (o.contains(p))
            n++;
    }
    return n;
}

int main()
{
    // 50% of the volume of the unit cube
    std::array<tetra::Vec3d, 8> cs = {tetra::Vec3d{0, .5,  0},
                                      tetra::Vec3d{0,  0, .5},
                                      tetra::Vec3d{0,  1, .5},
                                      tetra::Vec3d{0, .5,  1},
                                      tetra::Vec3d{1, .5,  0},
                                      tetra::Vec3d{1,  0, .5},
                                      tetra::Vec3d{1,  1, .5},
                                      tetra::Vec3d{1, .5,  1}};

    const int N = 1'000'000;

    int n = ninside(cs, N);

    printf("%5.2lf%%\n", n * 100.0 / N);
}

//#include <array>
//
//#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
//#include <CGAL/Triangulation_3.h>
//
//typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
//typedef CGAL::Triangulation_3<K>      Triangulation;
//typedef Triangulation::Cell_handle    Cell_handle;
////typedef Triangulation::Vertex_handle  Vertex_handle;
//typedef Triangulation::Locate_type    Locate_type;
//typedef Triangulation::Point          Point;
//
//int main()
//{
//    std::vector<Point> cs = {Point(0, 0, 0),
//                             Point(0, 0, 1),
//                             Point(0, 1, 0),
//                             Point(0, 1, 1),
//                             Point(1, 0, 0),
//                             Point(1, 0, 1),
//                             Point(1, 1, 0),
//                             Point(1, 1, 1)};
//
//    Triangulation T(cs.begin(), cs.end());
//    auto n = T.number_of_vertices();
//
//    std::cout << "nvertices: " << n << std::endl;
//
//
//    auto rnd = Randgen{};
//    for (int i = 0; i < 20; ++i) {
//
//        Point p(rnd(), rnd(), rnd());
//
//  Locate_type lt;
//  int li, lj;
//  Cell_handle c = T.locate(p, lt, li, lj);
//  printf("%4.2lf %4.2lf %4.2lf: ", p[0], p[1], p[2]);
//  if (lt > Triangulation::CELL) {
//      std::cout << "Outside.";
//  } else {
//      std::cout << "Inside.";
//  }
//  std::cout << std::endl;
//
//    }
//
////  Locate_type lt;
////  int li, lj;
////  Point p(0.5,1.5,0.5);
////  Cell_handle c = T.locate(p, lt, li, lj);
////  // p is the vertex of c of index li :
////
////  std::cout << p[0] << "," << p[1] << "," << p[2] << ": ";
////  if (lt > Triangulation::CELL) {
////      std::cout << "Outside.";
////  } else {
////      std::cout << "Inside.";
////  }
////  std::cout << std::endl;
////
//  //assert( lt == Triangulation::VERTEX );
//  //assert( c->vertex(li)->point() == p );
//}