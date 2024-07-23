#include "STestEditorViewport.h"
#include "FTestViewportClient.h"

void STestEditorViewport::Construct(const FArguments& InArgs)
{
	SEditorViewport::Construct(SEditorViewport::FArguments());
}

STestEditorViewport::STestEditorViewport()
{
}

STestEditorViewport::~STestEditorViewport()
{
}

TSharedRef<FEditorViewportClient> STestEditorViewport::MakeEditorViewportClient()
{
	ViewportClient = MakeShareable(new FTestViewportClient());
	return ViewportClient.ToSharedRef();
}

void STestEditorViewport::SetViewportRotation(const FRotator& NewRotation)
{
	if (ViewportClient.IsValid())
	{
		ViewportClient->SetViewRotation(NewRotation);
	}
}

FRotator STestEditorViewport::GetViewportRotation() const
{
	if (ViewportClient.IsValid())
	{
		return ViewportClient->GetViewRotation();
	}
	return FRotator::ZeroRotator;
}