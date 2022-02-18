#pragma once

namespace Hexagon
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44,      /* , */
		Minus = 45,      /* - */
		Period = 46,     /* . */
		Slash = 47,      /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61,     /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,   /* [ */
		Backslash = 92,     /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,   /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal  = 330,
		KPDivide   = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd      = 334,
		KPEnter    = 335,
		KPEqual    = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define HX_KEY_SPACE           ::Hexagon::Key::Space
#define HX_KEY_APOSTROPHE      ::Hexagon::Key::Apostrophe    /* ' */
#define HX_KEY_COMMA           ::Hexagon::Key::Comma         /* , */
#define HX_KEY_MINUS           ::Hexagon::Key::Minus         /* - */
#define HX_KEY_PERIOD          ::Hexagon::Key::Period        /* . */
#define HX_KEY_SLASH           ::Hexagon::Key::Slash         /* / */
#define HX_KEY_0               ::Hexagon::Key::D0
#define HX_KEY_1               ::Hexagon::Key::D1
#define HX_KEY_2               ::Hexagon::Key::D2
#define HX_KEY_3               ::Hexagon::Key::D3
#define HX_KEY_4               ::Hexagon::Key::D4
#define HX_KEY_5               ::Hexagon::Key::D5
#define HX_KEY_6               ::Hexagon::Key::D6
#define HX_KEY_7               ::Hexagon::Key::D7
#define HX_KEY_8               ::Hexagon::Key::D8
#define HX_KEY_9               ::Hexagon::Key::D9
#define HX_KEY_SEMICOLON       ::Hexagon::Key::Semicolon     /* ; */
#define HX_KEY_EQUAL           ::Hexagon::Key::Equal         /* = */
#define HX_KEY_A               ::Hexagon::Key::A
#define HX_KEY_B               ::Hexagon::Key::B
#define HX_KEY_C               ::Hexagon::Key::C
#define HX_KEY_D               ::Hexagon::Key::D
#define HX_KEY_E               ::Hexagon::Key::E
#define HX_KEY_F               ::Hexagon::Key::F
#define HX_KEY_G               ::Hexagon::Key::G
#define HX_KEY_H               ::Hexagon::Key::H
#define HX_KEY_I               ::Hexagon::Key::I
#define HX_KEY_J               ::Hexagon::Key::J
#define HX_KEY_K               ::Hexagon::Key::K
#define HX_KEY_L               ::Hexagon::Key::L
#define HX_KEY_M               ::Hexagon::Key::M
#define HX_KEY_N               ::Hexagon::Key::N
#define HX_KEY_O               ::Hexagon::Key::O
#define HX_KEY_P               ::Hexagon::Key::P
#define HX_KEY_Q               ::Hexagon::Key::Q
#define HX_KEY_R               ::Hexagon::Key::R
#define HX_KEY_S               ::Hexagon::Key::S
#define HX_KEY_T               ::Hexagon::Key::T
#define HX_KEY_U               ::Hexagon::Key::U
#define HX_KEY_V               ::Hexagon::Key::V
#define HX_KEY_W               ::Hexagon::Key::W
#define HX_KEY_X               ::Hexagon::Key::X
#define HX_KEY_Y               ::Hexagon::Key::Y
#define HX_KEY_Z               ::Hexagon::Key::Z
#define HX_KEY_LEFT_BRACKET    ::Hexagon::Key::LeftBracket   /* [ */
#define HX_KEY_BACKSLASH       ::Hexagon::Key::Backslash     /* \ */
#define HX_KEY_RIGHT_BRACKET   ::Hexagon::Key::RightBracket  /* ] */
#define HX_KEY_GRAVE_ACCENT    ::Hexagon::Key::GraveAccent   /* ` */
#define HX_KEY_WORLD_1         ::Hexagon::Key::World1        /* non-US #1 */
#define HX_KEY_WORLD_2         ::Hexagon::Key::World2        /* non-US #2 */

/* Function keys */
#define HX_KEY_ESCAPE          ::Hexagon::Key::Escape
#define HX_KEY_ENTER           ::Hexagon::Key::Enter
#define HX_KEY_TAB             ::Hexagon::Key::Tab
#define HX_KEY_BACKSPACE       ::Hexagon::Key::Backspace
#define HX_KEY_INSERT          ::Hexagon::Key::Insert
#define HX_KEY_DELETE          ::Hexagon::Key::Delete
#define HX_KEY_RIGHT           ::Hexagon::Key::Right
#define HX_KEY_LEFT            ::Hexagon::Key::Left
#define HX_KEY_DOWN            ::Hexagon::Key::Down
#define HX_KEY_UP              ::Hexagon::Key::Up
#define HX_KEY_PAGE_UP         ::Hexagon::Key::PageUp
#define HX_KEY_PAGE_DOWN       ::Hexagon::Key::PageDown
#define HX_KEY_HOME            ::Hexagon::Key::Home
#define HX_KEY_END             ::Hexagon::Key::End
#define HX_KEY_CAPS_LOCK       ::Hexagon::Key::CapsLock
#define HX_KEY_SCROLL_LOCK     ::Hexagon::Key::ScrollLock
#define HX_KEY_NUM_LOCK        ::Hexagon::Key::NumLock
#define HX_KEY_PRINT_SCREEN    ::Hexagon::Key::PrintScreen
#define HX_KEY_PAUSE           ::Hexagon::Key::Pause
#define HX_KEY_F1              ::Hexagon::Key::F1
#define HX_KEY_F2              ::Hexagon::Key::F2
#define HX_KEY_F3              ::Hexagon::Key::F3
#define HX_KEY_F4              ::Hexagon::Key::F4
#define HX_KEY_F5              ::Hexagon::Key::F5
#define HX_KEY_F6              ::Hexagon::Key::F6
#define HX_KEY_F7              ::Hexagon::Key::F7
#define HX_KEY_F8              ::Hexagon::Key::F8
#define HX_KEY_F9              ::Hexagon::Key::F9
#define HX_KEY_F10             ::Hexagon::Key::F10
#define HX_KEY_F11             ::Hexagon::Key::F11
#define HX_KEY_F12             ::Hexagon::Key::F12
#define HX_KEY_F13             ::Hexagon::Key::F13
#define HX_KEY_F14             ::Hexagon::Key::F14
#define HX_KEY_F15             ::Hexagon::Key::F15
#define HX_KEY_F16             ::Hexagon::Key::F16
#define HX_KEY_F17             ::Hexagon::Key::F17
#define HX_KEY_F18             ::Hexagon::Key::F18
#define HX_KEY_F19             ::Hexagon::Key::F19
#define HX_KEY_F20             ::Hexagon::Key::F20
#define HX_KEY_F21             ::Hexagon::Key::F21
#define HX_KEY_F22             ::Hexagon::Key::F22
#define HX_KEY_F23             ::Hexagon::Key::F23
#define HX_KEY_F24             ::Hexagon::Key::F24
#define HX_KEY_F25             ::Hexagon::Key::F25

/* Keypad */
#define HX_KEY_KP_0            ::Hexagon::Key::KP0
#define HX_KEY_KP_1            ::Hexagon::Key::KP1
#define HX_KEY_KP_2            ::Hexagon::Key::KP2
#define HX_KEY_KP_3            ::Hexagon::Key::KP3
#define HX_KEY_KP_4            ::Hexagon::Key::KP4
#define HX_KEY_KP_5            ::Hexagon::Key::KP5
#define HX_KEY_KP_6            ::Hexagon::Key::KP6
#define HX_KEY_KP_7            ::Hexagon::Key::KP7
#define HX_KEY_KP_8            ::Hexagon::Key::KP8
#define HX_KEY_KP_9            ::Hexagon::Key::KP9
#define HX_KEY_KP_DECIMAL      ::Hexagon::Key::KPDecimal
#define HX_KEY_KP_DIVIDE       ::Hexagon::Key::KPDivide
#define HX_KEY_KP_MULTIPLY     ::Hexagon::Key::KPMultiply
#define HX_KEY_KP_SUBTRACT     ::Hexagon::Key::KPSubtract
#define HX_KEY_KP_ADD          ::Hexagon::Key::KPAdd
#define HX_KEY_KP_ENTER        ::Hexagon::Key::KPEnter
#define HX_KEY_KP_EQUAL        ::Hexagon::Key::KPEqual

#define HX_KEY_LEFT_SHIFT      ::Hexagon::Key::LeftShift
#define HX_KEY_LEFT_CONTROL    ::Hexagon::Key::LeftControl
#define HX_KEY_LEFT_ALT        ::Hexagon::Key::LeftAlt
#define HX_KEY_LEFT_SUPER      ::Hexagon::Key::LeftSuper
#define HX_KEY_RIGHT_SHIFT     ::Hexagon::Key::RightShift
#define HX_KEY_RIGHT_CONTROL   ::Hexagon::Key::RightControl
#define HX_KEY_RIGHT_ALT       ::Hexagon::Key::RightAlt
#define HX_KEY_RIGHT_SUPER     ::Hexagon::Key::RightSuper
#define HX_KEY_MENU            ::Hexagon::Key::Menu
