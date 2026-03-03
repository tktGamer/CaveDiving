/**
 * @file   PartObject.cpp
 *
 * @brief  オブジェクトを構成する体の一部に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付　2026/03/03
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "PartObject.h"


// RotationLimit::OFFの定義
const PartObject::RotationLimit PartObject::RotationLimit::OFF = 
{
    DirectX::SimpleMath::Vector3::Zero,
    DirectX::SimpleMath::Vector3::Zero,
    false
};
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] root 所持するキャラクタークラス
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
PartObject::PartObject(Character* root,const GameObject* parent, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	GameObject{ Tag::ObjectPart,parent,initialPosition,initialAngle },
	m_parentCharacter{ root },
    m_rotationLimit{}
{
}

/**
 * @brief デストラクタ
 */
PartObject::~PartObject()
{
}

/**
 * @brief メッセージ対応処理
 *
 * @param[in] messageID メッセージ
 *
 * @return なし
 */
void PartObject::OnMessegeAccepted(Message::MessageID messageID)
{
}

/**
 * @brief 角度制限を無効化
 *
 * @param[in] なし
 *
 * @return なし
 */
void PartObject::RotationLimitOFF()
{
    m_rotationLimit.enable = false;
}

/**
 * @brief 角度制限を有効化
 *
 * @param[in] なし
 *
 * @return なし
 */
void PartObject::RotationLimitON()
{
    m_rotationLimit.enable = true;
}


/**
 * @brief 角度制限を考慮してローカル回転を設定
 *
 * @param[in] eulerAngle  設定するラジアン角 y:yaw x:Pitch z:Roll 
 *
 * @return なし
 */
void PartObject::SetLocalRotationEuler(const DirectX::SimpleMath::Vector3& eulerAngle)
{
    
    DirectX::SimpleMath::Vector3 result = eulerAngle;
    //角度制限が有効なら
    if (m_rotationLimit.enable)
    {
        //制限内に調整する
        result.x = TKTLib::Clamp(eulerAngle.x, m_rotationLimit.min.x, m_rotationLimit.max.x);
        result.y = TKTLib::Clamp(eulerAngle.y, m_rotationLimit.min.y, m_rotationLimit.max.y);
        result.z = TKTLib::Clamp(eulerAngle.z, m_rotationLimit.min.z, m_rotationLimit.max.z);
    }
    //ローカルの回転
    m_localEuler = result;
    //クォータニオンに変換
    DirectX::SimpleMath::Quaternion quaternion = DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
        result.y,
        result.x,
        result.z);

    //ローカル回転を更新
    SetQuaternion(quaternion); 
}

/**
 * @brief ローカル角度を取得
 *
 * @param[in] なし
 *
 * @return ローカル角度
 */
const DirectX::SimpleMath::Vector3& PartObject::GetLocalEuler()
{
    return m_localEuler;
}

/**
 * @brief 角度制限設定
 *
 * @param[in] rotationLimit  角度制限
 *
 * @return なし
 */
void PartObject::SetRotationLimit(const RotationLimit& rotationLimit)
{
    m_rotationLimit = rotationLimit;
}

/**
 * @brief 部品をもつキャラクターの取得
 *
 * @param[in] なし
 *
 * @return 部品をもつキャラクター
 */
Character* PartObject::GetRootCharacter()
{
	return m_parentCharacter;
}
