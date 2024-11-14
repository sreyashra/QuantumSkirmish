#pragma once

UENUM(BlueprintType)
enum class EStance : uint8
{
	Stand UMETA(DisplayName = "Stand"),
	Crouch UMETA (DisplayName = "Crouch")
};

UENUM(BlueprintType)
enum class EStanceLastFrame : uint8
{
	Stand UMETA(DisplayName = "Stand"),
	Crouch UMETA (DisplayName = "Crouch")
};