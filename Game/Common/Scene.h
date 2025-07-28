#pragma once
// ヘッダファイルの読み込み ===================================================
#include"pch.h"
#include <string>
#include"Game/Common/Graphics.h"
#include"Game/Shader.h"
// クラスの宣言 ===============================================================

class SceneManager;


// クラスの定義 ===============================================================
/**
  * @brief シーンの基底クラス
  */
class Scene
{
	// クラス定数の宣言 -------------------------------------------------
public:



// データメンバの宣言 -----------------------------------------------
private:
	SceneManager* m_pSceneManager;	///< シーンマネージャ
	Graphics* m_pGraphics;	///< グラフィックス
// メンバ関数の宣言 -------------------------------------------------
// コンストラクタ/デストラクタ
public:
	// コンストラクタ
	Scene(SceneManager* pSceneManager);

	// デストラクタ
	virtual ~Scene();


	// 操作
public:
	// 初期化処理
	virtual void Initialize() = 0;

	// 更新処理
	virtual void Update(float elapsedTime) = 0;

	// 描画処理
	virtual void Render() = 0;

	// 終了処理
	virtual void Finalize() = 0;


// 取得/設定
public:


// 内部実装
protected:
	//シーンの変更
	void ChangeScene(const std::string& nextSceneName,bool isStack=false);
	//シーンのポップ
	void PopScene();

	//共有データの読み込み
	void ReadSharedData(const std::string& key, int* pValue) const;
	void ReadSharedData(const std::string& key, float* pValue) const;
	void ReadSharedData(const std::string& key, std::string* pValue) const;
	void ReadSharedData(const std::string& key, bool* pValue) const;

	//共有データの読み込み
	void WriteSharedData(const std::string& key, int		 value) const;
	void WtiteSharedData(const std::string& key, float		 value) const;
	void WriteSharedData(const std::string& key, std::string value) const;
	void WriteSharedData(const std::string& key, bool value) const;

	//グラフィックスの取得
	Graphics* GetGraphics();
};

