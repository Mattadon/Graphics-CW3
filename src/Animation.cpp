#include "../Include/Animation.h"

#include "../Include/Introduction.h"
#include "../Include/tank/TankObject.h"
#include "../Include/transport/TransportObject.h"
#include "../Include/CWObject.h"
#include "../Include/Light.h"

void SetupAnimation(TankObject &duskTank, TankObject &dawnTank, TransportObject &duskTransport, TransportObject &dawnTransport)
{
    /* Fly in */
    glm::vec3 duskTankOffset(0.0f, -2.0f, 2.0f);
    glm::vec3 dawnTankOffset(0.0f, -2.0f, -2.0f);;

    glm::quat dawnRotation = glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 duskTeamSpawn(0.0f, 20.0f, -600.0f);
    glm::vec3 duskTeamLanding(0.0f, 20.0f, -60.0f);

    duskTank.addKeyframe({duskTeamSpawn + duskTankOffset, glm::quat(), 0.0f});
    duskTransport.addKeyframe({duskTeamSpawn, glm::quat(), 0.0f});
    duskTransport.addArm1Keyframe({0.0f, 0.0f});
    duskTransport.addArm2Keyframe({0.0f, 0.0f});

    duskTank.addKeyframe({duskTeamLanding + duskTankOffset, glm::quat(), 20.0f});
    duskTransport.addKeyframe({duskTeamLanding, glm::quat(), 20.0f});
    duskTransport.addArm1Keyframe({0.0f, 20.0f});
    duskTransport.addArm2Keyframe({0.0f, 20.0f});

    glm::vec3 dawnTeamSpawn(0.0f, 20.0f, 600.0f);
    glm::vec3 dawnTeamLanding(0.0f, 20.0f, 50.0f);

    dawnTank.addKeyframe({dawnTeamSpawn + dawnTankOffset, dawnRotation, 0.0f});
    dawnTransport.addKeyframe({dawnTeamSpawn, dawnRotation, 0.0f});
    dawnTransport.addArm1Keyframe({0.0f, 0.0f});
    dawnTransport.addArm2Keyframe({0.0f, 0.0f});

    dawnTank.addKeyframe({dawnTeamLanding + dawnTankOffset, dawnRotation, 25.0f});
    dawnTransport.addKeyframe({dawnTeamLanding, dawnRotation, 25.0f});
    dawnTransport.addArm1Keyframe({0.0f, 25.0f});
    dawnTransport.addArm2Keyframe({0.0f, 25.0f});

    /* Release tanks */

    duskTank.addKeyframe({duskTeamLanding + duskTankOffset, glm::quat(), 28.0f});
    duskTransport.addKeyframe({duskTeamLanding, glm::quat(), 28.0f});
    duskTransport.addArm1Keyframe({0.0f, 28.0f});
    duskTransport.addArm2Keyframe({0.0f, 28.0f});

    dawnTank.addKeyframe({dawnTeamLanding + dawnTankOffset, dawnRotation, 28.0f});
    dawnTransport.addKeyframe({dawnTeamLanding, dawnRotation, 28.0f});
    dawnTransport.addArm1Keyframe({0.0f, 28.0f});
    dawnTransport.addArm2Keyframe({0.0f, 28.0f});

    duskTransport.addArm1Keyframe({30.0f, 29.0f});
    duskTransport.addArm2Keyframe({30.0f, 29.0f});

    dawnTransport.addArm1Keyframe({30.0f, 29.0f});
    dawnTransport.addArm2Keyframe({30.0f, 29.0f});

    duskTank.addKeyframe({duskTeamLanding + glm::vec3(0.0f, -14.0f, 2.0f), glm::angleAxis(glm::radians(10.0f), glm::vec3(1.0f, 0.0f, 0.0f)), 30.0f});
    duskTank.addKeyframe({duskTeamLanding + glm::vec3(0.0f, -17.0f, 2.5f), glm::angleAxis(glm::radians(-2.0f), glm::vec3(1.0f, 0.0f, 0.0f)), 30.5f});
    duskTank.addKeyframe({duskTeamLanding + glm::vec3(0.0f, -16.0f, 2.0f), glm::quat(), 31.0f});

    dawnTank.addKeyframe({dawnTeamLanding + glm::vec3(0.0f, -14.0f, -2.0f), glm::angleAxis(glm::radians(-10.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * dawnRotation, 30.2f});
    dawnTank.addKeyframe({dawnTeamLanding + glm::vec3(0.0f, -17.0f, -2.5f), glm::angleAxis(glm::radians(2.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * dawnRotation, 30.7f});
    dawnTank.addKeyframe({dawnTeamLanding + glm::vec3(0.0f, -16.0f, -2.0f), dawnRotation, 31.2f});

    /* Transports leave */

    duskTransport.addArm1Keyframe({30.0f, 30.0f});
    duskTransport.addArm2Keyframe({30.0f, 30.0f});
    duskTransport.addArm1Keyframe({0.0f, 31.0f});
    duskTransport.addArm2Keyframe({0.0f, 31.2f});

    duskTransport.addKeyframe({duskTeamLanding, glm::quat(), 31.5f});
    duskTransport.addArm1Keyframe({0.0f, 31.5f});
    duskTransport.addArm2Keyframe({0.0f, 31.5f});

    /*
    duskTank.addTurretKeyframe({0.0f, 0.0f});
    duskTank.addTurretKeyframe({45.0f, 10.0f});
    duskTank.addTurretKeyframe({90.0f, 15.0f});
    duskTank.addCannonKeyframe({0.0f, 0.0f});
    duskTank.addCannonKeyframe({0.0f, 7.5f});
    duskTank.addCannonKeyframe({-60.0f, 17.5f});
    */
}