#pragma once

namespace AAEngine::Math
{
	// Forward declaration of templates
	template<typename T> struct TVector2;
	template<typename T> struct TVector3;
	template<typename T> struct TVector4;
	template<typename T> struct TMatrix44;
	template<typename T> struct TQuaternion;
	template<typename T> struct TEuler;
	template<typename T> struct TTransform;
}

using FVector4f = AAEngine::Math::TVector4<float>;
using FVector4d = AAEngine::Math::TVector4<double>;

using FVector3f = AAEngine::Math::TVector3<float>;
using FVector3d = AAEngine::Math::TVector3<double>;

using FVector2f = AAEngine::Math::TVector2<float>;
using FVector2d = AAEngine::Math::TVector2<double>;

using FMatrix44f = AAEngine::Math::TMatrix44<float>;
using FMatrix44d = AAEngine::Math::TMatrix44<double>;

using FQuaternionf = AAEngine::Math::TQuaternion<float>;
using FQuaterniond = AAEngine::Math::TQuaternion<double>;

using FEulerf = AAEngine::Math::TEuler<float>;
using FEulerd = AAEngine::Math::TEuler<double>;

using FTransformf = AAEngine::Math::TTransform<float>;
using FTransformd = AAEngine::Math::TTransform<double>;