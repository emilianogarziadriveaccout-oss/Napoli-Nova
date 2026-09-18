#include "NovaGameMode.h"
#include "Characters/NovaPlayerCharacter.h"

ANovaGameMode::ANovaGameMode()
{
    DefaultPawnClass = ANovaPlayerCharacter::StaticClass();
}
