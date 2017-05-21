#ifndef GRAPHICS_OBJECT_H
#define GRAPHICS_OBJECT_H

#include "CWObject.h"

class GraphicsObject :public CWObject
{
private:
    Mesh* mesh;
    glm::vec3 worldPosition;
    float scale;

    std::vector<struct CWKeyframe> keyframes;
    int keyframeIndex;
public:
    glm::quat rotation;
    GraphicsObject(Mesh* myMesh, glm::vec3 initialPosition, glm::quat initialRotation)
    {
        mesh = myMesh;
        worldPosition = initialPosition;
        rotation = initialRotation;
        scale = 1.0f;

        keyframeIndex = 0;
    }

    GraphicsObject(Mesh* myMesh, glm::vec3 initialPosition, glm::quat initialRotation, float meshScale)
    {
        mesh = myMesh;
        worldPosition = initialPosition;
        rotation = initialRotation;
        scale = meshScale;

        keyframeIndex = 0;
    }

    virtual void MotionTween(float time)
    {
        if(keyframeIndex < (int) keyframes.size() - 1)
        {
            if(time > keyframes[keyframeIndex + 1].time)
            {
                keyframeIndex++;
            }

            float timeDiff = keyframes[keyframeIndex + 1].time - keyframes[keyframeIndex].time;
            float timeNow = time - keyframes[keyframeIndex].time;
            float tweenFactor = timeNow / timeDiff;

            glm::vec3 translationDiff = keyframes[keyframeIndex + 1].position - keyframes[keyframeIndex].position;
            worldPosition = keyframes[keyframeIndex].position + translationDiff * tweenFactor;

            rotation = glm::slerp(keyframes[keyframeIndex].orientation, keyframes[keyframeIndex + 1].orientation, tweenFactor);

        }
    }

    virtual void Draw(Shader shader, glm::mat4& view, glm::mat4& projection, const std::vector<LightSource*> &lights, glm::mat4& lightSpace)
    {
        glm::mat4 model;
        model = glm::translate(model, this->worldPosition);
        model = glm::rotate(model, glm::angle(rotation), glm::axis(rotation));
        model = glm::scale(model, glm::vec3(scale));

        glm::mat4 MVP = projection * view * model;

        GLint mvpLocation = glGetUniformLocation(shader.getShaderProgram(), "MVPmatrix");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(MVP));

        GLint modelLocation = glGetUniformLocation(shader.getShaderProgram(), "modelMatrix");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

        //Calculate the normal matrix for the vertices
        glm::mat3 normalMatrix = glm::mat3(glm::transpose(glm::inverse(model)));
        GLint normalMatrixLoc = glGetUniformLocation(shader.getShaderProgram(), "normalMatrix");
        glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));

        GLint lightSpaceLocation = glGetUniformLocation(shader.getShaderProgram(), "lightSpace");
        glUniformMatrix4fv(lightSpaceLocation, 1, GL_FALSE, glm::value_ptr(lightSpace));

        mesh->Draw(shader, lights);
    }

    /* Alternative version of Draw takes the transform of the object directly */
    void Draw(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection, const std::vector<LightSource*> &lights)
    {
        glm::mat4 MVP = projection * view * model;

        GLint mvpLocation = glGetUniformLocation(shader.getShaderProgram(), "MVPmatrix");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(MVP));

        GLint modelLocation = glGetUniformLocation(shader.getShaderProgram(), "modelMatrix");
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));



        mesh->Draw(shader, lights);
    }

    void addKeyframe(struct CWKeyframe newKey)
    {
        keyframes.push_back(newKey);
    }

    void setPostion(glm::vec3 newPos)
    {
        worldPosition = newPos;
    }

    void setRotation(glm::quat newRot)
    {
        rotation = newRot;
    }
};

#endif // GRAPHICS_OBJECT_H
