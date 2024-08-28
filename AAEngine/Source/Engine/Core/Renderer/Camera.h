#pragma once

namespace AAEngine {

	class CCamera
	{
	public:
		virtual ~CCamera() {}

		const FVector3f& GetCameraLocation() const { return Location; };
		const FEulerf& GetCameraRotation() const { return Rotation; };

		void SetCameraLocation(const FVector3f& NewLocation)
		{
			Location = NewLocation;
			CalculateViewMatrix();
		}

		void SetCameraRotation(const FEulerf& NewRotation)
		{
			Rotation = NewRotation;
			CalculateViewMatrix();
		}

		const FMatrix44f& GetCameraViewProjectionMatrix() const { return ViewProjectionMatrix; };
		const FMatrix44f& GetCameraProjectionMatrix() const { return ProjectionMatrix; };
		const FMatrix44f& GetCameraViewMatrix() const { return ViewMatrix; };

	protected:
		virtual void CalculateViewMatrix()
		{
			FVector3f LookAtVector = Location + Rotation.ToVector();

			ViewMatrix = FMatrix44f::LookAt(Location, LookAtVector, FVector3f(0.0f, 1.0f, 0.0f));
			ViewMatrix.InverseFast();

			ViewProjectionMatrix = ViewMatrix * ProjectionMatrix;
		}

		FMatrix44f ProjectionMatrix;
		FMatrix44f ViewMatrix;
		FMatrix44f ViewProjectionMatrix;
		FVector3f Location;
		FEulerf Rotation;
	};

	class CPerspectiveCamera : public CCamera
	{
	public:
		CPerspectiveCamera(float FOVDeg, float InAspectRatio, float NearPlane, float FarPlane)
		{
			ProjectionMatrix = FMatrix44f::MakePerspective(Math::FMath::DegToRad(FOVDeg), InAspectRatio, NearPlane, FarPlane);
			Location = FVector3f::ZeroVector;
			Rotation = FEulerf::ZeroEuler;
			FOV = FOVDeg;
			AspectRatio = InAspectRatio;
			CalculateViewMatrix();
		}
	private:

		float FOV;
		float AspectRatio;
	};
}