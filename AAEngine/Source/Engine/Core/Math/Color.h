#pragma once

#include "Core/Core.h"

namespace AAEngine
{
	/*
	* Color struct to define a 4 float Linear Color.
	*/
	struct FColor
	{
		/*
		* Union to give multiple representations of the same Color struct without any memory loss
		*/
		union
		{
			struct {
				float	R, // Red
						G, // Green
						B, // Blue
						A; // Alpha
			};
			// Any similar types here!
		};

		/*
		* Default Constructor for the Color class
		*/
		FColor() = default;

		/*
		* Constructor that takes in 3 floats for R,G,B
		* 
		* @param InR - Red value for the color
		* @param InG - Green value for the color
		* @param InB - Blue value for the color
		*/
		FColor(float InR, float InG, float InB)
			: R(InR), G(InG), B(InB), A(1.0f) {}

		/*
		* Constructor that takes in 4 floats for R,G,B,A
		*
		* @param InR - Red value for the color
		* @param InG - Green value for the color
		* @param InB - Blue value for the color
		* @param InA - Alpha value for the color
		*/
		FColor(float InR, float InG, float InB, float InA)
			: R(InR), G(InG), B(InB), A(InA) {}

		// --- STATIC CONST to define commonly used color values for the Color Struct. ------
		/*
		* static const variable for White color (1,1,1).
		*/
		static const FColor White;
		/*
		* static const variable for Gray color (0.5,0.5,0.5).
		*/
		static const FColor Gray;
		/*
		* static const variable for Black color (0,0,0).
		*/
		static const FColor Black;
		/*
		* static const variable for Transparent color (0,0,0,0).
		*/
		static const FColor Transparent;
		/*
		* static const variable for Red color (1,0,0).
		*/
		static const FColor Red;
		/*
		* static const variable for Green color (0,1,0).
		*/
		static const FColor Green;
		/*
		* static const variable for Blue color (0,0,1).
		*/
		static const FColor Blue;
		/*
		* static const variable for Yellow color (1,1,0).
		*/
		static const FColor Yellow;
		/*
		* static const variable for Cyan color (0,1,1).
		*/
		static const FColor Cyan;
		/*
		* static const variable for Magenta color (1,0,1).
		*/
		static const FColor Magenta;
		// ----------------------------------------------------------------------------------
	};
}