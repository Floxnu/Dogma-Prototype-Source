// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeflectResponseActor.generated.h"

UCLASS()
class TWINSTICKTEST_API ADeflectResponseActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeflectResponseActor();

protected:
	
	bool SpawnObject(TSubclassOf<AActor> actorClass, FVector spawnLocation, FRotator spawnRotation);

public:	
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void OnProjectileCollision(class AProjectileBase* projectileHit, struct FHitResult hitInformation, class ACharacter* playerRef);

};
