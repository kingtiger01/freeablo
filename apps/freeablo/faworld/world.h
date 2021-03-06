#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <map>
#include <utility>

#include "../engine/inputobserverinterface.h"


namespace FARender
{
    class RenderState;
}

namespace DiabloExe
{
    class DiabloExe;
}

namespace FAWorld
{
    class Actor;
    class Player;
    class GameLevel;

    // at 125 ticks/second, it will take about 200 days to reach max value, so int32 will probably do :p
    typedef int64_t Tick;
    static const Tick MAX_TICK = 214748364;

    class World : public Engine::KeyboardInputObserverInterface, public Engine::MouseInputObserverInterface
    {
        public:
            World(const DiabloExe::DiabloExe& exe);
            ~World();

            static World* get();
            void notify(Engine::KeyboardInputAction action);
            void notify(Engine::MouseInputAction action, Engine::Point mousePosition);
            void generateLevels();
            GameLevel* getCurrentLevel();
            size_t getCurrentLevelIndex();

            void setLevel(size_t levelNum);
            GameLevel* getLevel(size_t level);
            void insertLevel(size_t level, GameLevel* gameLevel);

            Actor* getActorAt(size_t x, size_t y);

            void update(bool noclip);

            void addCurrentPlayer(Player * player);
            Player* getCurrentPlayer();

            void registerPlayer(Player* player);
            void deregisterPlayer(Player* player);
            const std::vector<Player*>& getPlayers();

            void fillRenderState(FARender::RenderState* state);

            static const Tick ticksPerSecond = 125; ///< number of times per second that game state will be updated
            static Tick getTicksInPeriod(float seconds);
            static float getSecondsPerTick();

            Actor* getActorById(int32_t id);

            void getAllActors(std::vector<Actor*>& actors);

            Tick getCurrentTick();

        private:
            void playLevelMusic(size_t level);
            void changeLevel(bool up);
            void stopPlayerActions();
            void onMouseClick(Engine::Point mousePosition);
            void onMouseDown(Engine::Point mousePosition);

            std::map<size_t, GameLevel*> mLevels;
            Tick mTicksPassed = 0;
            Player* mCurrentPlayer;
            std::vector<Player*> mPlayers; ///< This vector is sorted
            const DiabloExe::DiabloExe& mDiabloExe;
    };
}

#endif
