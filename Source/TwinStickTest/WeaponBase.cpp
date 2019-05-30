// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"
#include "Components/ArrowComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "TwinStickPC.h"
#include "Runtime/Engine/Classes/Camera/CameraShake.h"
#include "TSPlayerController.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	weaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	weaponMesh->SetHiddenInGame(true);
	RootComponent = weaponMesh;

	projectileOrigin = CreateDefaultSubobject<UArrowComponent>(TEXT("Projectile Origin"));
	projectileOrigin->SetupAttachment(weaponMesh, FName("Muzzle"));
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	characterRef = Cast<ATwinStickPC>(Instigator);
	
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AWeaponBase::PrimaryFirePressed()
{
}

void AWeaponBase::PrimaryFireReleased()
{
}

void AWeaponBase::SecondaryButtonPressed()
{
}

void AWeaponBase::SecondaryButtonReleased()
{
}

float AWeaponBase::GetMoveSpeedModifier()
{
	return weaponMoveSpeedModifier;
}

void AWeaponBase::DrawWeapon()
{
	if (characterRef != nullptr) {
	
		characterRef->PlayFireAnimMontage(weaponEquipAnim);
	}
	weaponMesh->SetHiddenInGame(false);
	isWeaponDrawn = true;
}

void AWeaponBase::SheatheWeapon()
{
	weaponMesh->SetHiddenInGame(true);
	isWeaponDrawn = false;
}

EWeaponType AWeaponBase::GetWeaponType()
{
	return weaponType;
}

void AWeaponBase::WeaponCooldownFinished()
{
	weaponCanFire = true;
}

void AWeaponBase::FireWeapon()
{
	if (characterRef != nullptr) {
		ATSPlayerController* pc = Cast<ATSPlayerController>(characterRef->GetController());
		if (IsValid(pc)) {
			pc->ClientPlayCameraShake(shotCameraShake);
		}
	}
}

