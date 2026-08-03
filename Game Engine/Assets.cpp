#include "Assets.h"

using namespace nu;
namespace assets {
    Mesh playerMesh{ {Vector2{-1, -1}, Vector2{0, 0}, Vector2{-1, 1}, Vector2{2, 0}, Vector2{-1, -1}}, Color{1.0f, 1.0f, 1.0f} };
    Mesh playerMesh2{ {Vector2{0, 0}, Vector2{-2, -2}, Vector2{-2, 2},Vector2{0, 0}}, Color{0.1333333333f, 0.2941176471f, 1.0f} };
    Model playerModel = vector<Mesh>{ {playerMesh, playerMesh2} };

    Mesh rockMesh1{ {Vector2{-5, -5}, Vector2{-5, 5},Vector2{5, 5},Vector2{5, -5},Vector2{-5, -5}},{1, 1, 1} };
    Mesh rockMesh2{ {Vector2{0, -5}, Vector2{-5, 0},Vector2{0, 5},Vector2{5, 0},Vector2{0, -5}},{1, 1, 1} };
    Model rockModel = vector<Mesh>{ {rockMesh1, rockMesh2} };

    Model enemyModel = vector<Mesh>{ playerMesh };
    Mesh bulletMesh{
  {
    Vector2{ -1, -1 },
    Vector2{ 1, 0 },
    Vector2{ -1, 1 },
    Vector2{ -1, -1 },
  },
  Color{ 1.0f, 0.0f, 0.0f }
    };
    Model bulletModel{ std::vector<Mesh>{bulletMesh}};
}