// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JsonPawn.generated.h"

USTRUCT(BlueprintType)
struct FFruitDetailData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JsonData")
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JsonData")
		FVector Size;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JsonData")
		int32 Price;

};

USTRUCT(BlueprintType)
struct FFruitData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JsonData")
		TArray<FFruitDetailData> Details;

};

UCLASS()
class JSFLUX_API AJsonPawn : public APawn
{
	GENERATED_BODY()

public:
	AJsonPawn();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	void TestFunc_SaveToJson();

	UFUNCTION(BlueprintCallable)
	void TestFunc_LoadFromJson();

private:
	FVector ParserJsonAsVector(TSharedPtr<FJsonObject> JsonValueObject, FString KeyName);

public:	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "JsonData")
	FFruitData FruitData;

};
