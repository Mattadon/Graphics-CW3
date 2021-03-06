#ifndef CW_PHYSICS_LAMP_H
#define CW_PHYSICS_LAMP_H

#include "CWPhysicsObject.h"


class CWPhysicsLamp: public CWPhysicsObject
{
private:
    PointLight &light;
    float timer;
public:
    CWPhysicsLamp(Mesh* myMesh, PhysicsObject* myPhysicsObject, glm::vec3 offset, PointLight &myLight)
    : CWPhysicsObject(myMesh, myPhysicsObject, offset), light(myLight)
    {
        timer = 0.0f;
    }

    void UpdateLight(float dTime)
    {
        light.SetPosition(physicsObject->getPosition());

        //Reset the projectile if it has been travelling for too long
        if(timer > 0.0f)
        {
            timer -= dTime;

            if(timer <= 0.0f)
            {
                this->ResetObject();
            }
        }

    }

    virtual void Draw(Shader shader, glm::mat4& view, glm::mat4& projection, glm::mat4& lightSpace)
    {
        glm::mat4 model;

        glm::vec3 objectPosition = this->physicsObject->getPosition();
        glm::quat objectRotation = this->physicsObject->getRotationQuaternion();

        model = glm::translate(model, position);
        model = glm::translate(model, objectPosition);

        model = glm::rotate(model, glm::angle(objectRotation), glm::axis(objectRotation));

        glm::mat4 MVP = projection * view * model;

        GLint mvpLocation = glGetUniformLocation(shader.getShaderProgram(), "MVPmatrix");
        glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(MVP));

        mesh->Draw(shader);
    }

    void Fire(glm::vec3 newPos, glm::vec3 impulse)
    {
        timer = 5.0f;

        btRigidBody* rigidBody = physicsObject->getRigidBody();

        //If the object had come to rest, it may have deactivated. Reactivate it so that the world starts updating it again.
        rigidBody->activate();

        rigidBody->clearForces();

        //Stop the object moving
        btVector3 zeroVector(0, 0, 0);
        rigidBody->setLinearVelocity(zeroVector);
        rigidBody->setAngularVelocity(zeroVector);

        btTransform newTrans;
        newTrans.setOrigin(btVector3(newPos.x, newPos.y, newPos.z));


        //Teleport the object to its initial position
        rigidBody->setWorldTransform(newTrans);

        physicsObject->applyImpulse(impulse);
    }
};

#endif // CW_PHYSICS_LAMP_H
