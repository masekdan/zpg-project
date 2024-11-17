#ifndef FLASHLIGHT_CLASS_H
#define FLASHLIGHT_CLASS_H

#include "SpotLight.h"
#include "Observer.h"
#include "Camera.h"


class Flashlight : public SpotLight, public Observer
{
private:
    Camera* camera;
public:
    Flashlight(glm::vec3 position, glm::vec3 direction, float angle,glm::vec3 attenuation);
    void update() override;
    void registerSubject(Subject* subject) override;
};


#endif
