// Fill out your copyright notice in the Description page of Project Settings.


#include "DeflectResponseActor.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"

// Sets default values
ADeflectResponseActor::ADeflectResponseActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

bool ADeflectResponseActor::SpawnObject(TSubclassOf<AActor> actorClass, FVector spawnLocation, FRotator spawnRotation)
{
	return true;
}
