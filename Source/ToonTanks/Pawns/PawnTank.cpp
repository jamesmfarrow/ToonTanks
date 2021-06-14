// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnTank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APawnTank::APawnTank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}

bool APawnTank::GetIsPlayerAlive() 
{
    return bIsPlayerAlive;
}

// Called when the game starts or when spawned
void APawnTank::BeginPlay()
{
	Super::BeginPlay();
	
    PlayerControllerRef = Cast<APlayerController>(GetController());
    CurrentYaw = TurretMesh->GetOwner()->GetActorRotation();
}

void APawnTank::HandleDestruction() 
{
    Super::HandleDestruction();
    bIsPlayerAlive = false;
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

// Called every frame
void APawnTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    Rotate();
    Move();

    if(PlayerControllerRef)
    {
        FHitResult TraceResultHit;
        PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility, false, TraceResultHit);
        FVector HitLocation{TraceResultHit.ImpactPoint};
        RotateTurret(HitLocation);


        float X = InputComponent->GetAxisValue("ControllerX");
        float Y = InputComponent->GetAxisValue("ControllerY");

        if(X < 0 || X > 0) { TempX = X; }
        if(Y < 0 || Y > 0) { TempY = Y; }
        

        UE_LOG(LogTemp, Warning, TEXT("X$ value: %f"), TempX);
        UE_LOG(LogTemp, Warning, TEXT("Y$ value: %f"), TempY);


        FVector Direction = GetActorForwardVector() * -TempY;
        Direction += GetActorRightVector() * TempX;
        TargetYaw = Direction.Rotation();
        CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, .02f);
        //TurretMesh->SetWorldRotation(Direction.Rotation());
        TurretMesh->SetWorldRotation(CurrentYaw);
    }
}


// Called to bind functionality to input
void APawnTank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APawnTank::CalculateMoveInput);
    PlayerInputComponent->BindAxis("Turn", this, &APawnTank::CalculateRotateInput);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APawnTank::Fire);
    PlayerInputComponent->BindAxis("ControllerX", this, &APawnTank::ControllerX);
    PlayerInputComponent->BindAxis("ControllerY", this, &APawnTank::ControllerY);
}



void APawnTank::CalculateMoveInput(float Value) 
{
    MoveDirection = FVector(Value * MoveSpeed * GetWorld()->DeltaTimeSeconds, 0, 0); //x directiomn only
}

void APawnTank::CalculateRotateInput(float Value) 
{
    float RotateAmount{Value * RoatateSpeed * GetWorld()->DeltaTimeSeconds};
    FRotator Rotation{FRotator(0, RotateAmount, 0)};
    RotationDirection = FQuat(Rotation);
}


void APawnTank::Move() 
{
    AddActorLocalOffset(MoveDirection, true);
}

void APawnTank::Rotate() 
{
    AddActorLocalRotation(RotationDirection, true);
}

void APawnTank::ControllerX(float Value) 
{
    //UE_LOG(LogTemp, Warning, TEXT("X value: %f"), Value);
}

void APawnTank::ControllerY(float Value) 
{
    //UE_LOG(LogTemp, Warning, TEXT("Y value: %f"), Value);
}


