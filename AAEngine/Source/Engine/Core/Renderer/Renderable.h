#pragma once

namespace AAEngine {

	class IRenderable
	{
	public:

		/*
		* Pure virtual Render function that should be overriden to add rendering code.
		*/
		virtual void Render() = 0;

		virtual void UpdateModelMatrix() {};

		const FMatrix44f& GetModelMatrix() const { return ModelMatrix; }

	private:

		FMatrix44f ModelMatrix = FMatrix44f::IdentityMatrix;
	};
}