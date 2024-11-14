#pragma once

UENUM(BlueprintType)
enum class EOffsetRootRotationMode : uint8
{
	Accumulate UMETA(DisplayName = "Accumulate"),
	Release UMETA (DisplayName = "Release"),
};