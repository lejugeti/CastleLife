// Fill out your copyright notice in the Description page of Project Settings.


#include "CastleLifeCharacter.h"

#include "AbilitySystemComponent.h"
#include "CastleLife/Abilities/SpeakToActor.h"


BEGIN_DEFINE_SPEC(MyCustomSpec, "MyGame.MyCustomClass", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
    TSharedPtr<ACastleLifeCharacter> CustomClass;
END_DEFINE_SPEC(MyCustomSpec)
void MyCustomSpec::Define()
{
    Describe("Execute()", [this]()
    {
        It("should return true when successful", [this]()
        {
            TSet<ACastleLifeCharacter> Set;
            TSet<ACastleLifeCharacter*> SetPointer;
            ACastleLifeCharacter Character;
            // Set.Add(Character);
            // SetPointer.Add(&Character);
            // TestTrue("Execute", Set.Contains(Character));
            // TestTrue("Execute", SetPointer.Contains(&Character));
        });
    });
}