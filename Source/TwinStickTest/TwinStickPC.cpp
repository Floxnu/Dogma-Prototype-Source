// Fill out your copyright notice in the Description page of Project Settings.


#include "TwinStickPC.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "WeaponBase.h"
#include "Components/CapsuleComponent.h"
#include "MeleeBase.h"
#include "DeflectResponseActor.h"

// Sets default values
ATwinStickPC::ATwinStickPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	currentWeaponIndex = 0;

	GetCharacterMovement()->MaxWalkSpeed = baseMoveSpeed;

	currentHP = maxHP;
}

// Called when the game starts or when spawned
void ATwinStickPC::BeginPlay()
{
	Super::BeginPlay();

	currentHP = maxHP;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	bUseControllerRotationYaw = false;


	normalAttackResponse = GetWorld()->SpawnActor<ADeflectResponseActor>(normalAttackResponseClass);
	altAttackReponse = GetWorld()->SpawnActor<ADeflectResponseActor>(altAttackResponseClass);

	if (!IsMelee) {	
		for (auto weapon : startingWeapons) {
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Cast<APawn>(this);

			FVector spawnLocation = GetActorLocation();

			AWeaponBase* current = GetWorld()->SpawnActor<AWeaponBase>(weapon, spawnLocation, GetActorRotation(), spawnParams);
			current->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, false), FName("right_weapon"));
			currentWeapons.Add(current);
		}
	
		EquipWeapon(currentWeapons[0]);
	}
	else {
	
		FActorSpawnParameters spawnParams;
		spawnParams.Owner = this;
		spawnParams.Instigator = Cast<APawn>(this);

		FVector spawnLocation = GetActorLocation();
		AMeleeBase* current = GetWorld()->SpawnActor<AMeleeBase>(startingMelee, spawnLocation, GetActorRotation(), spawnParams);
		current->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("right_melee"));
		equipedMelee = current;

		GetCharacterMovement()->MaxWalkSpeed = baseMoveSpeed;
	
	}
	canFire = true;
	
	attackEnergy = totalEnergy / 2;
	defenseEnergy = totalEnergy / 2;
}

void ATwinStickPC::EquipWeapon(AWeaponBase * weaponToEquip)
{
	if (equipedWeapon != nullptr) {
		equipedWeapon->SheatheWeapon();
	}
	weaponToEquip->DrawWeapon();
	equipedWeapon = weaponToEquip;
	GetCharacterMovement()->MaxWalkSpeed = baseMoveSpeed - equipedWeapon->GetMoveSpeedModifier();
}

void ATwinStickPC::ModifyHP(float amountToChange)
{
	currentHP += amountToChange;

	if (currentHP <= 0) {
		Die();
	}
	else if (currentHP > maxHP) {
		currentHP = maxHP;
	}
}

void ATwinStickPC::SetShiftAttack(bool newState)
{
	isShiftingAttack = newState;
}

void ATwinStickPC::SetShiftDefense(bool newState)
{
	isShiftingDefence = newState;
}

// Called every frame
void ATwinStickPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isShiftingAttack) {
		if (attackEnergy < totalEnergy) {
			attackEnergy += DeltaTime * shifAmountModifier;
			defenseEnergy -= DeltaTime * shifAmountModifier;
		}
	}

	if (isShiftingDefence) {
		if (defenseEnergy < totalEnergy) {
			attackEnergy -= DeltaTime * shifAmountModifier;
			defenseEnergy += DeltaTime * shifAmountModifier;
		}
	}

	if (attackEnergy > totalEnergy) {
		attackEnergy = totalEnergy;
	}
	if (defenseEnergy > totalEnergy)
	{
		defenseEnergy = totalEnergy;
	}
	if(defenseEnergy < 0){
		defenseEnergy = 0;
	}
	if (attackEnergy < 0) {
		attackEnergy = 0;
	}


	float hpPercent = currentHP / maxHP;

	maxHP = defenseEnergy;

	currentHP = hpPercent * maxHP;

	currentHP += (hpRegenPercent * maxHP) * DeltaTime;
	if (currentHP > maxHP) {
		currentHP = maxHP;
	}

	equipedMelee->weaponDamage = attackEnergy;
}

// Called to bind functionality to input
void ATwinStickPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATwinStickPC::PrimaryAction(bool isPressed)
{
	if (IsMelee) {
		if (isPressed) {
			equipedMelee->SetProjectileResponse(normalAttackResponse);
			PlayAnimMontage(characterMeleeAnim);
		}
	}
	else {
	
		if (canFire && isPressed) {
			equipedWeapon->PrimaryFirePressed();
		}
		else if (canFire) {
			equipedWeapon->PrimaryFireReleased();
		}
	}
}

void ATwinStickPC::SecondaryAction(bool isPressed)
{
	if (IsMelee) {
		if (isPressed) {
			equipedMelee->SetProjectileResponse(altAttackReponse);
			PlayAnimMontage(characterDeflectAnim);
		}
	}
	else {
		if (canFire) {
			if (isPressed) { equipedWeapon->SecondaryButtonPressed(); }
			else
			{
				equipedWeapon->SecondaryButtonReleased();
			}
		}
	}
}

void ATwinStickPC::ChangeWeapon(bool isNext)
{
	if (!IsMelee) {
		currentWeaponIndex++;
		if (currentWeaponIndex >= currentWeapons.Num()) {
			currentWeaponIndex = 0;
		}
		EquipWeapon(currentWeapons[currentWeaponIndex]);
	}
}

void ATwinStickPC::SetIsAiming(bool newState)
{
	isAiming = newState;
}

void ATwinStickPC::PlayFireAnimMontage(UAnimMontage* animToPlay)
{
	PlayAnimMontage(animToPlay);
}

EWeaponType ATwinStickPC::GetEquipedWeaponType()
{
	if (IsValid(equipedWeapon)) {
	
		return equipedWeapon->GetWeaponType();
	}
	else { return EWeaponType::WT_Rifle; }

}

bool ATwinStickPC::GetIsAiming()
{
	return isAiming;
}

void ATwinStickPC::SetCanFire(bool newState)
{
	canFire = newState;
}

FVector ATwinStickPC::GetWeaponLocation()
{
	if (IsValid(equipedWeapon)) {
		return equipedWeapon->GetActorLocation();
	}
	return GetActorLocation();
}

AMeleeBase * ATwinStickPC::GetMeleeWeapon()
{
	return equipedMelee;
}

float ATwinStickPC::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	ModifyHP(-DamageAmount);
	return DamageAmount;
}

float ATwinStickPC::GetCurrentHealth()
{
	return currentHP;
}

void ATwinStickPC::Die()
{
	//GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_EngineTraceChannel1, ECollisionResponse::ECR_Ignore);
	if (!IsMelee) {
		for (auto weapon : currentWeapons) {
			weapon->Destroy();
		}
	}
	GetMovementComponent()->SetActive(false);
	canFire = false;
	GetMesh()->SetSimulatePhysics(true);

}


