#pragma once

enum class NormalKey
{
	RELEASED = -1,
	NONE = 0,
	W = 1,
	A = 2,
	S = 3,
	D = 4,
	Q = 5,
	E = 6,
	F = 7,
	ENTER = 8,
	SPACE = 9,
};

enum class MouseKeys
{
	RELEASED = -1,
	NONE = 0,
	LEFT_CLICK = 1,
	RIGHT_CLICK = 2,
	Mid = 3
};

enum class ModifierKeys
{
	RELEASED = -1,
	NONE = 0,
	ALT = 1,
	SHIFT = 2
};


class InputSystem
{
public:
};

NormalKey _normalKey;
MouseKeys _mouseKey;
ModifierKeys _modifierKey;
