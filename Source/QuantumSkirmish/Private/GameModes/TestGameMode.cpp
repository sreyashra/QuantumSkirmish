#include "GameModes/TestGameMode.h"
#include "Characters/HeroBase.h"
#include "Player/HeroPlayerController.h"


ATestGameMode::ATestGameMode()
{
	DefaultPawnClass = AHeroBase::StaticClass();
	PlayerControllerClass = AHeroPlayerController::StaticClass();
}
