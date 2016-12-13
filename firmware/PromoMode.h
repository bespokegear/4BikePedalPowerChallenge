#pragma once

#include "Mode.h"

class _PromoMode : public Mode {
public:
    enum Stage {
        PlayerLit,
        PlayerFade
    };
    _PromoMode();
    void start();
    void stop();
    void modeUpdate();
    bool isFinished() { return _done; }

private:
    int16_t _wipe;
    unsigned long _last;
    uint8_t _player;
    Stage _stage;
    unsigned long _stageStart;
    bool _done;

    void lightPlayer(uint8_t player);
    void setStage(Stage stage);
    void startFade();

};

extern _PromoMode PromoMode;
