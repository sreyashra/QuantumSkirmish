#pragma once

UENUM(BlueprintType)
enum class EMovementState : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Moving UMETA (DisplayName = "Moving")
};

UENUM(BlueprintType)
enum class EMovementStateLastFrame : uint8
{
	Idle UMETA(DisplayName = "Idle"),
	Moving UMETA (DisplayName = "Moving")
};