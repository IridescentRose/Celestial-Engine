/**
 * Defines an Application State
 */
#pragma once

namespace Celeste::Core {

    class Application;

    /**
     * An Application State
     */
    class ApplicationState {
    public:
        /**
         * Creates State - calls onStart after asset initialization.
         * Initialization should be done in the constructor, with only logic or events going into onStart or onCleanup!
         */
        ApplicationState() {
            onStart();
        };

        /**
         * Destroys State - calls onCleanup before asset destruction.
         * Only logic should be done in onCleanup!
         */
        virtual ~ApplicationState() {
            onCleanup();
        }

        virtual void onUpdate(Application* app, double dt) = 0;
        virtual void onDraw(Application* app, double dt) = 0;

        virtual void onStart() = default;
        virtual void onCleanup() = default;

    };
}