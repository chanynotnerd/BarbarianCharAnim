// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	APawn* MyPawn = TryGetPawnOwner();
	ACharacter* MyCharacter = Cast<ACharacter>(MyPawn);
	// Cast ���ָ� ���� ĳ���ͷ� �ٲ���.

	if (MyCharacter)
	{
		// Update Pawn Data
		Speed = MyCharacter->GetCharacterMovement()->Velocity.SizeSquared2D();
		// ĳ���ʹ� ĳ���͹����Ʈ�� ������ ����, �ű⼭ Velocity�� ������.
		// �����¿츸 �ʿ��ϱ⿡ SizeSquared2D ���.

		Direction = CalculateDirection(MyCharacter->GetCharacterMovement()->Velocity,
			MyCharacter->GetActorRotation());

		bIsCrouch = MyCharacter->GetCharacterMovement()->IsCrouching();
		// As Same As 
		// bIsCrouch = MyCharacter->bIsCrouched;
	}
}
