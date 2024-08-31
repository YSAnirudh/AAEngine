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
			if (FVector3f::AreNearlyEqual(NewLocation, Location))
			{
				return;
			}
			Location = NewLocation;
			bPropertiesDirtied = true;
		}

		void SetCameraRotation(const FEulerf& NewRotation)
		{
			if (FEulerf::AreNearlyEqual(NewRotation, Rotation))
			{
				return;
			}
			Rotation = NewRotation;
			bPropertiesDirtied = true;
		}

		void RecalculateViewMatrix()
		{
			if (bPropertiesDirtied)
			{
				CalculateViewMatrix();
			}
		}

		const FMatrix44f& GetCameraProjectionMatrix() const { return ProjectionMatrix; };
		const FMatrix44f& GetCameraViewMatrix() const { return ViewMatrix; };

	protected:
		virtual void CalculateViewMatrix()
		{
			const FVector3f LookAtVector = Location + Rotation.ToVector();

			ViewMatrix = FMatrix44f::LookAt(Location, LookAtVector, FVector3f(0.0f, 1.0f, 0.0f));
			ViewMatrix.InverseFast();

			bPropertiesDirtied = false;
		}

		FMatrix44f ProjectionMatrix;
		FMatrix44f ViewMatrix;
		FVector3f Location;
		FEulerf Rotation;

		bool bPropertiesDirtied = false;
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
			bPropertiesDirtied = true;
		}
	private:

		float FOV;
		float AspectRatio;
	};
}