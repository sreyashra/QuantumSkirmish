#pragma once

UENUM(BlueprintType)
enum class ERotationMode : uint8
{
	OrientToMovement UMETA(DisplayName = "Orient To Movement"),
	Strafe UMETA (DisplayName = "Strafe")
};

UENUM(BlueprintType)
enum class ERotationModeLastFrame : uint8
{
	OrientToMovement UMETA(DisplayName = "Orient To Movement"),
	Strafe UMETA (DisplayName = "Strafe")
};