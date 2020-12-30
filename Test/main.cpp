#include <Celeste.hpp>

class GameApplication : public Celeste::Core::Application {
public:
    GameApplication() :
        Celeste::Core::Application("MyGame")
    {
        clip = Celeste::createScopePtr<Celeste::Audio::AudioClip>("./test.ogg");
        clip->SetPosition(0, 0, 0);
        clip->Play(0);
    }

    ~GameApplication() override = default;

private:
    Celeste::ScopePtr<Celeste::Audio::AudioClip> clip;
};

Celeste::Core::Application* CreateNewCelesteApp() {
    return new GameApplication();
}