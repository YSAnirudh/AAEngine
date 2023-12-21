#pragma once

namespace AAEngine
{
	/*
	* using definition for a MouseCode
	* It is just a uint16_t
	*/
	using EMouseCode = unsigned int;

	namespace Mouse
	{
		/*
		* Mouse Codes as uint16_t for tracking Mouse Codes associated with each mouse button
		* GLFW based Mouse Codes
		*/
		enum : EMouseCode
		{
			// Buttons
			Button0 = 0,
			Button1 = 1,
			Button2 = 2,
			Button3 = 3,
			Button4 = 4,
			Button5 = 5,
			Button6 = 6,
			Button7 = 7,

			// Generic Buttons
			ButtonLast = Button7,
			ButtonLeft = Button0,
			ButtonRight = Button1,
			ButtonMiddle = Button2
		};
	}
}