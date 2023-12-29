#pragma once

namespace AAEngine {

	/*
	* Rendering Context interface to help derive and define platform and API specific Rendering Contexts
	*/
	class AA_ENGINE_API IRenderingContext
	{
	public:
		/*
		* Pure virtual function Used to Initialize a Rendering Context;
		*/
		virtual void InitializeContext() = 0;

		/*
		* Pure virtual function Used to Swap Buffers;
		*/
		virtual void SwapBuffers() = 0;
	private:
	};
}