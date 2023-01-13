// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonPawn.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"

AJsonPawn::AJsonPawn()
{
 	PrimaryActorTick.bCanEverTick = false;

}

void AJsonPawn::BeginPlay()
{
	Super::BeginPlay();
	
	TestFunc_SaveToJson();

}

void AJsonPawn::TestFunc_SaveToJson()
{
	FFruitDetailData Apple;
	Apple.Name = TEXT("Apple");
	Apple.Size = FVector(5.f, 5.f, 5.f);
	Apple.Price = 1000;
	FruitData.Details.Add(Apple);

	FFruitDetailData Banana;
	Banana.Name = TEXT("Banana");
	Banana.Size = FVector(3.f, 3.f, 10.f);
	Banana.Price = 700;
	FruitData.Details.Add(Banana);

	FString JsonString;
	FJsonObjectConverter::UStructToJsonObjectString(FruitData, JsonString);
	FFileHelper::SaveStringToFile(*JsonString, *(FPaths::ProjectContentDir() + TEXT("/Json/Test.json")));

}

void AJsonPawn::TestFunc_LoadFromJson()
{

}

FVector AJsonPawn::ParserJsonAsVector(TSharedPtr<FJsonObject> JsonValueObject, FString KeyName)
{
	return FVector();
}
