#ifndef ENTITY_CPP
#define ENTITY_CPP

#include <glm/glm.hpp>
#include <glad/glad.h>

class Entity {
public:
    //somethings here and there
    glm::vec3 oPosition;             //position in 3d world
    glm::vec3 oFacingDirection;          //heading direction ("looking at")
    glm::vec3 oSpeedVector;
    //maybe model?

private:
    //other things
};

#endif