// Fill out your copyright notice in the Description page of Project Settings.


#include "JsonPawn.h"
#include "JsonObjectConverter.h"
#include "Misc/FileHelper.h"
#include "Templates/SharedPointer.h"

AJsonPawn::AJsonPawn()
{
 	PrimaryActorTick.bCanEverTick = false;

}

void AJsonPawn::BeginPlay()
{
	Super::BeginPlay();
	
	//TestFunc_SaveToJson();
	TestFunc_LoadFromJson();
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
	/*FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() + TEXT("/Json/Test.json")));

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> JsonValueArray = JsonObject->GetArrayField(TEXT("details"));

		for (int32 i = 0; i < JsonValueArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> JsonValue = JsonValueArray[i];
			TSharedPtr<FJsonObject> JsonValueObject = JsonValue->AsObject();

			FFruitDetailData DetailData;
			DetailData.Name = JsonValueObject->GetStringField(TEXT("name"));
			DetailData.Size = ParseJsonAsVector(JsonValueObject, TEXT("size"));
			DetailData.Price = JsonValueObject->GetNumberField(TEXT("price"));

			FruitData.Details.Push(DetailData);
			UE_LOG(LogTemp, Warning, TEXT("Name : %s, Size : %s, Price : %d"), *DetailData.Name, *DetailData.Size.ToString(), DetailData.Price);
		}
	}*/

	FString JsonString;
	FFileHelper::LoadFileToString(JsonString, *(FPaths::ProjectContentDir() + TEXT("/Json/Employees.json")));

	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	TArray<FString> Name;
	TArray<FString> LastName;
	TArray<FString> Gender;

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		TArray<TSharedPtr<FJsonValue>> EmployeesArray = JsonObject->GetArrayField(TEXT("Employees"));

		for (int32 i = 0; i < EmployeesArray.Num(); i++)
		{
			TSharedPtr<FJsonValue> EmployeesValue = EmployeesArray[i];
			TSharedPtr<FJsonObject> EmployeesValueObject = EmployeesValue->AsObject();

			EmployeesValueObject->TryGetStringArrayField("name", Name);
			EmployeesValueObject->TryGetStringArrayField("lastName", LastName);
			EmployeesValueObject->TryGetStringArrayField("gender", Gender);		
		}

		for (int32 j = 0; j < 6; j++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Name : %s, LastName : %s, Gender : %s"), *Name[j], *LastName[j], *Gender[j]);
		}
	}
	
}

FVector AJsonPawn::ParseJsonAsVector(TSharedPtr<FJsonObject> JsonValueObject, FString KeyName)
{
	TArray<FString> ArrayJson;
	JsonValueObject->TryGetStringArrayField(*KeyName, ArrayJson);

	return FVector{ FCString::Atof(*ArrayJson[0]), FCString::Atof(*ArrayJson[1]) , FCString::Atof(*ArrayJson[2]) };
}