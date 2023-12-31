// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* MyPawn = TryGetPawnOwner();
	ACharacter* MyCharacter = Cast<ACharacter>(MyPawn);
	// Cast 해주며 폰을 캐릭터로 바꿔줌.

	if (MyCharacter)
	{
		// Update Pawn Data
		Speed = MyCharacter->GetCharacterMovement()->Velocity.SizeSquared2D();
		// 캐릭터는 캐릭터무브먼트를 가지고 있음, 거기서 Velocity를 가져옴.
		// 상하좌우만 필요하기에 SizeSquared2D 사용.

		Direction = CalculateDirection(MyCharacter->GetCharacterMovement()->Velocity,
			MyCharacter->GetActorRotation());

		bIsCrouch = MyCharacter->GetCharacterMovement()->IsCrouching();
		// As Same As 
		// bIsCrouch = MyCharacter->bIsCrouched;
	}
}
