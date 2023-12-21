#pragma once

#include "Containers/StaticArray.h"
#include "Input/KeyCodes.h"

#include <imgui.h>

namespace AAEngine {

	struct FImGuiToEngineCodes
	{
	public:
        // Temporary ImGui to Engine Code Coversion
        static EKeyCode GetKey(ImGuiKey key)
        {
            switch (key)
            {
            case ImGuiKey_Tab:              return FKey::Tab;
            case ImGuiKey_LeftArrow:        return FKey::Left;
            case ImGuiKey_RightArrow:       return FKey::Right;
            case ImGuiKey_UpArrow:          return FKey::Up;
            case ImGuiKey_DownArrow:        return FKey::Down;
            case ImGuiKey_PageUp:           return FKey::PageUp;
            case ImGuiKey_PageDown:         return FKey::PageDown;
            case ImGuiKey_Home:             return FKey::Home;
            case ImGuiKey_End:              return FKey::End;
            case ImGuiKey_Insert:           return FKey::Insert;
            case ImGuiKey_Delete:           return FKey::Delete;
            case ImGuiKey_Backspace:        return FKey::Backspace;
            case ImGuiKey_Space:            return FKey::Space;
            case ImGuiKey_Enter:            return FKey::Enter;
            case ImGuiKey_Escape:           return FKey::Escape;
            case ImGuiKey_Apostrophe:       return FKey::Apostrophe;
            case ImGuiKey_Comma:            return FKey::Comma;
            case ImGuiKey_Minus:            return FKey::Minus;
            case ImGuiKey_Period:           return FKey::Period;
            case ImGuiKey_Slash:            return FKey::Slash;
            case ImGuiKey_Semicolon:        return FKey::Semicolon;
            case ImGuiKey_Equal:            return FKey::Equal;
            case ImGuiKey_LeftBracket:      return FKey::LeftBracket;
            case ImGuiKey_Backslash:        return FKey::Backslash;
            case ImGuiKey_RightBracket:     return FKey::RightBracket;
            case ImGuiKey_GraveAccent:      return FKey::GraveAccent;
            case ImGuiKey_CapsLock:         return FKey::CapsLock;
            case ImGuiKey_ScrollLock:       return FKey::ScrollLock;
            case ImGuiKey_NumLock:          return FKey::NumLock;
            case ImGuiKey_PrintScreen:      return FKey::PrintScreen;
            case ImGuiKey_Pause:            return FKey::Pause;
            case ImGuiKey_Keypad0:          return FKey::KP0;
            case ImGuiKey_Keypad1:          return FKey::KP1;
            case ImGuiKey_Keypad2:          return FKey::KP2;
            case ImGuiKey_Keypad3:          return FKey::KP3;
            case ImGuiKey_Keypad4:          return FKey::KP4;
            case ImGuiKey_Keypad5:          return FKey::KP5;
            case ImGuiKey_Keypad6:          return FKey::KP6;
            case ImGuiKey_Keypad7:          return FKey::KP7;
            case ImGuiKey_Keypad8:          return FKey::KP8;
            case ImGuiKey_Keypad9:          return FKey::KP9;
            case ImGuiKey_KeypadDecimal:    return FKey::KPDecimal;
            case ImGuiKey_KeypadDivide:     return FKey::KPDivide;
            case ImGuiKey_KeypadMultiply:   return FKey::KPMultiply;
            case ImGuiKey_KeypadSubtract:   return FKey::KPSubtract;
            case ImGuiKey_KeypadAdd:        return FKey::KPAdd;
            case ImGuiKey_KeypadEnter:      return FKey::KPEnter;
            case ImGuiKey_KeypadEqual:      return FKey::KPEqual;
            case ImGuiKey_LeftShift:        return FKey::LeftShift;
            case ImGuiKey_LeftCtrl:         return FKey::LeftControl;
            case ImGuiKey_LeftAlt:          return FKey::LeftAlt;
            case ImGuiKey_LeftSuper:        return FKey::LeftSuper;
            case ImGuiKey_RightShift:       return FKey::RightShift;
            case ImGuiKey_RightCtrl:        return FKey::RightControl;
            case ImGuiKey_RightAlt:         return FKey::RightAlt;
            case ImGuiKey_RightSuper:       return FKey::RightSuper;
            case ImGuiKey_Menu:             return FKey::Menu;
            case ImGuiKey_0:                return FKey::D0;
            case ImGuiKey_1:                return FKey::D1;
            case ImGuiKey_2:                return FKey::D2;
            case ImGuiKey_3:                return FKey::D3;
            case ImGuiKey_4:                return FKey::D4;
            case ImGuiKey_5:                return FKey::D5;
            case ImGuiKey_6:                return FKey::D6;
            case ImGuiKey_7:                return FKey::D7;
            case ImGuiKey_8:                return FKey::D8;
            case ImGuiKey_9:                return FKey::D9;
            case ImGuiKey_A:                return FKey::A;
            case ImGuiKey_B:                return FKey::B;
            case ImGuiKey_C:                return FKey::C;
            case ImGuiKey_D:                return FKey::D;
            case ImGuiKey_E:                return FKey::E;
            case ImGuiKey_F:                return FKey::F;
            case ImGuiKey_G:                return FKey::G;
            case ImGuiKey_H:                return FKey::H;
            case ImGuiKey_I:                return FKey::I;
            case ImGuiKey_J:                return FKey::J;
            case ImGuiKey_K:                return FKey::K;
            case ImGuiKey_L:                return FKey::L;
            case ImGuiKey_M:                return FKey::M;
            case ImGuiKey_N:                return FKey::N;
            case ImGuiKey_O:                return FKey::O;
            case ImGuiKey_P:                return FKey::P;
            case ImGuiKey_Q:                return FKey::Q;
            case ImGuiKey_R:                return FKey::R;
            case ImGuiKey_S:                return FKey::S;
            case ImGuiKey_T:                return FKey::T;
            case ImGuiKey_U:                return FKey::U;
            case ImGuiKey_V:                return FKey::V;
            case ImGuiKey_W:                return FKey::W;
            case ImGuiKey_X:                return FKey::X;
            case ImGuiKey_Y:                return FKey::Y;
            case ImGuiKey_Z:                return FKey::Z;
            case ImGuiKey_F1:               return FKey::F1;
            case ImGuiKey_F2:               return FKey::F2;
            case ImGuiKey_F3:               return FKey::F3;
            case ImGuiKey_F4:               return FKey::F4;
            case ImGuiKey_F5:               return FKey::F5;
            case ImGuiKey_F6:               return FKey::F6;
            case ImGuiKey_F7:               return FKey::F7;
            case ImGuiKey_F8:               return FKey::F8;
            case ImGuiKey_F9:               return FKey::F9;
            case ImGuiKey_F10:              return FKey::F10;
            case ImGuiKey_F11:              return FKey::F11;
            case ImGuiKey_F12:              return FKey::F12;
            case ImGuiKey_F13:              return FKey::F13;
            case ImGuiKey_F14:              return FKey::F14;
            case ImGuiKey_F15:              return FKey::F15;
            case ImGuiKey_F16:              return FKey::F16;
            case ImGuiKey_F17:              return FKey::F17;
            case ImGuiKey_F18:              return FKey::F18;
            case ImGuiKey_F19:              return FKey::F19;
            case ImGuiKey_F20:              return FKey::F20;
            case ImGuiKey_F21:              return FKey::F21;
            case ImGuiKey_F22:              return FKey::F22;
            case ImGuiKey_F23:              return FKey::F23;
            case ImGuiKey_F24:              return FKey::F24;
            default:                        return FKey::None;
            }
        }
	};

	struct FEngineToImGuiCodes
	{
	public:
        // Temporary Engine to ImGui Code Coversion
        static ImGuiKey GetKey(EKeyCode key)
        {
            switch (key)
            {
            case FKey::Tab:             return ImGuiKey_Tab;
            case FKey::Left:            return ImGuiKey_LeftArrow;
            case FKey::Right:           return ImGuiKey_RightArrow;
            case FKey::Up:              return ImGuiKey_UpArrow;
            case FKey::Down:            return ImGuiKey_DownArrow;
            case FKey::PageUp:          return ImGuiKey_PageUp;
            case FKey::PageDown:        return ImGuiKey_PageDown;
            case FKey::Home:            return ImGuiKey_Home;
            case FKey::End:             return ImGuiKey_End;
            case FKey::Insert:          return ImGuiKey_Insert;
            case FKey::Delete:          return ImGuiKey_Delete;
            case FKey::Backspace:       return ImGuiKey_Backspace;
            case FKey::Space:           return ImGuiKey_Space;
            case FKey::Enter:           return ImGuiKey_Enter;
            case FKey::Escape:          return ImGuiKey_Escape;
            case FKey::Apostrophe:      return ImGuiKey_Apostrophe;
            case FKey::Comma:           return ImGuiKey_Comma;
            case FKey::Minus:           return ImGuiKey_Minus;
            case FKey::Period:          return ImGuiKey_Period;
            case FKey::Slash:           return ImGuiKey_Slash;
            case FKey::Semicolon:       return ImGuiKey_Semicolon;
            case FKey::Equal:           return ImGuiKey_Equal;
            case FKey::LeftBracket:     return ImGuiKey_LeftBracket;
            case FKey::Backslash:       return ImGuiKey_Backslash;
            case FKey::RightBracket:    return ImGuiKey_RightBracket;
            case FKey::GraveAccent:     return ImGuiKey_GraveAccent;
            case FKey::CapsLock:        return ImGuiKey_CapsLock;
            case FKey::ScrollLock:      return ImGuiKey_ScrollLock;
            case FKey::NumLock:         return ImGuiKey_NumLock;
            case FKey::PrintScreen:     return ImGuiKey_PrintScreen;
            case FKey::Pause:           return ImGuiKey_Pause;
            case FKey::KP0:             return ImGuiKey_Keypad0;
            case FKey::KP1:             return ImGuiKey_Keypad1;
            case FKey::KP2:             return ImGuiKey_Keypad2;
            case FKey::KP3:             return ImGuiKey_Keypad3;
            case FKey::KP4:             return ImGuiKey_Keypad4;
            case FKey::KP5:             return ImGuiKey_Keypad5;
            case FKey::KP6:             return ImGuiKey_Keypad6;
            case FKey::KP7:             return ImGuiKey_Keypad7;
            case FKey::KP8:             return ImGuiKey_Keypad8;
            case FKey::KP9:             return ImGuiKey_Keypad9;
            case FKey::KPDecimal:       return ImGuiKey_KeypadDecimal;
            case FKey::KPDivide:        return ImGuiKey_KeypadDivide;
            case FKey::KPMultiply:      return ImGuiKey_KeypadMultiply;
            case FKey::KPSubtract:      return ImGuiKey_KeypadSubtract;
            case FKey::KPAdd:           return ImGuiKey_KeypadAdd;
            case FKey::KPEnter:         return ImGuiKey_KeypadEnter;
            case FKey::KPEqual:         return ImGuiKey_KeypadEqual;
            case FKey::LeftShift:       return ImGuiKey_LeftShift;
            case FKey::LeftControl:     return ImGuiKey_LeftCtrl;
            case FKey::LeftAlt:         return ImGuiKey_LeftAlt;
            case FKey::LeftSuper:       return ImGuiKey_LeftSuper;
            case FKey::RightShift:      return ImGuiKey_RightShift;
            case FKey::RightControl:    return ImGuiKey_RightCtrl;
            case FKey::RightAlt:        return ImGuiKey_RightAlt;
            case FKey::RightSuper:      return ImGuiKey_RightSuper;
            case FKey::Menu:            return ImGuiKey_Menu;
            case FKey::D0:              return ImGuiKey_0;
            case FKey::D1:              return ImGuiKey_1;
            case FKey::D2:              return ImGuiKey_2;
            case FKey::D3:              return ImGuiKey_3;
            case FKey::D4:              return ImGuiKey_4;
            case FKey::D5:              return ImGuiKey_5;
            case FKey::D6:              return ImGuiKey_6;
            case FKey::D7:              return ImGuiKey_7;
            case FKey::D8:              return ImGuiKey_8;
            case FKey::D9:              return ImGuiKey_9;
            case FKey::A:               return ImGuiKey_A;
            case FKey::B:               return ImGuiKey_B;
            case FKey::C:               return ImGuiKey_C;
            case FKey::D:               return ImGuiKey_D;
            case FKey::E:               return ImGuiKey_E;
            case FKey::F:               return ImGuiKey_F;
            case FKey::G:               return ImGuiKey_G;
            case FKey::H:               return ImGuiKey_H;
            case FKey::I:               return ImGuiKey_I;
            case FKey::J:               return ImGuiKey_J;
            case FKey::K:               return ImGuiKey_K;
            case FKey::L:               return ImGuiKey_L;
            case FKey::M:               return ImGuiKey_M;
            case FKey::N:               return ImGuiKey_N;
            case FKey::O:               return ImGuiKey_O;
            case FKey::P:               return ImGuiKey_P;
            case FKey::Q:               return ImGuiKey_Q;
            case FKey::R:               return ImGuiKey_R;
            case FKey::S:               return ImGuiKey_S;
            case FKey::T:               return ImGuiKey_T;
            case FKey::U:               return ImGuiKey_U;
            case FKey::V:               return ImGuiKey_V;
            case FKey::W:               return ImGuiKey_W;
            case FKey::X:               return ImGuiKey_X;
            case FKey::Y:               return ImGuiKey_Y;
            case FKey::Z:               return ImGuiKey_Z;
            case FKey::F1:              return ImGuiKey_F1;
            case FKey::F2:              return ImGuiKey_F2;
            case FKey::F3:              return ImGuiKey_F3;
            case FKey::F4:              return ImGuiKey_F4;
            case FKey::F5:              return ImGuiKey_F5;
            case FKey::F6:              return ImGuiKey_F6;
            case FKey::F7:              return ImGuiKey_F7;
            case FKey::F8:              return ImGuiKey_F8;
            case FKey::F9:              return ImGuiKey_F9;
            case FKey::F10:             return ImGuiKey_F10;
            case FKey::F11:             return ImGuiKey_F11;
            case FKey::F12:             return ImGuiKey_F12;
            case FKey::F13:             return ImGuiKey_F13;
            case FKey::F14:             return ImGuiKey_F14;
            case FKey::F15:             return ImGuiKey_F15;
            case FKey::F16:             return ImGuiKey_F16;
            case FKey::F17:             return ImGuiKey_F17;
            case FKey::F18:             return ImGuiKey_F18;
            case FKey::F19:             return ImGuiKey_F19;
            case FKey::F20:             return ImGuiKey_F20;
            case FKey::F21:             return ImGuiKey_F21;
            case FKey::F22:             return ImGuiKey_F22;
            case FKey::F23:             return ImGuiKey_F23;
            case FKey::F24:             return ImGuiKey_F24;
            default:                    return ImGuiKey_None;
            }
        }
	};
}