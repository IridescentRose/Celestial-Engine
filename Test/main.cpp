#include <Celeste.hpp>

class GameApplication : public Celeste::Core::Application {
public:
    GameApplication() :
        Celeste::Core::Application("MyGame")
    {

    }

    ~GameApplication() override = default;
};

Celeste::Core::Application* CreateNewCelesteApp() {
    return new GameApplication();
}