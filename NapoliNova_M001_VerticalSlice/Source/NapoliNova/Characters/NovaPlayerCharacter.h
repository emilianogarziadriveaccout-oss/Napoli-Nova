#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "NovaPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UNovaInteractionComponent;
class UNovaPhoneComponent;

UCLASS()
class NAPOLINOVA_API ANovaPlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ANovaPlayerCharacter();

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<USpringArmComponent> CameraBoom;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UCameraComponent> FollowCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UNovaInteractionComponent> InteractionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    TObjectPtr<UNovaPhoneComponent> PhoneComponent;

    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void Interact();
    void TogglePhone();
    void Record();
    void Publish();
};
