//======================================================
// File Name	: HpUi.h
// Summary		: ニューラルネットワーク情報
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\GameObject.h>

class HpUi :public GameObject
{
public:
	//コンストラクタ
	HpUi();
	//デストラクタ
	~HpUi();

public:
	//初期化
	void Initialize();
	//更新
	void Update(const DX::StepTimer& timer) override;
	//描画
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

public:
	//プレイヤーのHPを設定
	void SetPlayerHp(int hp);
	//エネミーのHPを設定
	void SetEnemyHp(int hp);

private:
	//プレイヤーのHP
	int			m_playerHp;
	//エネミーのHP
	int         m_enemyHp;

};

/// <summary>
/// プレイヤーのHPを設定
/// </summary>
/// <param name="hp"></param>
inline void HpUi::SetPlayerHp(int hp)
{
	m_playerHp = hp;
}

/// <summary>
/// エネミーのHPを設定
/// </summary>
/// <param name="hp"></param>
inline void HpUi::SetEnemyHp(int hp)
{
	m_enemyHp = hp;
}