// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "DeflectProjectileResponse.generated.h"

/**
 * 
 */
UCLASS()
class TWINSTICKTEST_API UDeflectProjectileResponse : public UObject
{
	GENERATED_BODY()

protected:

	UFUNCTION(BlueprintCallable)
	bool SpawnObject(TSubclassOf<AActor> actorClass, FVector spawnLocation, FRotator spawnRotation);

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnProjectileCollision(class AProjectileBase* projectileHit, struct FHitResult hitInformation);
	
};
