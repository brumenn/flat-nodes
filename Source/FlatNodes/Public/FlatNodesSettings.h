// Copyright (c) 2022 Nicolas Castelli. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "FlatNodesSettings.generated.h"

/**
 * Configure the Flat Nodes plug-in.
 */
UCLASS(config = EditorPerProjectUserSettings)
class UFlatNodesSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFlatNodesSettings();

#if WITH_EDITOR
	//~ UDeveloperSettings interface
	virtual FText GetSectionText() const override;

	/**
	 * Called when a property on this object has been modified externally
	 *
	 * @param PropertyThatChanged the property that was modified
	 */
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	/**
	 * This alternate version of PostEditChange is called when properties inside structs are modified. The property that was actually modified
	 * is located at the tail of the list. The head of the list is the FStructProperty member variable that contains the property that was modified.
	 */
	virtual void PostEditChangeChainProperty(FPropertyChangedChainEvent& PropertyChangedEvent) override;
#endif

	FSlateBrush* CreateHeaderBrush();
	FSlateBrush* CreateBodyBrush();
	FSlateBrush* CreateBodyBrush_Var();

	void SetNodeTitleColor(const FSlateColor& Color);
	void RefreshCurrentTheme();

	/** Whether to use gradient on node header or not. Default: false */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Use Gradient")
	bool bHeaderUseGradient;

	/** Brightness of node header. Default: 0.25 */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Brightness", meta = (ClampMin = "0", ClampMax = "1"))
	float HeaderBrightness = 0.25f;

	/** Opacity of node header. Default: 1.0 */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Opacity", meta = (ClampMin = "0", ClampMax = "1"))
	float HeaderOpacity = 1.0f;

	/** Whether to use default color (FStyleColors::Foreground) or the below user color for node title color. Must at least reopen graph editors already opened to see effect on it. Default: false */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Use Title Color", meta = (ConfigRestartRequired = true))
	bool bNodeTitleColor;

	/** User node title color (EStyleColor::User1). Default: same as FStyleColors::Foreground */
	UPROPERTY(config, EditAnywhere, Category = "Header", DisplayName = "Title Color", meta = (EditCondition = "bNodeTitleColor"))
	FLinearColor NodeTitleColor = FStyleColors::Foreground.GetSpecifiedColor();

	/** Color of regular node background. Default: 0.0145f, 0.0145f, 0.0145f, 0.9f */
	UPROPERTY(config, EditAnywhere, Category = "Body|RegularNode", DisplayName = "Background Color")
	FLinearColor RegularNodeColor = FLinearColor(0.0145f, 0.0145f, 0.0145f, 0.9f);

	/** Color of var node background. Default: 0.0145f, 0.0145f, 0.0145f, 0.89f */
	UPROPERTY(config, EditAnywhere, Category = "Body|VarNode", DisplayName = "Background Color")
	FLinearColor VarNodeColor = FLinearColor(0.0145f, 0.0145f, 0.0145f, 0.89f);

	TMap<FString, FSlateBrush*> SlateBrushes;
};
