#ifndef GLOBAL_LIGHTS_H
#define GLOBAL_LIGHTS_H

#include <vector>
#include "light.h"

class GlobalLights
{
private:
    GlobalLights() = default;
    ~GlobalLights()
    {
        for (Light *l : this->lights)
        {
            delete l;
        }
    }

    GlobalLights(const GlobalLights &) = delete;
    GlobalLights &operator=(const GlobalLights &) = delete;

    std::vector<Light *> lights;

public:
    static GlobalLights &getInstance()
    {
        static GlobalLights instance;
        return instance;
    }

    void addLight(Light *light)
    {
        lights.push_back(light);
    }

    const std::vector<Light *> &getLights() const
    {
        return lights;
    }

    void clear()
    {
        lights.clear();
    }
};

#endif
