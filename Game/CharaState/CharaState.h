//======================================================
// File Name	: CharaState.h
// Summary		: �L�����̃X�e�[�g
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/Character.h>

#include <Game/Common/StepTimer.h>

class Character;
class CharacterController;
class NeuralNetworkManager;

class CharaState
{
public:
	//�R���X�g���N�^
	CharaState()
		: m_neuralNetwork()
		, m_chara()
		, m_enemy()
	{
	};
	//�f�X�g���N�^
	virtual ~CharaState() = default;

public:
	//������
	virtual void Initialize(Character* chara, Character* enemy, NeuralNetworkManager* neuralNetwork) = 0;
	//�X�V
	virtual void Update(const DX::StepTimer& timer) = 0;

public:
	NeuralNetworkManager* GetNeuralNetworkManager() { return m_neuralNetwork; }
	Character* GetChara() { return m_chara; }
	Character* GetEnemy() { return m_enemy; }

public:
	void SetNeuralNetworkManager(NeuralNetworkManager* neuralNetworkManager) { m_neuralNetwork = neuralNetworkManager; }
	void SetChara(Character* chara) { m_chara = chara; }
	void SetEnemy(Character* enemy) { m_enemy = enemy; }

private:
	//�j���[�����l�b�g���[�N�}�l�[�W���[
	NeuralNetworkManager*		m_neuralNetwork;
	//�X�e�C�g���삷��L�����N�^�[
	Character*                  m_chara;
	//�G�L�����N�^�[
	Character*                  m_enemy;
};