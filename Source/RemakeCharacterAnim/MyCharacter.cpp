// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0,
		-GetCapsuleComponent()->GetScaledCapsuleHalfHeight()),		// Returns the capsule half-height scaled
		FRotator(0, -90.0f, 0)
	);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	UEnhancedInputLocalPlayerSubsystem* LocalPlayerSystem
		= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	
	if (LocalPlayerSystem && DefaultInputMappingContext)	// ��Ʈ�ѷ��� �� �������� �˻�.
	{
		LocalPlayerSystem->AddMappingContext(DefaultInputMappingContext, 0);
	}
	// 37~45�� ��Ʈ�ѷ� ���� �� imc �ִ� �κ�? ã�ƺ��� �� ����ϰ� �ϴϱ� �� ��ü�� �ϱ��� ��.
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(IA_MoveForwardLeftRight, ETriggerEvent::Triggered,
			this, &AMyCharacter::MoveForwardLeftRight);
		EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered,
			this, &AMyCharacter::Look);
		EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered,
			this, &AMyCharacter::Jump);
		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Triggered,
			this, &AMyCharacter::Run);
		EnhancedInputComponent->BindAction(IA_Run, ETriggerEvent::Completed,
			this, &AMyCharacter::RunStop);
		EnhancedInputComponent->BindAction(IA_Crouch, ETriggerEvent::Triggered,
			this, &AMyCharacter::DoCrouch);
		EnhancedInputComponent->BindAction(IA_Dead, ETriggerEvent::Triggered,
			this, &AMyCharacter::DoDead);
	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	FVector2D CameraVector = Value.Get<FVector2D>();
	AddControllerPitchInput(CameraVector.Y);
	AddControllerYawInput(CameraVector.X);
}

void AMyCharacter::MoveForwardLeftRight(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	FRotator Rotation = GetControlRotation();	// ��Ʈ�ѷ��� ȸ���� ��������.
	FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);	// Yawȸ���� ������ ī�޶� ������ ��.

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);	// ȸ������ �־��־� ȸ������ �������� �չ����� ����.
	FVector RightVector = UKismetMathLibrary::GetRightVector(YawRotation);	// ������ ������ ȸ������ ������

	AddMovementInput(ForwardVector, MoveVector.Y);
	AddMovementInput(RightVector, MoveVector.X);
}

void AMyCharacter::Jump()
{
	GetCharacterMovement()->DoJump(GetCharacterMovement()->IsFalling());
}

void AMyCharacter::Run()
{
	
}

void AMyCharacter::RunStop()
{
	
}

void AMyCharacter::DoCrouch(const FInputActionValue& Value)
{
	if (CanCrouch())
	{
		Crouch();
	}
	else
	{
		UnCrouch();
	}
}

void AMyCharacter::DoDead(const FInputActionValue& Value)
{
	FString SectionName = FString::Printf(TEXT("Death%d"), FMath::RandRange(1, 3));
	PlayAnimMontage(AnimMontage, 1.0f, FName(*SectionName));
	// FString���� FName���� ��ȯ �� TestHUDName = FName(*TestHUDString) �̷� ������.
}
