// Fill out your copyright notice in the Description page of Project Settings.


#include "TSPlayerController.h"
#include "TwinStickPC.h"
#include "DrawDebugHelpers.h"


ATSPlayerController::ATSPlayerController()
{

	bShowMouseCursor = true;

}

void ATSPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();


	InputComponent->BindAxis("MoveForward");
	InputComponent->BindAxis("MoveRight");
	InputComponent->BindAxis("FireForward");
	InputComponent->BindAxis("FireRight");

	InputComponent->BindAction("PrimaryFire", EInputEvent::IE_Pressed, this, &ATSPlayerController::PrimaryFirePressed);
	InputComponent->BindAction("PrimaryFire", EInputEvent::IE_Released, this, &ATSPlayerController::PrimaryFireReleased);

	InputComponent->BindAction("SecondaryFire", EInputEvent::IE_Pressed, this, &ATSPlayerController::SecondaryFirePressed);
	InputComponent->BindAction("SecondaryFire", EInputEvent::IE_Released, this, &ATSPlayerController::SecondaryFireReleased);

	InputComponent->BindAction("ShiftRight", EInputEvent::IE_Pressed, this, &ATSPlayerController::ShiftRightPressed);
	InputComponent->BindAction("ShiftRight", EInputEvent::IE_Released, this, &ATSPlayerController::ShiftRightReleased);

	InputComponent->BindAction("ShiftLeft", EInputEvent::IE_Pressed, this, &ATSPlayerController::ShiftLeftPressed);
	InputComponent->BindAction("ShiftLeft", EInputEvent::IE_Released, this, &ATSPlayerController::ShiftLeftReleased);
}

void ATSPlayerController::BeginPlay()
{
	Super::BeginPlay();

	currentPC = Cast<ATwinStickPC>(GetCharacter());
}

void ATSPlayerController::OnPossess(APawn * InPawn)
{
	Super::OnPossess(InPawn);

	currentPC = Cast<ATwinStickPC>(GetCharacter());

}

bool ATSPlayerController::InputAxis(FKey Key, float Delta, float DeltaTime, int32 NumSamples, bool bGamepad)
{
	bool ret = Super::InputAxis(Key, Delta, DeltaTime, NumSamples, bGamepad);
	bIsGamepadInput = bGamepad;
	return ret;
}

bool ATSPlayerController::InputKey(FKey Key, EInputEvent EventType, float AmountDepressed, bool bGamepad)
{
	bool ret = Super::InputKey(Key, EventType, AmountDepressed, bGamepad);
	bIsGamepadInput = bGamepad;
	return ret;
}

void ATSPlayerController::PrimaryFirePressed()
{
	if (IsValid(currentPC)) {
	
		currentPC->PrimaryAction(true);
	}
}

void ATSPlayerController::PrimaryFireReleased()
{
	if (IsValid(currentPC)) {

		currentPC->PrimaryAction(false);
	}
}

void ATSPlayerController::SecondaryFirePressed()
{
	if (IsValid(currentPC)) {

		currentPC->SecondaryAction(true);
	}
}

void ATSPlayerController::SecondaryFireReleased()
{
	if (IsValid(currentPC)) {

		currentPC->SecondaryAction(false);
	}
}

void ATSPlayerController::NextWeaponPressed()
{
	if (IsValid(currentPC)) {

		currentPC->ChangeWeapon(true);
	}
}

void ATSPlayerController::ShiftLeftPressed()
{
	if (IsValid(currentPC)) {
		currentPC->SetShiftAttack(true);
	}
}

void ATSPlayerController::ShiftLeftReleased()
{
	if (IsValid(currentPC)) {
		currentPC->SetShiftAttack(false);
	}
}

void ATSPlayerController::ShiftRightPressed()
{
	if (IsValid(currentPC)) {
		currentPC->SetShiftDefense(true);
	}
}


void ATSPlayerController::ShiftRightReleased()
{
	if (IsValid(currentPC)) {
		currentPC->SetShiftDefense(false);
	}
}


void ATSPlayerController::RotateToMousePosition()
{

	FRotator targetRot = GetCharacter()->GetActorRotation();
	if (bIsGamepadInput) {

		const float ForwardValue = GetInputAxisValue("FireForward");
		const float RightValue = GetInputAxisValue("FireRight");
		
		FVector current = FVector(ForwardValue, RightValue, 0.f);

		if (current.SizeSquared() >= 0.05f) {
		
			targetRot = current.Rotation();
			SetControlRotation(targetRot);
			GetCharacter()->FaceRotation(targetRot);
			return;
		}

	}
	else {
		FHitResult TraceHitResult;
		GetHitResultUnderCursor(ECC_Visibility, false, TraceHitResult);

		FVector mouseLocation = FVector(0, 0, 0);
		FVector mouseDirection = FVector(0, 0, 0);
		DeprojectMousePositionToWorld(mouseLocation, mouseDirection);

		FVector weaponLocation = currentPC->GetWeaponLocation();

		float charHeight = weaponLocation.Z;
		FVector hitLocation = TraceHitResult.Location;
		float zDiff = (charHeight - mouseLocation.Z);
		float targetX = ((hitLocation.X - mouseLocation.X) / (hitLocation.Z - mouseLocation.Z)) * zDiff + mouseLocation.X;
		float targetY = ((hitLocation.Y - mouseLocation.Y) / (hitLocation.Z - mouseLocation.Z)) * zDiff + mouseLocation.Y;
		FVector targetVector = FVector(targetX, targetY, charHeight);
		//FVector rotateLocation = FVector(TraceHitResult.Location.X, TraceHitResult.Location.Y, GetCharacter()->GetActorLocation().Z);


		DrawDebugSphere(
			GetWorld(),
			targetVector,
			5,
			32,
			FColor(255, 0, 0), false,.1f
		);

		 targetRot = FRotationMatrix::MakeFromX(targetVector - weaponLocation).Rotator();
		 targetRot = FRotator(targetRot.Pitch, targetRot.Yaw, 0.f);
		 SetControlRotation(targetRot);
		 GetCharacter()->FaceRotation(targetRot);
		 return;
	}
	
}

void ATSPlayerController::PlayerTick(float DeltaTime) 
{
	Super::PlayerTick(DeltaTime);

	if (IsValid(currentPC)) {
		const float ForwardValue = GetInputAxisValue("MoveForward");
		const float RightValue = GetInputAxisValue("MoveRight");

		GetCharacter()->AddMovementInput(FVector(ForwardValue, RightValue, 0.f));
	
		RotateToMousePosition();
	}
	/*if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, GetControlRotation().ToString());
	}
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Purple, GetCharacter()->GetActorRotation().ToString());
	}*/
}