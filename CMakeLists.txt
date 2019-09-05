cmake_minimum_required(VERSION 3.10)
project(roguelike)
set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES
        Main.cpp
        ConstSettings.h
        Random.cpp Random.h
        Direction.h Direction.cpp

        engine/Window.cpp engine/Window.h
        engine/GameObject.cpp engine/GameObject.h
        engine/Stage.cpp engine/Stage.h
        engine/ResourceLoader.cpp engine/ResourceLoader.h
        engine/StageManager.cpp engine/StageManager.h
        engine/Inputs.cpp engine/Inputs.h
        engine/TextureGroup.cpp engine/TextureGroup.h
        engine/DirectionalTextureGroup.cpp engine/DirectionalTextureGroup.h
        engine/ApplicationStatus.h
        levels/TileType.h levels/TileType.cpp

        levels/LevelTiles.cpp levels/LevelTiles.h
        levels/LevelTilesPathfinding.cpp levels/LevelTilesPathfinding.h
        levels/LevelGenerator.cpp levels/LevelGenerator.h
        levels/Room.cpp levels/Room.h
        levels/LevelManipulator.cpp
        levels/LevelManipulator.h
        levels/RoomGroup.cpp levels/RoomGroup.h

        gameobject/ProjectileGO.cpp gameobject/ProjectileGO.h
        gameobject/ProjectilesGO.cpp gameobject/ProjectilesGO.h
        gameobject/PictureGO.cpp gameobject/PictureGO.h
        gameobject/SpriteGO.cpp gameobject/SpriteGO.h
        gameobject/DamageableGO.cpp gameobject/DamageableGO.h
        gameobject/LevelGO.cpp gameobject/LevelGO.h
        gameobject/FogGO.cpp gameobject/FogGO.h
        gameobject/PlayerGO.cpp gameobject/PlayerGO.h

        gameobject/enemy/EnemiesGO.cpp gameobject/enemy/EnemiesGO.h
        gameobject/enemy/EnemyGO.cpp gameobject/enemy/EnemyGO.h
        gameobject/enemy/EnemyType.h
        gameobject/enemy/EnemyFactory.cpp gameobject/enemy/EnemyFactory.h

        stages/MenuStage.cpp stages/MenuStage.h
        stages/GameStage.cpp stages/GameStage.h
        )

if (WIN32)  #windows
    #localizing sfml files on windows - assumes they are in folder below:
    set(SFML_LOC "c:/sfml64/")

    set(SFML_INCLUDE_DIR "${SFML_LOC}include")
    set(SFML_LIB_DIR "${SFML_LOC}lib")
    include_directories(${SFML_INCLUDE_DIR})
    link_directories(${SFML_LIB_DIR})
    link_libraries("-static")
    add_executable(roguelike ${SOURCE_FILES})
    set(LIBRARY_FILES sfml-main-d.a;sfml-system-d.a;sfml-window-d.a;sfml-graphics-d.a;sfml-audio-d.a)
    target_link_libraries(roguelike ${LIBRARY_FILES})
endif()
if (UNIX AND NOT APPLE) #linux compilation - assumes files are downloaded from repository
    add_executable(roguelike ${SOURCE_FILES})
    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
    find_package(SFML REQUIRED system window graphics network audio)
    if (SFML_FOUND)
        include_directories(${SFML_INCLUDE_DIR})
        target_link_libraries(simulator ${SFML_LIBRARIES})
    endif()
endif()
