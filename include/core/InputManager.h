#pragma once

#include "core/InputAction.hpp"
#include "utility/FVector2.h"
#include <array>

class InputManager
{
    private:
        static constexpr size_t ACTION_COUNT = static_cast<size_t>(Action::COUNT);
        std::array<int, ACTION_COUNT> keyBindings;
        std::array<bool, ACTION_COUNT> keyDowns;
        std::array<bool, ACTION_COUNT> keyUps;
        std::array<bool, ACTION_COUNT> keyStates;

        FVector2 mousePos;
        FVector2 mouseDelta;
        float mouseWheel;

        size_t ToIndex(Action action) const
        {
            return static_cast<size_t>(action);
        }

    public:

        InputManager();

        void BindKey(Action action, const int key);
        void UnbindKey(Action action);
        void Update();

        bool GetActionDown(Action action) const; // TRUE: alla pressione
        bool GetActionUp(Action action) const; // TRUE: rilascio
        bool GetActionState(Action action) const; // TRUE: finche è premuto

        FVector2 GetMousePos() const;
        FVector2 GetMouseDelta() const;
        float GetMouseWheel() const;

        bool GetMouseButtonDown(int button) const;
        bool GetMouseButtonUp(int button) const;
        bool GetMouseButtonState(int button) const;
};