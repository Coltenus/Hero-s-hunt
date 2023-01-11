cmake_minimum_required(VERSION 3.23)
project(game5)

set(CMAKE_CXX_STANDARD 20)

set(NO_CONSOLE_FLAGS ", -Wl,--subsystem,windows")
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -fexceptions -static -static-libgcc -static-libstdc++ -g -static-libgcc -static-libstdc++ -L")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}${NO_CONSOLE_FLAGS}" )
if (DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )
endif(DEBUG)

set(PROJECT_HEADERS
        game5/src/common.h
        game5/src/characters/enemies/Rogue.h
        game5/main.cpp game5/src/characters/heroes.h
        game5/src/characters/abilities.h
        game5/src/characters/items.h
        game5/src/characters/enemies.h
        game5/src/characters/abilities/sw_abilities.h
        game5/src/characters/abilities/ar_abilities.h
        game5/src/characters/abilities/pal_abilities.h
        game5/src/pages/GameplayEvents/gameplay_events.h
        game5/src/pages.h
        game5/src/characters/heroes/Hero.h
        game5/src/characters/abilities/Ability.h
        game5/src/characters/items/Item.h
        game5/src/utils/Audio.h
        game5/src/pages/Page.h
        game5/src/characters/enemies/Enemy.h
        game5/src/pages/Gameplay.h
        game5/src/characters/items/Healing.h
        game5/src/characters/items/Block.h
        game5/src/characters/items/DmgPotion.h
        game5/src/characters/items/UpMaxHP.h
        game5/src/characters/abilities/Swordsman/SwAb1.h
        game5/src/characters/abilities/Swordsman/SwAb2.h
        game5/src/characters/abilities/Swordsman/SwAb3.h
        game5/src/characters/abilities/Archer/ArAb1.h
        game5/src/characters/abilities/Archer/ArAb2.h
        game5/src/characters/abilities/Archer/ArAb3.h
        game5/src/characters/abilities/Paladin/PalAb1.h
        game5/src/characters/abilities/Paladin/PalAb2.h
        game5/src/characters/abilities/Paladin/PalAb3.h
        game5/src/characters/heroes/Swordsman.h
        game5/src/characters/heroes/Archer.h
        game5/src/characters/heroes/Paladin.h
        game5/src/characters/enemies/Zombie.h
        game5/src/pages/GameplayEvents/GameplayEvent.h
        game5/src/pages/GameplayEvents/Battle.h
        game5/src/utils/Button.h
        game5/src/pages/GameplayEvents/ChooseStart.h
        game5/src/pages/GameplayEvents/Transition.h
        game5/src/pages/GameplayEvents/Reward.h
        game5/src/pages/GameplayEvents/DeadScreen.h
        game5/src/pages/GameplayEvents/Shop.h
        game5/src/pages/GameplayEvents/Rest.h
        game5/src/pages/MainMenu.h
        game5/src/pages/Settings.h
        game5/src/pages/Credits.h
        game5/src/pages/ChooseSave.h
        game5/src/utils/Save.h
        game5/src/utils/TextFrame.h
        game5/src/utils/RadioButton.h
        )
set(PROJECT_SOURCES
        game5/src/characters/enemies/Rogue.cpp
        game5/src/characters/heroes/Hero.cpp
        game5/src/characters/abilities/Ability.cpp
        game5/src/characters/items/Item.cpp
        game5/src/utils/Audio.cpp
        game5/src/pages/Page.cpp
        game5/src/characters/enemies/Enemy.cpp
        game5/src/pages/Gameplay.cpp
        game5/src/characters/items/Healing.cpp
        game5/src/characters/items/Block.cpp
        game5/src/characters/items/DmgPotion.cpp
        game5/src/characters/items/UpMaxHP.cpp
        game5/src/characters/abilities/Swordsman/SwAb1.cpp
        game5/src/characters/abilities/Swordsman/SwAb2.cpp
        game5/src/characters/abilities/Swordsman/SwAb3.cpp
        game5/src/characters/abilities/Archer/ArAb1.cpp
        game5/src/characters/abilities/Archer/ArAb2.cpp
        game5/src/characters/abilities/Archer/ArAb3.cpp
        game5/src/characters/abilities/Paladin/PalAb1.cpp
        game5/src/characters/abilities/Paladin/PalAb2.cpp
        game5/src/characters/abilities/Paladin/PalAb3.cpp
        game5/src/characters/heroes/Swordsman.cpp
        game5/src/characters/heroes/Archer.cpp
        game5/src/characters/heroes/Paladin.cpp
        game5/src/characters/enemies/Zombie.cpp
        game5/src/pages/GameplayEvents/GameplayEvent.cpp
        game5/src/pages/GameplayEvents/Battle.cpp
        game5/src/utils/Button.cpp
        game5/src/pages/GameplayEvents/ChooseStart.cpp
        game5/src/pages/GameplayEvents/Transition.cpp
        game5/src/pages/GameplayEvents/Reward.cpp
        game5/src/pages/GameplayEvents/DeadScreen.cpp
        game5/src/pages/GameplayEvents/Shop.cpp
        game5/src/pages/GameplayEvents/Rest.cpp
        game5/src/pages/MainMenu.cpp
        game5/src/pages/Settings.cpp
        game5/src/pages/Credits.cpp
        game5/src/pages/ChooseSave.cpp
        game5/src/utils/Save.cpp
        game5/src/utils/TextFrame.cpp
        game5/src/utils/RadioButton.cpp
        )

add_executable(game5 ${PROJECT_SOURCES} ${PROJECT_HEADERS})

find_package(raylib CONFIG REQUIRED)
target_include_directories(game5 PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(game5 PRIVATE ${raylib_LIBRARIES})

if (CMAKE_BUILD_TYPE MATCHES Debug)
    add_definitions(-DDEBUG=1)
endif()