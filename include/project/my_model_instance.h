//
// Created by ivan on 6/23/21.
//

#ifndef MI18085_RG_PROJEKAT_MY_MODEL_INSTANCE_H
#define MI18085_RG_PROJEKAT_MY_MODEL_INSTANCE_H

#include <learnopengl/model.h>
#include <learnopengl/shader.h>

bool showNormals = false;
void swap_showNormals() {
    showNormals = !showNormals;
}

class MyModelInstance {

    Model* model;
    Shader* shader;
    Shader* normalShader;
public:
    MyModelInstance(string modelPath, string shaderName) {
        this->shader = new Shader(("resources/shaders/" + shaderName + ".vs").c_str(), ("resources/shaders/" + shaderName + ".fs").c_str());
        this->model = new Model(("resources/objects/" + modelPath).c_str());
        this->model->SetShaderTextureNamePrefix("material.");

        this->normalShader = new Shader("resources/shaders/9.3.normal_visualization.vs", "resources/shaders/9.3.normal_visualization.fs", "resources/shaders/9.3.normal_visualization.gs");
    }

    void Draw(glm::mat4 model, vector<Light> lights) {
        // don't forget to enable shader before setting uniforms
        this->shader->use();

        this->shader->setInt("nrLights", lights.size());

        for(int i = 0; i < lights.size(); i++) {
            this->shader->setInt("lights["+to_string(i)+"].type", lights[i].type);
            this->shader->setVec3("lights["+to_string(i)+"].position", lights[i].position);
            this->shader->setVec3("lights["+to_string(i)+"].direction", lights[i].direction);
            this->shader->setVec3("lights["+to_string(i)+"].ambient", lights[i].ambient);
            this->shader->setVec3("lights["+to_string(i)+"].diffuse", lights[i].diffuse);
            this->shader->setVec3("lights["+to_string(i)+"].specular", lights[i].specular);
            this->shader->setFloat("lights["+to_string(i)+"].constant", lights[i].constant);
            this->shader->setFloat("lights["+to_string(i)+"].linear", lights[i].linear);
            this->shader->setFloat("lights["+to_string(i)+"].quadratic", lights[i].quadratic);
            this->shader->setFloat("lights["+to_string(i)+"].cutOff", lights[i].cutOff);
            this->shader->setFloat("lights["+to_string(i)+"].outerCutOff", lights[i].outerCutOff);
        }
        this->shader->setVec3("viewPos", programState->camera.Position);
        this->shader->setFloat("material.shininess", 32.0f);

        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(programState->camera.Zoom),
                                                (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = programState->camera.GetViewMatrix();
        this->shader->setMat4("projection", projection);
        this->shader->setMat4("view", view);

        this->shader->setMat4("model", model);
        this->model->Draw(*(this->shader));

        if(showNormals) {
            this->normalShader->use();
            this->normalShader->setMat4("projection", projection);
            this->normalShader->setMat4("view", view);
            this->normalShader->setMat4("model", model);
            this->model->Draw(*(this->normalShader));
        }
    }
};

#endif //MI18085_RG_PROJEKAT_MY_MODEL_INSTANCE_H
