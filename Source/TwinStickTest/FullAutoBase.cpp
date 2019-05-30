// Fill out your copyright notice in the Description page of Project Settings.


#include "FullAutoBase.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"
#include "ProjectileBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "TwinStickPC.h"


void AFullAutoBase::PrimaryFirePressed() 
{
	UWorld* World = GetWorld();

	World->GetTimerManager().SetTimer(TimerHandle_CooldownFinished, this, &AFullAutoBase::WeaponCooldownFinished, fireCooldown, true, 0);

}

void AFullAutoBase::PrimaryFireReleased()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CooldownFinished);
}

void AFullAutoBase::SecondaryButtonPressed()
{
}

void AFullAutoBase::SecondaryButtonReleased()
{
}

void AFullAutoBase::WeaponCooldownFinished()
{
	weaponMesh->PlayAnimation(weaponFireAnim, false);
	characterRef->PlayFireAnimMontage(characterFireAnim);
	FireWeapon();
}

void AFullAutoBase::FireWeapon()
{
	Super::FireWeapon();

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Cast<APawn>(Instigator);

	FVector spawnLocation = projectileOrigin->GetComponentLocation();

	AProjectileBase* projectile = GetWorld()->SpawnActor<AProjectileBase>(projectileClass, spawnLocation, projectileOrigin->GetComponentRotation(), spawnParams);
	projectile->SetprojectileDamage(weaponDamage);
	projectile->SetDamageType(DamageType);
}

void AFullAutoBase::SheatheWeapon()
{
	Super::SheatheWeapon();

	if (TimerHandle_CooldownFinished.IsValid()) {
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_CooldownFinished);
	}
}


