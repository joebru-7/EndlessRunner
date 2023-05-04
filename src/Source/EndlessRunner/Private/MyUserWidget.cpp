// Fill out your copyright notice in the Description page of Project Settings.

#include "MyUserWidget.h"
#include "CoreMinimal.h"
#include <fstream>

//shuld probably move out of class
FString UMyUserWidget::readHighscore()
{
	std::fstream highsoreFIle;
	highsoreFIle.open("C:\\temp\\Highscore.txt");

	UE_LOG(LogTemp, Warning, TEXT("%i"), highsoreFIle.is_open())

	char text[1024] = "no highscores yet";

	highsoreFIle.read(text,1023);

	return FString(text);

}