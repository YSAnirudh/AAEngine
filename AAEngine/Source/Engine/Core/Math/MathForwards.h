#pragma once

namespace AAEngine::Math
{
	// Forward declaration of templates
	template<typename T> struct TVector3;
	template<typename T> struct TVector4;
	template<typename T> struct TMatrix44;
}

using FVector4f = AAEngine::Math::TVector4<float>;
using FVector4d = AAEngine::Math::TVector4<double>;

using FVector3f = AAEngine::Math::TVector3<float>;
using FVector3d = AAEngine::Math::TVector3<double>;

using FMatrix44f = AAEngine::Math::TMatrix44<float>;
using FMatrix44d = AAEngine::Math::TMatrix44<double>;