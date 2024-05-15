#pragma once

struct Screenbounds final
{
    friend class Singleton;
    
    explicit Screenbounds(const unsigned int width, const unsigned int height) : width(width), height(height) {}

    const unsigned int width;
    const unsigned int height;
};
