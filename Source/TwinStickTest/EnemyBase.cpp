// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBase.h"
#include "Runtime/Engine/Classes/Animation/AnimMontage.h"
#include "Components/CapsuleComponent.h"
#include "MeleeBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBase.h"

// Sets default values
AEnemyBase::AEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	currentHP = maxHP;
	bCanBeDamaged = true;
	this->OnTakePointDamage.AddDynamic(this, &AEnemyBase::OnPointDamageTaken);
}

// Called when the game starts or when spawned
void AEnemyBase::BeginPlay()
{
	Super::BeginPlay();
	currentHP = maxHP;
	bCanBeDamaged = true;

	if (meleeWeapon != nullptr) {

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Cast<APawn>(this);

		FVector spawnLocation = GetActorLocation();

		AMeleeBase* current = GetWorld()->SpawnActor<AMeleeBase>(meleeWeapon, spawnLocation, GetActorRotation(), spawnParams);
		current->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), FName("weapon_socket"));
		equipedMeleeWeapon = current;
	
	}

	if (rangedWeapon != nullptr) {

		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Cast<APawn>(this);

		FVector spawnLocation = GetActorLocation();

		AWeaponBase* current = GetWorld()->SpawnActor<AWeaponBase>(rangedWeapon, spawnLocation, GetActorRotation(), spawnParams);
		current->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), FName("right_weapon"));
		equipRangedWeapon = current;
		equipRangedWeapon->DrawWeapon();

	}
}

void AEnemyBase::OnPointDamageTaken(AActor * DamagedActor, float Damage, AController * InstigatedBy, FVector HitLocation, UPrimitiveComponent * FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType * DamageType, AActor * DamageCauser)
{
	
}

// Called every frame
void AEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void AEnemyBase::ModifyHealth(float changeValue)
{
	currentHP += changeValue;
	UE_LOG(LogTemp, Warning, TEXT("currentHP: %f"), currentHP);
	if (currentHP <= 0) {
		if (GetMeleeWeapon() != nullptr) {
			GetMeleeWeapon()->Destroy();
		}
		if (GetRangedWeapon() != nullptr) {
			GetRangedWeapon()->Destroy();
		}
		Destroy();
	}
	else if (currentHP > maxHP) {
		currentHP = maxHP;
	}
}

float AEnemyBase::MeleeAttack()
{
	PlayAnimMontage(attackAnim);

	return attackAnim->SequenceLength;
}

float AEnemyBase::RangedAttack()
{
	equipRangedWeapon->PrimaryFirePressed();

	return 0.0f;
}

AMeleeBase * AEnemyBase::GetMeleeWeapon()
{
	return equipedMeleeWeapon;
}

AWeaponBase * AEnemyBase::GetRangedWeapon()
{
	return equipRangedWeapon;
}

float AEnemyBase::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("Damage Registered"));
	ModifyHealth(-DamageAmount);
	hasTakenPlayerDamage = true;
	return DamageAmount;
}



