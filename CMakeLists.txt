cmake_minimum_required(VERSION 3.12)

project(Game)

set(SFML_DIR "SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)
add_executable(Game
    src/main.cpp
    src/Engine.cpp
    src/Engine.h
    src/Button.cpp
    src/Button.h
    src/ResourceManager.cpp
    src/ResourceManager.h

    src/menu/Menu.cpp
    src/menu/Menu.h

    src/game/Game.cpp
    src/game/Game.h
    src/game/Player.cpp
    src/game/Player.h
    src/game/Bullet.cpp
    src/game/Bullet.h
    src/game/Enemy.cpp
    src/game/Enemy.h
    src/game/Collision.cpp
    src/game/Collision.h
    src/game/Life.cpp
    src/game/Life.h
    src/game/Chunk.cpp
    src/game/Chunk.h
    src/game/UpgradeMenu.cpp
    src/game/UpgradeMenu.h
    src/game/ItemDrop.cpp
    src/game/ItemDrop.h
    src/game/Animation.cpp
    src/game/Animation.h
    src/game/Trap.cpp
    src/game/Trap.h
    src/game/Inventory.cpp
    src/game/Inventory.h
)
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system sfml-network)