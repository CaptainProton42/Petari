#include "Game/Enemy/KameckBeamHolder.hpp"
#include "Game/Enemy/KameckBeam.hpp"
#include "Game/Enemy/KameckFireBall.hpp"
#include "Game/Enemy/KameckTurtle.hpp"
#include "Game/Scene/SceneObjHolder.hpp"

namespace {
    static const s32 sMaxKameckBeam = 16;
    static const s32 sMaxKameckFireBall = 16;
    static const s32 sMaxKameckBeamTurtle = 16;
};  // namespace

KameckBeamHolder::KameckBeamHolder() : DeriveActorGroup< KameckBeam >("カメックビーム管理", ::sMaxKameckBeam) {
    KameckBeam* kameckBeam;

    for (s32 i = 0; i < ::sMaxKameckBeam; i++) {
        kameckBeam = new KameckBeam("カメックビーム");
        kameckBeam->initWithoutIter();
        registerActor(kameckBeam);
    }
}

KameckFireBallHolder::KameckFireBallHolder() : DeriveActorGroup< KameckFireBall >("カメック火の玉管理", ::sMaxKameckFireBall) {
    KameckFireBall* kameckFireBall;

    for (s32 i = 0; i < ::sMaxKameckFireBall; i++) {
        kameckFireBall = new KameckFireBall("カメックビーム用炎");
        kameckFireBall->initWithoutIter();
        kameckFireBall->makeActorDead();
        registerActor(kameckFireBall);
    }
}

KameckBeamTurtleHolder::KameckBeamTurtleHolder() : DeriveActorGroup< KameckTurtle >("カメックビーム用カメ管理", ::sMaxKameckBeamTurtle) {
    KameckTurtle* kameckTurtle;

    for (s32 i = 0; i < ::sMaxKameckBeamTurtle; i++) {
        kameckTurtle = new KameckTurtle("カメックビーム用カメ");
        kameckTurtle->initWithoutIter();
        kameckTurtle->makeActorDead();
        registerActor(kameckTurtle);
    }
}

namespace MR {
    void createKameckBeamHolder() {
        MR::createSceneObj(SceneObj_KameckBeamHolder);
    }

    void createKameckFireBallHolder() {
        MR::createSceneObj(SceneObj_KameckFireBallHolder);
    }

    void createKameckBeamTurtleHolder() {
        MR::createSceneObj(SceneObj_KameckBeamTurtleHolder);
    }

    KameckBeam* startFollowKameckBeam(s32 beamKind, MtxPtr pMtx, f32 scale, const TVec3f& rWandLocalPos, KameckBeamEventListener* pEventListener) {
        KameckBeam* kameckBeam = getKameckBeam();

        if (kameckBeam == nullptr) {
            return nullptr;
        }

        kameckBeam->setBeamKind(beamKind);

        if (!kameckBeam->requestFollowWand(pMtx, scale)) {
            return nullptr;
        }

        kameckBeam->setWandLocalPosition(rWandLocalPos);
        kameckBeam->setEventListener(pEventListener);

        return kameckBeam;
    }

    KameckBeam* getKameckBeam() {
        KameckBeamHolder* kameckBeamHolder = MR::getSceneObj< KameckBeamHolder >(SceneObj_KameckBeamHolder);

        if (kameckBeamHolder->getDeadActor()) {
            return static_cast< KameckBeam* >(kameckBeamHolder->getDeadActor());
        }

        return nullptr;
    }

    KameckFireBall* getKameckFireBall() {
        KameckFireBallHolder* kameckFireBallHolder = MR::getSceneObj< KameckFireBallHolder >(SceneObj_KameckFireBallHolder);

        if (kameckFireBallHolder->getDeadActor()) {
            return static_cast< KameckFireBall* >(kameckFireBallHolder->getDeadActor());
        }

        return nullptr;
    }

    KameckTurtle* getKameckBeamTurtle() {
        KameckBeamTurtleHolder* kameckBeamTurtleHolder = MR::getSceneObj< KameckBeamTurtleHolder >(SceneObj_KameckBeamTurtleHolder);

        if (kameckBeamTurtleHolder->getDeadActor()) {
            return static_cast< KameckTurtle* >(kameckBeamTurtleHolder->getDeadActor());
        }

        return nullptr;
    }
};  // namespace MR
