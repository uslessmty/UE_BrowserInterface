#pragma once

#include "CoreMinimal.h"
#include "SEditorViewport.h"


class FTestViewportClient;

class STestEditorViewport : public SEditorViewport
{
public:
	SLATE_BEGIN_ARGS(STestEditorViewport) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);
	STestEditorViewport();
	~STestEditorViewport();

	// 公开设置视口旋转和获取视口旋转的方法
	void SetViewportRotation(const FRotator& NewRotation);
	FRotator GetViewportRotation() const;

protected:
	/** SEditorViewport interface */
	virtual TSharedRef<FEditorViewportClient> MakeEditorViewportClient() override;

private:
	TSharedPtr<FTestViewportClient> ViewportClient;
};
