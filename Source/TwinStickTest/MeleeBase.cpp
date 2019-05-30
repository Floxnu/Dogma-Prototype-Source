// Fill out your copyright notice in the Description page of Project Settings.


#include "MeleeBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ProjectileBase.h"
#include "DeflectResponseActor.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"

// Sets default values
AMeleeBase::AMeleeBase()
{
 	
	PrimaryActorTick.bCanEverTick = true;

	weaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMesh"));
	weaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = weaponMesh;

	weaponCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WeaponCollision"));
	weaponCollision->OnComponentBeginOverlap.AddDynamic(this, &AMeleeBase::OnWeaponOverlap);
	weaponCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	weaponCollision->SetGenerateOverlapEvents(false);
	weaponCollision->SetupAttachment(RootComponent);

}

void AMeleeBase::OnWeaponOverlap(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {

		if (ACharacter* charHit = Cast<ACharacter>(OtherActor)) {
			WeaponCollisionTrace();
		}
		if (AProjectileBase* projectileHit = Cast<AProjectileBase>(OtherActor)) {
			//deflectionResponse->OnProjectileCollision(projectileHit, SweepResult);
		}
	}
}

void AMeleeBase::SetWeaponCollisionEnabled(bool newState)
{
	weaponCollision->SetGenerateOverlapEvents(newState);


	isAttacking = newState;
	if (newState) {
		
		AActor* current = GetWorld()->SpawnActor<AActor>(hitBoxClass);
		current->AttachToActor(Instigator, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		currentHitbox = current;
		hitActors.Empty();
		
	}
}

void AMeleeBase::SetProjectileResponse(ADeflectResponseActor * newDeflectionResponse)
{
	deflectionResponse = newDeflectionResponse;
}

// Called when the game starts or when spawned
void AMeleeBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMeleeBase::WeaponCollisionTrace()
{
	FVector traceStart = weaponMesh->GetSocketLocation(FName("Attack6"));
	FVector traceEnd = weaponMesh->GetSocketLocation(FName("Attack1"));

	FHitResult TraceResult;
	GetWorld()->SweepSingleByChannel(TraceResult, traceStart, traceEnd, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(25));

	//DrawDebugLine(GetWorld(), traceStart, traceEnd, FColor::Red, false, 1.0f);
	if (TraceResult.Actor.Get() != nullptr && TraceResult.Actor.Get() != Instigator && TraceResult.Actor.Get() != this && !hitActors.Contains(TraceResult.Actor.Get())) {
		
		UE_LOG(LogTemp, Warning, TEXT("Hit Registered"));

		if (ACharacter* charHit = Cast<ACharacter>(TraceResult.Actor.Get())) {
			UGameplayStatics::ApplyDamage(charHit, weaponDamage, Instigator->GetController(), this, DamageType);
			UE_LOG(LogTemp, Warning, TEXT("Hit Data: Actor %s, Impact Point %s, Normal %s"), *GetNameSafe(charHit) , *TraceResult.ImpactPoint.ToString(), *TraceResult.Normal.ToString());
		
			DrawDebugSphere(GetWorld(), TraceResult.ImpactPoint, 10, 5, FColor::Purple, false, 1.0f);
		}

		hitActors.Add(TraceResult.Actor.Get());
	
	}

}

// Called every frame
void AMeleeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
