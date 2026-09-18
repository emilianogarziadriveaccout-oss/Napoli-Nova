#include "NovaPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Interaction/NovaInteractionComponent.h"
#include "Systems/Phone/NovaPhoneComponent.h"

ANovaPlayerCharacter::ANovaPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 300.0f;
    CameraBoom->bUsePawnControlRotation = true;

    FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
    FollowCamera->SetupAttachment(CameraBoom);
    FollowCamera->bUsePawnControlRotation = false;

    InteractionComponent = CreateDefaultSubobject<UNovaInteractionComponent>(TEXT("Interaction"));
    PhoneComponent = CreateDefaultSubobject<UNovaPhoneComponent>(TEXT("Phone"));

    GetCharacterMovement()->MaxWalkSpeed = 350.0f;
}

void ANovaPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ANovaPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ANovaPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ANovaPlayerCharacter::Turn);
    PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ANovaPlayerCharacter::LookUp);

    PlayerInputComponent->BindAction(TEXT("Interact"), IE_Pressed, this, &ANovaPlayerCharacter::Interact);
    PlayerInputComponent->BindAction(TEXT("Phone"), IE_Pressed, this, &ANovaPlayerCharacter::TogglePhone);
    PlayerInputComponent->BindAction(TEXT("Record"), IE_Pressed, this, &ANovaPlayerCharacter::Record);
    PlayerInputComponent->BindAction(TEXT("Publish"), IE_Pressed, this, &ANovaPlayerCharacter::Publish);
}

void ANovaPlayerCharacter::MoveForward(float Value)
{
    AddMovementInput(GetActorForwardVector(), Value);
}

void ANovaPlayerCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ANovaPlayerCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ANovaPlayerCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void ANovaPlayerCharacter::Interact()
{
    if (InteractionComponent)
        InteractionComponent->TryInteract();
}

void ANovaPlayerCharacter::TogglePhone()
{
    if (PhoneComponent)
        PhoneComponent->TogglePhone();
}

void ANovaPlayerCharacter::Record()
{
    if (!PhoneComponent)
        return;

    if (PhoneComponent->IsRecording())
        PhoneComponent->StopRecording();
    else
        PhoneComponent->StartRecording();
}

void ANovaPlayerCharacter::Publish()
{
    if (PhoneComponent)
        PhoneComponent->PublishCurrentVideo();
}
