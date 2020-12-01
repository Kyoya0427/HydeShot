//======================================================
// File Name	: NeuralNetworkData.h
// Summary		: �j���[�����l�b�g���[�N���
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\GameObject.h>

class NeuralNetworkManager;

class NeuralNetworkData :public GameObject
{
public:
	//�R���X�g���N�^
	NeuralNetworkData();
	//�f�X�g���N�^
	~NeuralNetworkData();

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
	//�j���[�����l�b�g���[�N�̃f�[�^���擾
	void SetNeuralNetwork(NeuralNetworkManager* neuralNetwork) { m_neuralNetwork = neuralNetwork; }

private:
	//�j���[�����l�b�g���[�N�}�l�[�W���[
	NeuralNetworkManager* m_neuralNetwork;

};