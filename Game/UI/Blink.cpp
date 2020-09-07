//======================================================
// File Name	: Blink.cpp
// Summary		: �摜���u�����N
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================

#include "Blink.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
Blink::Blink()
	: m_isBlink(true), m_blinkTime(0.0f), m_interval(0.0f), m_stopFlag(true)
{
}

/// <summary>
/// �f�X�g���N�^	
/// </summary>
Blink::~Blink()
{
}

/// <summary>
/// ������
/// </summary>
/// <param name="interval">�C���^�[�o��</param>
void Blink::Initialize(float interval)
{
	m_interval = interval;
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="timer">�^�C�}�[</param>
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
/// ���Z�b�g
/// </summary>
/// <param name="flag">�g�p���邩</param>
void Blink::Reset(bool flag)
{
	m_isBlink = flag;
	m_blinkTime = 0.0f;
}

/// <summary>
/// �X�^�[�g
/// </summary>
void Blink::Start()
{
	m_stopFlag = false;
}

/// <summary>
/// �X�g�b�v
/// </summary>
void Blink::Stop()
{
	m_stopFlag = true;
}
