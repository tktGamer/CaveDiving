/**
 * @file   InputHandler.cpp
 *
 * @brief  入力管理に関するソースファイル
 *
 * @author 制作者名 福地貴翔
 *
 * @date   日付  2026/03/22
 */
 // ヘッダファイルの読み込み ===================================================
#include "pch.h"
#include "InputHandler.h"
// メンバ関数の定義 ===========================================================
/**
 * @brief コンストラクタ
 *
 * @param[in] なし
 */
InputHandler::InputHandler()
{
}

/**
 * @brief デストラクタ
 */
InputHandler::~InputHandler()
{
}

/**
 * @brief コマンドの登録
 *
 * @param[in] key  対応キー
 * @param[in] type キーの入力状態
 * @param[in] cmd　コマンド
 *
 * @return なし
 */
void InputHandler::Register(const DirectX::Keyboard::Keys& key, const InputType& type, std::unique_ptr<ICommand> cmd)
{
	m_commands.emplace_back(InputCommand{ key,type,std::move(cmd) });
}

/**
 * @brief キー判定
 *
 * @param[in] objectID  コマンドを送るオブジェクトの番号
 *
 * @return なし
 */
void InputHandler::Update(const int& objectID)
{
    DirectX::Keyboard::KeyboardStateTracker* tracker = Graphics::GetInstance()->GetKeyboardTracker();

    for (InputCommand& entry : m_commands)
    {
        bool trigger = false;
        //入力されているか判定
        switch (entry.type)
        {
        case InputType::Pressed:
            trigger = tracker->IsKeyPressed(entry.key);
            break;

        case InputType::Released:
            trigger = tracker->IsKeyReleased(entry.key);
            break;

        case InputType::Hold:
            trigger = tracker->GetLastState().IsKeyDown(entry.key);
            break;
        }
        //入力されていたらコマンドを送る
        if (trigger)
        {
            entry.command->Execute(objectID);
        }
    }
}