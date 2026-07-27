// Copyright (c) 2022 Nicolas Castelli. Licensed under the MIT License.

#include "FlatNodesSettings.h"
#include "Materials/MaterialInstanceDynamic.h"

#include "Misc/EngineVersionComparison.h"

#define LOCTEXT_NAMESPACE "FlatNodes"

UFlatNodesSettings::UFlatNodesSettings()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("FlatNodes");
}

#if WITH_EDITOR
FText UFlatNodesSettings::GetSectionText() const
{
	return LOCTEXT("UserSettingsDisplayName", "Flat Nodes");
}

void UFlatNodesSettings::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property)
	{
		const FName NAME_bHeaderUseGradient = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, bHeaderUseGradient);
		const FName NAME_HeaderBrightness = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, HeaderBrightness);
		const FName NAME_HeaderOpacity = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, HeaderOpacity);
		const FName NAME_bNodeTitleColor = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, bNodeTitleColor);
		const FName NAME_NodeTitleColor = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, NodeTitleColor);
		const FName NAME_RegularNodeColor = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, RegularNodeColor);
		const FName NAME_VarNodeColor = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, VarNodeColor);
		const FName PropertyName = PropertyChangedEvent.GetPropertyName();

		if (PropertyName == NAME_bHeaderUseGradient)
		{
			UObject* ResourceObject = SlateBrushes["HeaderBrush"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);

			if (Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
				DynamicMaterial->SetScalarParameterValue("UseGradient", bHeaderUseGradient);
			}
		}

		if (PropertyName == NAME_HeaderBrightness)
		{
			UObject* ResourceObject = SlateBrushes["HeaderBrush"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);

			if (Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
				DynamicMaterial->SetVectorParameterValue("Color", FVector(HeaderBrightness, HeaderBrightness, HeaderBrightness));
			}
		}

		if (PropertyName == NAME_HeaderOpacity)
		{
			UObject* ResourceObject = SlateBrushes["HeaderBrush"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);

			if (Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
				DynamicMaterial->SetScalarParameterValue("Opacity", HeaderOpacity);
			}
		}

		if (PropertyName == NAME_bNodeTitleColor)
		{
			// Here, we choose either the theme default color or the user one.
			if (bNodeTitleColor)
			{
				SetNodeTitleColor(FSlateColor(EStyleColor::User1));
			}
			else
			{
				SetNodeTitleColor(FStyleColors::Foreground);
			}
		}

		if (PropertyName == NAME_NodeTitleColor)
		{
			//if (bNodeTitleColor)
			//{
			//	// Change EStyleColor::User1 according to NodeTitleColor.
			//	USlateThemeManager::Get().SetDefaultColor(EStyleColor::User1, NodeTitleColor);
			//	//SetNodeTitleColor(FSlateColor(EStyleColor::User1));
			//}
			//else
			//{
			//	// Change EStyleColor::User1 according to FStyleColors::Foreground which is the theme default color used by the editor usually.
			//	USlateThemeManager::Get().SetDefaultColor(EStyleColor::User1, FStyleColors::Foreground.GetSpecifiedColor());
			//	//SetNodeTitleColor(FStyleColors::Foreground);
			//}

			// Change EStyleColor::User1 according to NodeTitleColor.
			USlateThemeManager::Get().SetDefaultColor(EStyleColor::User1, NodeTitleColor);

			RefreshCurrentTheme();
		}

		if (PropertyName == NAME_RegularNodeColor)
		{
			UObject* ResourceObject = SlateBrushes["BodyBrush"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);

			if (Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
				DynamicMaterial->SetVectorParameterValue("Color", FVector(RegularNodeColor.R, RegularNodeColor.G, RegularNodeColor.B));
				DynamicMaterial->SetScalarParameterValue("Opacity", RegularNodeColor.A);
			}
		}

		if (PropertyName == NAME_VarNodeColor)
		{
			UObject* ResourceObject = SlateBrushes["BodyBrush_Var"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);

			if (Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
				DynamicMaterial->SetVectorParameterValue("Color", FVector(VarNodeColor.R, VarNodeColor.G, VarNodeColor.B));
				DynamicMaterial->SetScalarParameterValue("Opacity", VarNodeColor.A);
			}
		}
	}
}

void UFlatNodesSettings::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.Property)
	{
		const FName NAME_RegularNodeColor = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, RegularNodeColor);
		const FName NAME_VarNodeColor = GET_MEMBER_NAME_CHECKED(UFlatNodesSettings, VarNodeColor);
		const FName PropertyName = PropertyChangedEvent.GetPropertyName();

		FProperty* PrevProperty = PropertyChangedEvent.PropertyChain.GetActiveNode()->GetPrevNode() ? PropertyChangedEvent.PropertyChain.GetActiveNode()->GetPrevNode()->GetValue() : nullptr;
		FProperty* NextProperty = PropertyChangedEvent.PropertyChain.GetActiveNode()->GetNextNode() ? PropertyChangedEvent.PropertyChain.GetActiveNode()->GetNextNode()->GetValue() : nullptr;
		FName FStructPropertyName = PrevProperty ? PrevProperty->GetFName() : NAME_None;

		if (FStructPropertyName == NAME_RegularNodeColor)
		{
			UObject* ResourceObject = SlateBrushes["BodyBrush"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);

			if (Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
				DynamicMaterial->SetVectorParameterValue("Color", FVector(RegularNodeColor.R, RegularNodeColor.G, RegularNodeColor.B));
				DynamicMaterial->SetScalarParameterValue("Opacity", RegularNodeColor.A);
			}
		}

		if (FStructPropertyName == NAME_VarNodeColor)
		{
			UObject* ResourceObject = SlateBrushes["BodyBrush_Var"]->GetResourceObject();
			UMaterialInterface* Material = Cast<UMaterialInterface>(ResourceObject);

			if (Material)
			{
				UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
				DynamicMaterial->SetVectorParameterValue("Color", FVector(VarNodeColor.R, VarNodeColor.G, VarNodeColor.B));
				DynamicMaterial->SetScalarParameterValue("Opacity", VarNodeColor.A);
			}
		}
	}
}
#endif	// WITH_EDITOR

FSlateBrush* UFlatNodesSettings::CreateHeaderBrush()
{
	FSlateBrush* SlateBrush = new FSlateBrush();

	const FString MaterialPath = FString("/FLatNodes/Materials/Box.Box");
	UMaterial* Material = LoadObject<UMaterial>(nullptr, *MaterialPath);
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	DynamicMaterial->SetScalarParameterValue("UseGradient", bHeaderUseGradient);
	DynamicMaterial->SetVectorParameterValue("Color", FVector(HeaderBrightness, HeaderBrightness, HeaderBrightness));
	DynamicMaterial->SetScalarParameterValue("Opacity", HeaderOpacity);
	DynamicMaterial->AddToRoot();

	SlateBrush->SetResourceObject(DynamicMaterial);
	SlateBrush->DrawAs = ESlateBrushDrawType::Box;
	SlateBrushes.Add("HeaderBrush", SlateBrush);

#if UE_VERSION_OLDER_THAN(5, 7, 0) // <5.7.0
	SlateBrush->Margin = FMargin(0, -1.0f / 32.0f, -3.0f / 20.0f, 0);
#endif // pre-5.7.0

	return SlateBrush;
}

FSlateBrush* UFlatNodesSettings::CreateBodyBrush()
{
	FSlateBrush* SlateBrush = new FSlateBrush();

	const FString MaterialPath = FString("/FLatNodes/Materials/Box.Box");
	UMaterial* Material = LoadObject<UMaterial>(nullptr, *MaterialPath);
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	DynamicMaterial->SetVectorParameterValue("Color", FVector(RegularNodeColor.R, RegularNodeColor.G, RegularNodeColor.B));
	DynamicMaterial->SetScalarParameterValue("Opacity", RegularNodeColor.A);
	DynamicMaterial->AddToRoot();

	SlateBrush->SetResourceObject(DynamicMaterial);
	SlateBrush->DrawAs = ESlateBrushDrawType::Box;
	SlateBrushes.Add("BodyBrush", SlateBrush);

	return SlateBrush;
}

FSlateBrush* UFlatNodesSettings::CreateBodyBrush_Var()
{
	FSlateBrush* SlateBrush = new FSlateBrush();

	const FString MaterialPath = FString("/FLatNodes/Materials/Box.Box");
	UMaterial* Material = LoadObject<UMaterial>(nullptr, *MaterialPath);
	UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

	DynamicMaterial->SetVectorParameterValue("Color", FVector(VarNodeColor.R, VarNodeColor.G, VarNodeColor.B));
	DynamicMaterial->SetScalarParameterValue("Opacity", VarNodeColor.A);
	DynamicMaterial->AddToRoot();

	SlateBrush->SetResourceObject(DynamicMaterial);
	SlateBrush->DrawAs = ESlateBrushDrawType::Box;
	SlateBrushes.Add("BodyBrush_Var", SlateBrush);

	return SlateBrush;
}

void UFlatNodesSettings::SetNodeTitleColor(const FSlateColor& Color)
{
	FSlateStyleSet* Style = (FSlateStyleSet*)&FAppStyle::Get();

	// Change the color used by "Graph.Node.NodeTitle" style. Bypass the use of const by GetWidgetStyle().
	FTextBlockStyle& GraphNodeTitle = const_cast<FTextBlockStyle&>(FAppStyle::Get().GetWidgetStyle<FTextBlockStyle>("Graph.Node.NodeTitle"));
	GraphNodeTitle.SetColorAndOpacity(Color);
	Style->Set("Graph.Node.NodeTitle", GraphNodeTitle);

	// To see the change on node titles, we also need to update "Graph.Node.NodeTitleInlineEditableText" style. Bypass the use of const by GetWidgetStyle().
	FInlineEditableTextBlockStyle& GraphNodeTitleInlineEditableText = const_cast<FInlineEditableTextBlockStyle&>(FAppStyle::Get().GetWidgetStyle<FInlineEditableTextBlockStyle>("Graph.Node.NodeTitleInlineEditableText"));
	GraphNodeTitleInlineEditableText.SetTextStyle(GraphNodeTitle);
	Style->Set("Graph.Node.NodeTitleInlineEditableText", GraphNodeTitleInlineEditableText);
}

void UFlatNodesSettings::RefreshCurrentTheme()
{
	// Get the current theme. Bypass the use of const by GetCurrentTheme().
	FStyleTheme& Theme = const_cast<FStyleTheme&>(USlateThemeManager::Get().GetCurrentTheme());
	// Simulate a change in the current theme to force applyTheme() to fire.
	Theme.LoadedDefaultColors.Empty();
	// Refresh the theme to see the colors change.
	USlateThemeManager::Get().ApplyTheme(USlateThemeManager::Get().GetCurrentThemeID());
}

#undef LOCTEXT_NAMESPACE
