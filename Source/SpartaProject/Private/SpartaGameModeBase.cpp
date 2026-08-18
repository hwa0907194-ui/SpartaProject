#include "SpartaGameModeBase.h"
#include "PlayerCharacter.h"

ASpartaGameModeBase::ASpartaGameModeBase()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
}