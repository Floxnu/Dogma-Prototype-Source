// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AProjectileBase::AProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ProjectileCollision"));
	ProjectileCollision->SetCollisionProfileName("Projectile");
	ProjectileCollision->OnComponentHit.AddDynamic(this, &AProjectileBase::OnHit);
	ProjectileCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectileBase::BeginOverlap);
	RootComponent = ProjectileCollision;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = ProjectileCollision;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// Die after 3 seconds by default
	InitialLifeSpan = 8.0f;

}

void AProjectileBase::SetDamageType(TSubclassOf<UDamageType> projectileDamageType)
{	
	damageType = projectileDamageType;
}

void AProjectileBase::SetprojectileDamage(float damageToDeal)
{
	projectileDamage = damageToDeal;
}

EProjectileType AProjectileBase::GetProjectileType()
{
	return projectileType;
}

// Called when the game starts or when spawned
void AProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectileBase::OnHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Registered"));
		/*if (OtherComp->IsSimulatingPhysics()) {
			OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());

			Destroy();
		}*/
		if (OtherActor->bCanBeDamaged && (OtherActor != Instigator->Instigator)) {
			if (!isDeflected) {
				UE_LOG(LogTemp, Warning, TEXT("Damage Sent to %s"), *OtherActor->GetName());
				UGameplayStatics::ApplyPointDamage(OtherActor, projectileDamage, Hit.Normal, Hit, Instigator->Instigator->GetController(), this, damageType);
				Destroy();
			}
		}
		if (isDeflected && (OtherActor == Instigator->Instigator)) {
			UGameplayStatics::ApplyPointDamage(OtherActor, projectileDamage, Hit.Normal, Hit, Instigator->Instigator->GetController(), this, damageType);
			Destroy();
		}

		Destroy();

		
	}
}

void AProjectileBase::BeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		if (OtherActor->bCanBeDamaged && (OtherActor != Instigator->Instigator)) {
			UE_LOG(LogTemp, Warning, TEXT("Damage Sent to %s"), *OtherActor->GetName());
			UGameplayStatics::ApplyPointDamage(OtherActor, projectileDamage, SweepResult.Normal, SweepResult, Instigator->Instigator->GetController(), this, damageType);
			Destroy();
		}
	}
	if (isDeflected && (OtherActor == Instigator->Instigator)) {
		UGameplayStatics::ApplyPointDamage(OtherActor, projectileDamage, SweepResult.Normal, SweepResult, Instigator->Instigator->GetController(), this, damageType);
		Destroy();
	}
}

// Called every frame
void AProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

