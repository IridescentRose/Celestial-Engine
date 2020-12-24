/**
 * This is your main entry point - it automatically sets things up!
 */
#pragma once

#include <Core/Application.hpp>
#include <Utilities/Utilities.hpp>
extern Celeste::Core::Application* CreateNewCelesteApp();

/**
 * This function initializes all utilities which can be used during headless operation.
 */
void headlessInit() {
    using namespace Celeste::Utilities;

    Logger::init();
    Timer::init();
    EventBus::init();

    CS_CORE_INFO("Initializing headless operation! [Platform Init Stage 1]");
}

/**
 * This function cleans up all utilities which can be used during headless operation
 */
void headlessCleanup() {
    using namespace Celeste::Utilities;

    EventBus::cleanup();
    Timer::cleanup();
    Logger::cleanup();
}

/**
 * Simple main function
 * @param argc - Argument count
 * @param argv - Argument variables
 * @return - Return code
 */
int main(int, char**) {

    /**
     * Init the base platform guarantees (Logging, Timing, Events)
     */
    CS_PROFILE_BEGIN_SESSION("Initialization", "Celeste-Init.json");
    CS_PROFILE_FUNCTION(headlessInit, __LINE__, __FILE__)

    /**
     * Create a new application
     */
    auto application = CreateNewCelesteApp();
    CS_PROFILE_END_SESSION();

    /**
     * Run the application main loop
     */
    CS_PROFILE_BEGIN_SESSION("User Session", "User-Session.json");
    application->Run();
    CS_PROFILE_END_SESSION();

    /**
     * Delete the application
     */
    CS_PROFILE_BEGIN_SESSION("Cleanup", "Celeste-Init.json");
    delete application;

    /**
     * Cleanup the base platform guarantees
     */
    CS_PROFILE_FUNCTION(headlessCleanup, __LINE__, __FILE__)
    CS_PROFILE_END_SESSION();

    return 0;
}