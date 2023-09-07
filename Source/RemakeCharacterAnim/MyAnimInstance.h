// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class REMAKECHARACTERANIM_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float Direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float AinYaw;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	float AimPitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
	uint32 bIsCrouch:1;
};
