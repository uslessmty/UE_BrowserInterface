#pragma once

#include "CoreMinimal.h"
#include "EditorViewportClient.h"

class FTestViewportClient : public FEditorViewportClient
{
public:
    FTestViewportClient();
    
    virtual void Tick(float DeltaSeconds) override;
    virtual void Draw(FViewport* InViewport, FCanvas* Canvas) override;
    // 可选：重载其他的虚函数以便自定义视口行为

private:
    // 保存上一次的视口角度
    FRotator LastViewRotation;
};