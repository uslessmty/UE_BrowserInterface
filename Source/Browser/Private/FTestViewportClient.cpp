#include "FTestViewportClient.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h" // For GEngine

FTestViewportClient::FTestViewportClient()
    : FEditorViewportClient(nullptr, nullptr)
    , LastViewRotation(FRotator::ZeroRotator)
{
    SetViewLocation(FVector::ZeroVector);
    SetViewRotation(FRotator::ZeroRotator);
    ViewFOV = 90.0f;
}

void FTestViewportClient::Tick(float DeltaSeconds)
{
    FEditorViewportClient::Tick(DeltaSeconds); // 调用基类的 Tick 函数
    
    // 获取当前视口角度
    FRotator CurrentViewRotation = GetViewRotation();
    
    // 检查视口角度是否变化
    if (!CurrentViewRotation.Equals(LastViewRotation, KINDA_SMALL_NUMBER))
    {
        UE_LOG(LogTemp, Log, TEXT("Viewport Rotation Changed: Pitch=%f, Yaw=%f, Roll=%f"), 
            CurrentViewRotation.Pitch, CurrentViewRotation.Yaw, CurrentViewRotation.Roll);
        
        LastViewRotation = CurrentViewRotation; // 更新上一次的视口角度
    }
}

void FTestViewportClient::Draw(FViewport* InViewport, FCanvas* Canvas)
{
    FEditorViewportClient::Draw(InViewport, Canvas);
    // 自定义的绘制逻辑（如果有需要）
}