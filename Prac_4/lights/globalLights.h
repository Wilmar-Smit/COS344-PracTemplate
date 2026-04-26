#ifndef GLOBAL_LIGHTS_H
#define GLOBAL_LIGHTS_H

#include <vector>
#include "light.h"
#include "../sceneClasses/drawerVisitor.h"

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
        for (DrawerVisitor *v : this->visitors)
        {
            if (v) delete v;
        }
    }

    GlobalLights(const GlobalLights &) = delete;
    GlobalLights &operator=(const GlobalLights &) = delete;

    std::vector<Light *> lights;
    std::vector<DrawerVisitor *> visitors;

public:
    static GlobalLights &getInstance()
    {
        static GlobalLights instance;
        return instance;
    }

    void addLight(Light *light)
    {
        lights.push_back(light);
        visitors.push_back(new DrawerVisitor(light->getShape()));
    }

    void replaceVisitor(size_t index, DrawerVisitor *newVisitor)
    {
        if (index < visitors.size())
        {
            if (visitors[index]) delete visitors[index];
            visitors[index] = newVisitor;
        }
    }

    const std::vector<Light *> &getLights() const
    {
        return lights;
    }

    const std::vector<DrawerVisitor *> &getVisitors() const
    {
        return visitors;
    }

    void clear()
    {
        lights.clear();
        visitors.clear();
    }
};

#endif
