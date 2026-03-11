#include "core/InputManager.h"

InputManager::InputManager()
{
    for (auto& keyBinding : keyBindings)
    {
        keyBinding = -1;
    }

    keyDowns.fill(false);
    keyUps.fill(false);
    keyStates.fill(false);

    mousePos = {0, 0};
    mouseDelta = {0, 0};
    mouseWheel = 0.0f;
}

void InputManager::BindKey(Action action, const int key)
{
    keyBindings[ToIndex(action)] = key;
}

void InputManager::UnbindKey(Action action)
{
    keyBindings[ToIndex(action)] = -1;    
    keyDowns[ToIndex(action)] = false;    
    keyUps[ToIndex(action)] = false;    
    keyStates[ToIndex(action)] = false;    
}

void InputManager::Update()
{
    keyDowns.fill(false);
    keyUps.fill(false);

    for (int i = 0; i < keyBindings.size(); ++i)
    {
        const int Key = keyBindings[i];
        if (Key == -1) continue;

        bool currentlyKeyDown = IsKeyDown(Key);

        keyDowns[i] = currentlyKeyDown && !keyStates[i];
        keyUps[i] = !currentlyKeyDown && keyStates[i];
        keyStates[i] = currentlyKeyDown;
    }

    const FVector2 oldMousePos = mousePos;
    mousePos = {GetMousePosition().x, GetMousePosition().y};
    mouseDelta = mousePos - oldMousePos;
    mouseWheel = GetMouseWheel();
}

bool InputManager::GetActionDown(Action action) const
{
    return keyDowns[ToIndex(action)];
}

bool InputManager::GetActionUp(Action action) const
{
    return keyUps[ToIndex(action)];
}

bool InputManager::GetActionState(Action action) const
{
    return keyStates[ToIndex(action)];
}

FVector2 InputManager::GetMousePos() const
{
    return mousePos;
}

FVector2 InputManager::GetMouseDelta() const
{
    return mouseDelta;
}

float InputManager::GetMouseWheel() const
{
    return mouseWheel;
}

bool InputManager::GetMouseButtonDown(int button) const
{
    return IsMouseButtonDown(button);
}

bool InputManager::GetMouseButtonUp(int button) const
{
    return IsMouseButtonReleased(button);
}

bool InputManager::GetMouseButtonState(int button) const
{
    return IsMouseButtonPressed(button);
}