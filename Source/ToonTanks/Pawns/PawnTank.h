// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnBase.h"
#include "PawnTank.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TOONTANKS_API APawnTank : public APawnBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	FVector MoveDirection;
	FQuat RotationDirection;


	FRotator CurrentYaw;
	FRotator TargetYaw;
	float TempX{0.f};
    float TempY{0.f};
	

	APlayerController* PlayerControllerRef;
	bool bIsPlayerAlive{true};

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float MoveSpeed{100.f};
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RoatateSpeed{100.f};

	void CalculateMoveInput(float Value);
	void CalculateRotateInput(float Value);

	void Move();
	void Rotate();

	void ControllerX(float Value);
	void ControllerY(float Value);

public:
	APawnTank();

	bool GetIsPlayerAlive();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;

	/*float InitialYaw{};
	float CurrentYaw{};
	float TargetYaw{};*/
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
