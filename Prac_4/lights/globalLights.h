#ifndef GLOBAL_LIGHTS_H
#define GLOBAL_LIGHTS_H

#include <vector>
#include "light.h"
#include "../sceneClasses/drawerVisitor.h"

class GlobalLights
{
private:
    static Colour cycleColour(Colour current, bool forward)
    {
        static const Colour palette[] = {
            Colour::Red,
            Colour::Green,
            Colour::Blue,
            Colour::Yellow,
            Colour::Cyan,
            Colour::Magenta,
            Colour::Orange,
            Colour::Purple,
            Colour::White,
        };

        const int paletteSize = static_cast<int>(sizeof(palette) / sizeof(palette[0]));
        int index = 0;
        for (int i = 0; i < paletteSize; i++)
        {
            if (palette[i] == current)
            {
                index = i;
                break;
            }
        }

        if (forward)
            index = (index + 1) % paletteSize;
        else
            index = (index - 1 + paletteSize) % paletteSize;

        return palette[index];
    }

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

    void cycleLightColours(bool forward)
    {
        for (size_t i = 0; i < lights.size(); i++)
        {
            Colour next = cycleColour(lights[i]->getColourEnum(), forward);
            lights[i]->setColour(next);
            replaceVisitor(i, new DrawerVisitor(lights[i]->getShape()));
        }
    }

    void clear()
    {
        lights.clear();
        visitors.clear();
    }
};

#endif
