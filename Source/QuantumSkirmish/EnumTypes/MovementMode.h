#pragma once
#include "Windows/AllowWindowsPlatformTypes.h"

UENUM(BlueprintType)
enum class EMovementModeCurrentFrame : uint8
{
	OnGround UMETA(DisplayName = "On Ground"),
	InAir UMETA (DisplayName = "In Air")
};

UENUM(BlueprintType)
enum class EMovementModeLastFrame : uint8
{
	OnGround UMETA(DisplayName = "On Ground"),
	InAir UMETA (DisplayName = "In Air")
};
