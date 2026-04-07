/**
 * @file   OutlineItem.cpp
 *
 * @brief  アウトラインアイテムに関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/01/19
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "OutlineItem.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] info  アイテム情報
 * @param[in] parent　親クラスのポインタ
 * @param[in] initialPosition　初期位置
 * @param[in] initialAngle　初期角度（ラジアン）
 */
OutlineItem::OutlineItem(const Item::ItemInfo& info,const GameObject* parent,
	const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	Item{info,parent,initialPosition,initialAngle}
{
}

/**
 * @brief デストラクタ
 */
OutlineItem::~OutlineItem()
{
}

/**
 * @brief アイテムが取得されたときの追加処理
 *
 * @param[in] other  アイテムを取得したオブジェクト
 *
 * @return  なし
 */
void OutlineItem::OnItemGetExtra(const GameObject* other)
{
	UNREFERENCED_PARAMETER(other);
	//アウトラインをだすようにする
	Messenger::GetInstance()->SetOutLineActive(true);
}