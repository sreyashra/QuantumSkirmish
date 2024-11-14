#pragma once

UENUM(BlueprintType)
enum class EGait : uint8
{
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA (DisplayName = "Run"),
	Sprint UMETA (DisplayName = "Sprint")
};

UENUM(BlueprintType)
enum class EGaitLastFrame : uint8
{
	Walk UMETA(DisplayName = "Walk"),
	Run UMETA (DisplayName = "Run"),
	Sprint UMETA (DisplayName = "Sprint")
};