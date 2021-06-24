#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <learnopengl/filesystem.h>
#include <learnopengl/shader.h>
#include <learnopengl/camera.h>
#include <learnopengl/model.h>

#include <project/program_state.h>
#include <project/my_callbacks.h>
#include <project/my_gl_util.h>
#include <project/my_imgui_util.h>
#include <project/my_model_instance.h>
#include <project/my_mesh_instance.h>

#include <project/my_framebuffer.h>
#include <project/my_skybox.h>

#include <iostream>

int main() {
    GLFWwindow *window = my_init(SCR_WIDTH, SCR_HEIGHT);

    MyModelInstance building("Wooden-Watch-Tower/wooden watch tower2.obj","basic");

    Light dirLight;
    dirLight.type = LIGHT_TYPE_DIRECTIONAL;
    dirLight.position = glm::vec3(4.0f, 4.0, 0.0);
    dirLight.ambient = glm::vec3(0.1, 0.1, 0.1);
    dirLight.diffuse = glm::vec3(0.6, 0.6, 0.6);
    dirLight.specular = glm::vec3(1.0, 1.0, 1.0);

    dirLight.direction = glm::vec3(-0.2f, -1.0f, -0.3f);

    Light& pointLight = programState->pointLight;
    pointLight.type = LIGHT_TYPE_POINT;
    pointLight.position = glm::vec3(0.0f, 8, 0.0);
    pointLight.ambient = glm::vec3(0.1, 0.1, 0.1);
    pointLight.diffuse = glm::vec3(0.6, 0.6, 0.6);
    pointLight.specular = glm::vec3(1.0, 1.0, 1.0);

    pointLight.constant = 1.0f;
    pointLight.linear = 0.09f;
    pointLight.quadratic = 0.032f;


    vector<Light> lights;
    lights.push_back(dirLight);
    lights.push_back(pointLight);

    vector<Vertex> vertices = {
            Vertex(0.5f,  0.5f, 0.0f),  // top right
            Vertex(0.5f, -0.5f, 0.0f),  // bottom right
            Vertex(-0.5f, -0.5f, 0.0f),  // bottom left
            Vertex(-0.5f,  0.5f, 0.0f)   // top left
    };
    vector<unsigned int> indices = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };

    MyMeshInstance ground(vertices,indices,"ground");


    vector<Vertex> vertices2 = {
                     // positions               // normals                    // texture coords
            Vertex(-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f),
            Vertex(0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f),
            Vertex(0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f),
            Vertex(0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f),
            Vertex(-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f),
            Vertex(-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f),

            Vertex(-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f),
            Vertex(0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f),
            Vertex(0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f),
            Vertex(0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f),
            Vertex(-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f),
            Vertex(-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f),

            Vertex(-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f),
            Vertex(-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f),
            Vertex(-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f),
            Vertex(-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f),
            Vertex(-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f),
            Vertex(-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f),

            Vertex(0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f),
            Vertex(0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f),
            Vertex(0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f),
            Vertex(0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f),
            Vertex(0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f),
            Vertex(0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f),

            Vertex(-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f),
            Vertex(0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f),
            Vertex(0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f),
            Vertex(0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f),
            Vertex(-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f),
            Vertex(-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f),

            Vertex(-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f),
            Vertex(0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f),
            Vertex(0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f),
            Vertex(0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f),
            Vertex(-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f),
            Vertex(-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f)
    };

    vector<unsigned int> indices2;
    for(unsigned int i = 0; i < vertices2.size(); i++ ) {
        indices2.push_back(i);
    }

    vector<Texture> textures(2);
    textures[0].id = TextureFromFile("container2_specular.png","resources/textures");
    textures[0].type = "texture_specular";
    textures[0].path = "container2_specular.png";
    textures[1].id = TextureFromFile("container2.png","resources/textures");
    textures[1].type = "texture_diffuse";
    textures[1].path = "container2.png";

    MyMeshInstance specBox(vertices2,indices2,textures,"basic");

    framebuffer_init();
    skybox_init();

    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        framebuffer_first_pass();

        // render
        // ------
        glClearColor(programState->clearColor.r, programState->clearColor.g, programState->clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        lights[0].direction = glm::vec3(-1.0 * cos(currentFrame), -1.0f, -1.0 * sin(currentFrame));


        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,
                               programState->itemPosition); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(programState->itemScale));    // it's a bit too big for our scene, so scale it down

        building.Draw(model, lights);




        glm::mat4 model2 = glm::mat4(1.0f);
        model2 = glm::translate(model2,
                                glm::vec3(0.0f,0.7f,0.0f));
        model2 = glm::scale(model2, glm::vec3(100.0f));
        model2 = glm::rotate(model2, glm::pi<float>()/2, glm::vec3(1.0f, 0.0f, 0.0f));

        ground.Draw(model2, lights);

        glm::mat4 model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3,
                                glm::vec3(5.0f,1.2f,0.0f));
        model3 = glm::scale(model3, glm::vec3(1.0f));
        model3 = glm::rotate(model3, glm::pi<float>()/2, glm::vec3(1.0f, 0.0f, 0.0f));

        specBox.Draw(model3, lights);

        model3 = glm::mat4(1.0f);
        model3 = glm::translate(model3, glm::vec3( 5.0 * cos(currentFrame), 5.0f, 5.0 * sin(currentFrame)));
        model3 = glm::scale(model3, glm::vec3(1.0f));
        model3 = glm::rotate(model3, glm::pi<float>()/2, glm::vec3(1.0f, 0.0f, 0.0f));

        specBox.Draw(model3, lights);

        skybox_draw();

        framebuffer_second_pass();

        if (programState->ImGuiEnabled)
            DrawImGui(programState);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    my_finish();
    return 0;
}