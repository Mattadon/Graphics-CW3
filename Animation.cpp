#include "Include/Animation.h"

#include "Include/Introduction.h"
#include "Include/tank/TankObject.h"
#include "Include/transport/TransportObject.h"
#include "Include/CWObject.h"
#include "Include/Light.h"
#include "Include/BLCamera.h"

void SetupAnimation(TankObject &duskTank, TankObject &dawnTank, TransportObject &duskTransport, TransportObject &dawnTransport, ThreeD_Camera &camera)
{
    /* Fly in */
    glm::vec3 duskTankOffset(0.0f, -2.0f, 2.0f);
    glm::vec3 dawnTankOffset(0.0f, -2.0f, -2.0f);;

    glm::quat dawnRotation = glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    glm::vec3 duskTeamSpawn(0.0f, 20.0f, -600.0f);
    glm::vec3 duskTeamLanding(0.0f, 20.0f, -60.0f);

    glm::vec3 dawnTeamSpawn(0.0f, 20.0f, 600.0f);
    glm::vec3 dawnTeamLanding(0.0f, 20.0f, 50.0f);

    camera.addKeyframe({glm::vec3(-60.0f, 20.0f, -30.0f), glm::vec3(-60.0f, 60.0f, -100.0f), 0.0f});
    camera.addKeyframe({glm::vec3(-60.0f, 20.0f, -30.0f), glm::vec3(-60.0f, 60.0f, -100.0f), 5.0f});
    camera.addKeyframe({glm::vec3(-80.0f, 20.0f, -30.0f), glm::vec3(0.0f, 20.0f, 0.0f), 10.0f});
    camera.addKeyframe({glm::vec3(-80.0f, 20.0f, -60.0f), glm::vec3(0.0f, -100.0f, 0.0f), 15.0f});
    camera.addKeyframe({duskTeamLanding + glm::vec3(-10.0f, 0.0f, -5.0f), duskTeamLanding, 20.0f});
    camera.addKeyframe({duskTeamLanding + glm::vec3(-5.0f, 0.0f, -15.0f), duskTeamLanding, 22.0f});
    camera.addKeyframe({duskTeamLanding + glm::vec3(10.0f, 0.0f, -15.0f), duskTeamLanding + duskTankOffset, 25.0f});

    duskTank.addKeyframe({duskTeamSpawn + duskTankOffset, glm::quat(), 0.0f});
    duskTank.addTurretKeyframe({0.0f, 0.0f});
    duskTank.addCannonKeyframe({0.0f, 0.0f});
    duskTransport.addKeyframe({duskTeamSpawn, glm::quat(), 0.0f});
    duskTransport.addArm1Keyframe({0.0f, 0.0f});
    duskTransport.addArm2Keyframe({0.0f, 0.0f});

    duskTank.addKeyframe({duskTeamLanding + duskTankOffset, glm::quat(), 20.0f});
    duskTransport.addKeyframe({duskTeamLanding, glm::quat(), 20.0f});
    duskTransport.addArm1Keyframe({0.0f, 20.0f});
    duskTransport.addArm2Keyframe({0.0f, 20.0f});

    dawnTank.addKeyframe({dawnTeamSpawn + dawnTankOffset, dawnRotation, 0.0f});
    dawnTank.addTurretKeyframe({0.0f, 0.0f});
    dawnTank.addCannonKeyframe({0.0f, 0.0f});
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

    camera.addKeyframe({duskTeamLanding + glm::vec3(10.0f, 0.0f, -15.0f), duskTeamLanding + duskTankOffset, 28.0f});
    camera.addKeyframe({duskTeamLanding + glm::vec3(0.0f, -14.0f, 2.0f) + glm::vec3(0.0f, 3.0f, -8.0f), duskTeamLanding + glm::vec3(0.0f, -12.0f, 2.0f), 30.0f});
    camera.addKeyframe({duskTeamLanding + glm::vec3(0.0f, -17.0f, 2.0f) + glm::vec3(0.0f, 3.0f, -8.0f), duskTeamLanding + glm::vec3(0.0f, -15.0f, 2.0f), 30.5f});
    camera.addKeyframe({duskTeamLanding + glm::vec3(0.0f, -16.0f, 2.0f) + glm::vec3(0.0f, 3.0f, -8.0f), duskTeamLanding + glm::vec3(0.0f, -14.0f, 2.0f), 31.0f});

    /* Transports leave */

    duskTransport.addArm1Keyframe({30.0f, 30.0f});
    duskTransport.addArm2Keyframe({30.0f, 30.0f});
    duskTransport.addArm1Keyframe({0.0f, 31.0f});
    duskTransport.addArm2Keyframe({0.0f, 31.2f});

    duskTransport.addKeyframe({duskTeamLanding, glm::quat(), 31.5f});
    duskTransport.addKeyframe({duskTeamLanding - glm::vec3(0.0f, 0.0f, -2.0f), glm::angleAxis(glm::radians(60.0f), glm::normalize(glm::vec3(0.0, 1.0f, 0.3f))), 32.5f});
    duskTransport.addKeyframe({duskTeamLanding - glm::vec3(0.0f, 0.0f, -4.0f), glm::angleAxis(glm::radians(120.0f), glm::normalize(glm::vec3(0.0, 1.0f, -0.3f))), 33.5f});
    duskTransport.addKeyframe({duskTeamLanding - glm::vec3(0.0f, 0.0f, -6.0f), glm::angleAxis(glm::radians(180.0f), glm::vec3(0.0, 1.0f, 0.0f)), 34.5f});
    duskTransport.addKeyframe({duskTeamSpawn, dawnRotation, 54.5f});

    dawnTransport.addArm1Keyframe({30.0f, 30.5f});
    dawnTransport.addArm2Keyframe({30.0f, 30.6f});
    dawnTransport.addArm1Keyframe({0.0f, 31.4f});
    dawnTransport.addArm2Keyframe({0.0f, 31.1f});

    dawnTransport.addKeyframe({dawnTeamLanding, dawnRotation, 32.0f});
    dawnTransport.addKeyframe({dawnTeamLanding, glm::angleAxis(glm::radians(90.0f), glm::normalize(glm::vec3(0.0, 1.0f, 0.2f))), 33.0f});
    dawnTransport.addKeyframe({dawnTeamLanding, glm::quat(), 34.0f});
    dawnTransport.addKeyframe({dawnTeamSpawn, glm::quat(), 54.0f});

    duskTank.addFireKeyframe(36.0f);
    dawnTank.addFireKeyframe(35.0f);

    /* Tanks attack */

    glm::vec3 duskStart = duskTeamLanding + glm::vec3(0.0f, -16.0f, 2.0f);
    glm::vec3 dawnStart = dawnTeamLanding + glm::vec3(0.0f, -16.0f, -2.0f);

    duskTank.addKeyframe({duskStart, glm::quat(), 33.3f});
    dawnTank.addKeyframe({dawnStart, dawnRotation, 33.0f});

    duskTank.addKeyframe({dawnStart, glm::angleAxis(glm::radians(5.0f), glm::vec3(1.0f, 0.0f, 0.0f)), 38.5f});
    duskTank.addTurretKeyframe({0.0f, 35.0f});
    duskTank.addTurretKeyframe({-30.0f, 38.0f});

    dawnTank.addKeyframe({dawnStart + glm::vec3(-20.0f, 0.0f, 0.0f), glm::angleAxis(glm::radians(30.0f), glm::normalize(glm::vec3(0.0f, -0.5f, -1.0f))) * dawnRotation, 35.0f});
    dawnTank.addKeyframe({dawnStart + glm::vec3(-30.0f, 0.0f, -20.0f), glm::angleAxis(glm::radians(60.0f), glm::normalize(glm::vec3(0.0f, -1.0f, -0.5f))) * dawnRotation, 36.0f});
    dawnTank.addTurretKeyframe({0.0f, 34.0f});
    dawnTank.addTurretKeyframe({-45.0f, 35.5f});

    duskTank.addKeyframe({dawnStart, dawnRotation, 40.0f});
    duskTank.addKeyframe({dawnStart + glm::vec3(-10.0f, 0.0f, -20.0f), glm::angleAxis(glm::radians(-10.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * dawnRotation, 42.0f});
    duskTank.addKeyframe({glm::vec3(-10.0f, 4.0f, -60.0f), glm::angleAxis(glm::radians(-120.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::angleAxis(glm::radians(-10.0f), glm::vec3(0.0f, 0.0f, 1.0f)) * dawnRotation, 48.0f});
    duskTank.addKeyframe({glm::vec3(-10.0f, 4.0f, -60.0f), glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 49.0f});
    duskTank.addTurretKeyframe({-30.0f, 39.0f});
    duskTank.addTurretKeyframe({20.0f, 41.0f});
    duskTank.addTurretKeyframe({-40.0f, 50.0f});
    duskTank.addTurretKeyframe({10.0f, 53.0f});
    duskTank.addFireKeyframe(45.0f);

    dawnTank.addKeyframe({glm::vec3(30.0f, 4.0f, -50.0f), glm::angleAxis(glm::radians(60.0f), glm::normalize(glm::vec3(0.0f, -1.0f, 0.0f))) * dawnRotation, 44.0f});
    dawnTank.addTurretKeyframe({-60.0f, 36.0f});
    dawnTank.addTurretKeyframe({-125.0f, 39.5f});
    dawnTank.addTurretKeyframe({0.0f, 49.0f});
    dawnTank.addFireKeyframe(39.0f);
    dawnTank.addKeyframe({glm::vec3(30.0f, 4.0f, -50.0f), glm::angleAxis(glm::radians(-110.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 49.0f});

    camera.addKeyframe({duskStart + glm::vec3(0.0f, 3.0f, -8.0f), duskStart + glm::vec3(0.0f, 2.0f, 0.0f), 33.3f});
    camera.addKeyframe({dawnStart + glm::vec3(13.0f, 3.0f, 0.0f), dawnStart + glm::vec3(0.0f, 2.0f, 0.0f), 38.5f});
    camera.addKeyframe({glm::vec3(30.0f, 4.0f, -50.0f) + glm::vec3(20.0f, 3.0f, 0.0f), glm::vec3(30.0f, 4.0f, -50.0f) + glm::vec3(0.0f, 2.0f, 0.0f), 44.0f});
    camera.addKeyframe({glm::vec3(30.0f, 4.0f, -50.0f) + glm::vec3(0.0f, 3.0f, -8.0f), glm::vec3(30.0f, 4.0f, -50.0f) + glm::vec3(0.0f, 2.0f, 0.0f), 49.0f});

    /* Final clash */

    duskTank.addKeyframe({glm::vec3(-10.0f, 4.0f, -60.0f), glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 52.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, 4.0f, -57.0f), glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 53.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, 4.0f, -58.0f), glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 54.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, 4.0f, -57.5f), glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 55.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, 4.0f, -60.0f), glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 57.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, 4.0f, -76.0f), glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 61.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, 2.0f, -79.0f), glm::angleAxis(glm::radians(-30.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 61.5f});
    duskTank.addKeyframe({glm::vec3(8.0f, -2.0f, -81.0f), glm::angleAxis(glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 62.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, -20.0f, -84.0f), glm::angleAxis(glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 65.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, -200.0f, -90.0f), glm::angleAxis(glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 80.0f});
    duskTank.addKeyframe({glm::vec3(8.0f, -600.0f, -90.0f), glm::angleAxis(glm::radians(-180.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::angleAxis(glm::radians(65.0f), glm::vec3(0.0f, 1.0f, 0.0f)), 81.0f});

    dawnTank.addKeyframe({glm::vec3(30.0f, 4.0f, -50.0f), glm::angleAxis(glm::radians(-110.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 52.0f});
    dawnTank.addKeyframe({glm::vec3(12.0f, 4.0f, -54.0f), glm::angleAxis(glm::radians(-110.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 53.0f});
    dawnTank.addKeyframe({glm::vec3(12.0f, 4.0f, -55.0f), glm::angleAxis(glm::radians(-110.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 54.0f});
    dawnTank.addKeyframe({glm::vec3(12.0f, 4.0f, -54.5f), glm::angleAxis(glm::radians(-110.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 55.0f});
    dawnTank.addKeyframe({glm::vec3(12.0f, 4.0f, -57.0f), glm::angleAxis(glm::radians(-110.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 57.0f});
    dawnTank.addKeyframe({glm::vec3(12.0f, 4.0f, -73.0f), glm::angleAxis(glm::radians(-110.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 61.0f});
    dawnTank.addKeyframe({glm::vec3(14.0f, 4.0f, -70.0f), glm::angleAxis(glm::radians(-110.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 62.0f});
    dawnTank.addKeyframe({glm::vec3(15.0f, 4.0f, -66.0f), glm::angleAxis(glm::radians(-140.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0f))), 64.0f});

    camera.addKeyframe({glm::vec3(30.0f, 4.0f, -55.0f) + glm::vec3(0.0f, 3.0f, -8.0f), glm::vec3(10.0f, 4.0f, -55.0f), 52.0f});
    camera.addKeyframe({glm::vec3(30.0f, 4.0f, -79.0f) + glm::vec3(0.0f, 3.0f, -8.0f), glm::vec3(10.0f, 4.0f, -79.0f), 61.0f});
    camera.addKeyframe({glm::vec3(30.0f, 4.0f, -79.0f) + glm::vec3(0.0f, 3.0f, -8.0f), glm::vec3(10.0f, 2.0f, -81.0f), 61.5f});
    camera.addKeyframe({glm::vec3(30.0f, 4.0f, -79.0f) + glm::vec3(0.0f, 3.0f, -8.0f), glm::vec3(10.0f, -2.0f, -84.0f), 62.0f});
    camera.addKeyframe({glm::vec3(30.0f, 4.0f, -79.0f) + glm::vec3(0.0f, 3.0f, -8.0f), glm::vec3(10.0f, -20.0f, -90.0f), 65.0f});
    camera.addKeyframe({glm::vec3(30.0f, 4.0f, -79.0f) + glm::vec3(0.0f, 3.0f, -8.0f), glm::vec3(10.0f, -20.0f, -90.0f), 67.0f});
    camera.addKeyframe({glm::vec3(15.0f, 4.0f, -66.0f) + glm::vec3(0.0f, 3.0f, -8.0f), glm::vec3(15.0f, 4.0f, -66.0f), 70.0f});

    /*
    duskTank.addTurretKeyframe({0.0f, 0.0f});
    duskTank.addTurretKeyframe({45.0f, 10.0f});
    duskTank.addTurretKeyframe({90.0f, 15.0f});
    duskTank.addCannonKeyframe({0.0f, 0.0f});
    duskTank.addCannonKeyframe({0.0f, 7.5f});
    duskTank.addCannonKeyframe({-60.0f, 17.5f});
    */
}
