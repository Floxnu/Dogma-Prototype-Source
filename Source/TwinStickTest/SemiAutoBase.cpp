// Fill out your copyright notice in the Description page of Project Settings.


#include "SemiAutoBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "TwinStickPC.h"
#include "Components/ArrowComponent.h"
#include "ProjectileBase.h"

void ASemiAutoBase::SecondaryButtonPressed()
{
	characterRef->SetIsAiming(true);
}

void ASemiAutoBase::SecondaryButtonReleased()
{
	characterRef->SetIsAiming(false);
}

void ASemiAutoBase::BeginPlay()
{
	Super::BeginPlay();

}

void ASemiAutoBase::FireWeapon()
{
	Super::FireWeapon();

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Cast<APawn>(Instigator);
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector spawnLocation = projectileOrigin->GetComponentLocation();

	AProjectileBase* projectile = GetWorld()->SpawnActor<AProjectileBase>(projectileClass, spawnLocation, projectileOrigin->GetComponentRotation(), spawnParams);
	if (projectile != nullptr) {
		projectile->SetprojectileDamage(weaponDamage);
		projectile->SetDamageType(DamageType);
	}
}

void ASemiAutoBase::PrimaryFirePressed() 
{
	if (isWeaponDrawn) {
	
		weaponMesh->PlayAnimation(weaponFireAnim, false);
		if (IsValid(characterRef)) {
			if (characterRef->GetIsAiming()) {
				characterRef->PlayFireAnimMontage(aimFireMontage);
			}
			else {
				characterRef->PlayFireAnimMontage(characterFireAnim);
			}
		}
		FireWeapon();
	}
}
