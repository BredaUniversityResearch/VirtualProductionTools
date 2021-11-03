#pragma once

#include "BaseLight.h"

#include "VirtualLight.generated.h"

UCLASS()
class UVirtualLight : public UBaseLight
{
    GENERATED_BODY()

public:

    UVirtualLight()
        : UBaseLight() {};

    virtual void SetEnabled(bool bNewState) override;
    virtual void SetLightIntensity(float NormalizedValue) override;
    virtual void SetHue(float NewValue) override;
    virtual void SetSaturation(float NewValue) override;
    virtual void SetUseTemperature(bool NewState) override;
    virtual void SetTemperature(float NormalizedValue) override;

    virtual void SetCastShadows(bool bState) override;

    virtual void AddHorizontal(float Degrees) override;
    virtual void AddVertical(float Degrees) override;
    virtual void SetInnerConeAngle(float NewValue) override;
    virtual void SetOuterConeAngle(float NewValue) override;

    virtual bool GetCastShadows() const override;

    virtual TSharedPtr<FJsonObject> SaveAsJson() const override;
    virtual FPlatformTypes::uint8 LoadFromJson(TSharedPtr<FJsonObject> JsonObject) override;

    virtual void BeginTransaction() override;

    union
    {
        class AActor* ActorPtr;
        class ASkyLight* SkyLight;
        class APointLight* PointLight;
        class ADirectionalLight* DirectionalLight;
        class ASpotLight* SpotLight;
    };

    UPROPERTY()
        bool bCastShadows;
};
