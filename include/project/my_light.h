//
// Created by ivan on 6/23/21.
//

#ifndef MI18085_RG_PROJEKAT_MY_LIGHT_H
#define MI18085_RG_PROJEKAT_MY_LIGHT_H

#define LIGHT_TYPE_POINT 0
#define LIGHT_TYPE_DIRECTIONAL 1
#define LIGHT_TYPE_SPOT 2
struct Light {
    int type = LIGHT_TYPE_POINT;

    //point and spot
    glm::vec3 position;

    //directional and spot
    glm::vec3 direction;

    //all
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    //point and spot
    float constant;
    float linear;
    float quadratic;

    //spot
    float cutOff;
    float outerCutOff;

};

#endif //MI18085_RG_PROJEKAT_MY_LIGHT_H
