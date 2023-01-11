//
// Created by colte on 02.01.2023.
//

#ifndef GAME5_DEADSCREEN_H
#define GAME5_DEADSCREEN_H

#include "GameplayEvent.h"

class DeadScreen : public GameplayEvent {
        private:
        bool active;

        public:
        DeadScreen(Hero**, short);
        ~DeadScreen() = default;
        void Update() override;
        void Draw() override;
        bool IsDone() override;
};


#endif //GAME5_DEADSCREEN_H
