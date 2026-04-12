//
// Coordinate conversion utilities.
// World-space uses Cartesian Y-up (physics, shape data).
// Screen-space uses Y-down (raylib rendering, camera, mouse input).
//

#ifndef ORBITAL_MECHANICS_COORDS_H
#define ORBITAL_MECHANICS_COORDS_H

#include "raylib.h"

namespace coords {

    inline Vector2 screenToWorld(Vector2 screen) {
        return { screen.x, -screen.y };
    }

    inline Vector2 worldToScreen(Vector2 world) {
        return { world.x, -world.y };
    }

}

#endif //ORBITAL_MECHANICS_COORDS_H
