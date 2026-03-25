/**
 * @file   RotationCommand.cpp
 *
 * @brief  回転コマンドに関するソースファイル
 *
 * @author 制作者名　福地貴翔　
 *
 * @date   日付　2026/03/22
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "RotationCommand.h"
#include "Game/Message/Messenger.h"
#include"Game/Object/GameObject.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] direction 回転方向
 */
RotationCommand::RotationCommand(const float& direction)
    :
    m_direction{direction}
{
}

/**
 * @brief デストラクタ
 */
RotationCommand::~RotationCommand()
{
}

/**
 * @brief コマンド実行
 *
 * @param[in] objectID  コマンドを送るオブジェクトの番号
 *
 * @return なし
 */
void RotationCommand::Execute(const int& objectID)
{
    //フレーム間時間
    float dt = Messenger::GetInstance()->GetElapsedTime();
    //回転量
    float angle = m_direction * ROTATION_SPEED_Y_ANGLE * dt;
    //回転させるオブジェクトを取得
    auto obj = Messenger::GetInstance()->GetObject(objectID);
    //クォータニオンに変換
    auto rot = DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(
        DirectX::SimpleMath::Vector3::UnitY,
        angle
    );

    obj->SetQuaternion(obj->GetQuaternion() * rot);
}



