//======================================================
// File Name	: Blink.cpp
// Summary		: 画像をブリンク
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================

#include "Blink.h"

/// <summary>
/// コンストラクタ
/// </summary>
Blink::Blink()
	: m_isBlink(true), m_blinkTime(0.0f), m_interval(0.0f), m_stopFlag(true)
{
}

/// <summary>
/// デストラクタ	
/// </summary>
Blink::~Blink()
{
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="interval">インターバル</param>
void Blink::Initialize(float interval)
{
	m_interval = interval;
}

/// <summary>
/// 更新
/// </summary>
/// <param name="timer">タイマー</param>
void Blink::Update(const DX::StepTimer & timer)
{
	if (m_stopFlag) return;

	float elapsedTime = float(timer.GetElapsedSeconds());

	m_blinkTime += elapsedTime;
	if (m_blinkTime >= m_interval)
	{
		m_isBlink   = !m_isBlink;
		m_blinkTime = 0.0f;
	}

}

/// <summary>
/// 
/// </summary>
/// <returns></returns>
bool Blink::GetState()
{
	return m_isBlink;
}

/// <summary>
/// リセット
/// </summary>
/// <param name="flag">使用するか</param>
void Blink::Reset(bool flag)
{
	m_isBlink = flag;
	m_blinkTime = 0.0f;
}

/// <summary>
/// スタート
/// </summary>
void Blink::Start()
{
	m_stopFlag = false;
}

/// <summary>
/// ストップ
/// </summary>
void Blink::Stop()
{
	m_stopFlag = true;
}
