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
	
	if (LocalPlayerSystem && DefaultInputMappingContext)	// 컨트롤러가 잘 잡혔는지 검사.
	{
		LocalPlayerSystem->AddMappingContext(DefaultInputMappingContext, 0);
	}
	// 37~45는 컨트롤러 지정 및 imc 주는 부분? 찾아보니 다 비슷하게 하니까 꼴 자체를 암기할 것.
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
	FRotator Rotation = GetControlRotation();	// 컨트롤러의 회전값 가져오기.
	FRotator YawRotation = FRotator(0, Rotation.Yaw, 0);	// Yaw회전을 가지고 카메라를 돌리는 것.

	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(YawRotation);	// 회전값을 넣어주어 회전값을 기준으로 앞방향을 구함.
	FVector RightVector = UKismetMathLibrary::GetRightVector(YawRotation);	// 오른쪽 방향의 회전값을 가져옴

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
	// FString에서 FName으로 변환 시 TestHUDName = FName(*TestHUDString) 이런 식으로.
}
