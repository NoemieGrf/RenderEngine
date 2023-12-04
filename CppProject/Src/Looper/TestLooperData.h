#pragma once

#include <array>

static constexpr std::array<float, 4 * (3 + 4 + 2)> TriangleVert =  {
        /* left bottom */  -0.5f, -0.5f, 0.0f,
        /* Color */ 0.2f, 0.5f, 1.7f, 1.0f,
        /* UV */ 0.0f, 0.0f,
        /* right bottom */  0.5f, -0.5f, 0.0f,
        /* Color */ 0.1f, 0.6f, 0.3f, 1.0f,
        /* UV */ 1.0f, 0.0f,
        /* right top */     0.5f, 0.5f, 0.0f,
        /* Color */ 0.8f, 0.2f, 0.1f, 1.0f,
        /* UV */ 1.0f, 1.0f,
        /* left top */     -0.5f, 0.5f, 0.0f,
        /* Color */ 0.8f, 0.2f, 0.1f, 1.0f,
        /* UV */ 0.0f, 1.0f
};

static constexpr std::array<unsigned int, 6> TriangleIndices = {0, 1, 2, 0, 2, 3 };