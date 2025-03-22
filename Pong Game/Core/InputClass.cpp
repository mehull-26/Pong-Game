// InputClass.cpp
#include "InputClass.h"

InputClass::InputClass()
{
    // Initialize all keys to being released and not pressed.
    for(int i = 0; i < 256; i++)
    {
        m_keys[i] = false;
    }

	for (int i = 0; i < 256; i++)
	{
		m_PrevKeys[i] = false;
	}
}

InputClass::InputClass(const InputClass& other)
{
    // Copy the state of the keys from the other object.
    for(int i = 0; i < 256; i++)
    {
        m_keys[i] = other.m_keys[i];
    }

    for (int i = 0; i < 256; i++)
    {
        m_PrevKeys[i] = other.m_PrevKeys[i];

    }
}

InputClass::~InputClass()
{
    // Destructor implementation (if needed)
}

bool InputClass::Initialize()
{
    // Initialize all keys to being released and not pressed.
    for (int i = 0; i < 256; i++)
    {
        m_keys[i] = false;
		m_PrevKeys[i] = false;
    }
	return true;
}

void InputClass::KeyDown(unsigned int key)
{
    // If a key is pressed then save that state in the key array.
    if(key < 256)
    {
        m_keys[key] = true;
    }
}

void InputClass::KeyUp(unsigned int key)
{
    // If a key is released then clear that state in the key array.
    if(key < 256)
    {
        m_keys[key] = false;
    }
}

bool InputClass::IsKeyDown(unsigned int key)
{
    // Return what state the key is in (pressed/not pressed).
    if(key < 256)
    {
        return m_keys[key];
    }
    return false;
}

bool InputClass::IsKeyPressed(unsigned int key)
{
    if (m_keys[key] && !m_PrevKeys[key])
    {
        m_PrevKeys[key] = true;
        return true;
    }
    else if (!m_keys[key])
    {
        m_PrevKeys[key] = false;
    }
    return false;
}

