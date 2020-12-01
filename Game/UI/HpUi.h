//======================================================
// File Name	: HpUi.h
// Summary		: �j���[�����l�b�g���[�N���
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\GameObject.h>

class HpUi :public GameObject
{
public:
	//�R���X�g���N�^
	HpUi();
	//�f�X�g���N�^
	~HpUi();

public:
	//������
	void Initialize();
	//�X�V
	void Update(const DX::StepTimer& timer) override;
	//�`��
	void Render() override;
	//����������̏���
	void OnCollision(GameObject* object) override;

public:
	//�v���C���[��HP��ݒ�
	void SetPlayerHp(int hp);
	//�G�l�~�[��HP��ݒ�
	void SetEnemyHp(int hp);

private:
	//�v���C���[��HP
	int			m_playerHp;
	//�G�l�~�[��HP
	int         m_enemyHp;

};

/// <summary>
/// �v���C���[��HP��ݒ�
/// </summary>
/// <param name="hp"></param>
inline void HpUi::SetPlayerHp(int hp)
{
	m_playerHp = hp;
}

/// <summary>
/// �G�l�~�[��HP��ݒ�
/// </summary>
/// <param name="hp"></param>
inline void HpUi::SetEnemyHp(int hp)
{
	m_enemyHp = hp;
}