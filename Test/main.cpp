#include <Celeste.hpp>

using namespace Celeste;
using namespace Celeste::Core;

class GameApplication : public Application {
public:
    GameApplication(){
        //For more detailed applications, push back a state!
        clip = createScopePtr<Audio::AudioClip>("./test.ogg");
        clip->SetPosition(0.0f, 0.0f, 0);
        clip->Play(0);
    }

    ~GameApplication() override = default;

private:
    ScopePtr<Audio::AudioClip> clip;
};

Application* CreateNewCelesteApp() {
    PlatformLayer::initializeWithSettings(ApplicationEngineConfig::defaultConfig);
    return new GameApplication();
}