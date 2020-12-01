//======================================================
// File Name	: NeuralNetworkManager.h
// Summary		: �j���[�����l�b�g���[�N�Ń��[�h�I��
// Date			: 2020/6/9
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <vector>

#include <Game/CharaState/CharaStateID.h>

#include <Game/GameObject/SelectMode.h>

class Character;
class NeuralNetwork;

class NeuralNetworkManager
{
public:
	//�O���o�̓f�[�^
	struct OutputData
	{
		float inputDis;
		float inputLeft;
		float inputRight;
		float inputWall;
		float inputShoot;
		float outputDis;
		float outputLeft;
		float outputRight;
		float outputWall;
		float outputShoot;
		char* outputChoiceMode;
	};

public:
	//�R���X�g���N�^
	NeuralNetworkManager(Character* character, Character* enemy);
	//�f�X�g���N�^
	virtual ~NeuralNetworkManager();

public:
	//�f�[�^�̐�
	static const int MAX_DATA_H = 54;
	static const int MAX_DATA_W = 10;
	//���͑w
	static const int INNPUT_LAYER = 6;
	//���ԑw
	static const int MIDDLE_LAYER = 20;
	//�o�͒l
	static const int OUTPUT_LAYER = 5;
	//�w�K��
	static const float  LEARNING_RATE;
	//�������^��
	static const float  MOMENTUM;
	//�ő勗��
	static const float  MAX_DISTANCE;
	//����
	static const float SHOT_JUDGMENT;
	//��
	static const float WALL_JUDGMENT;
	//����
	static const float DIS_JUDGMENT;
public:
	//�f�[�^���擾
	void InitializeTraining(wchar_t* fname);
	//�j���[�����l�b�g���[�N�̏�����
	void InitializeNeuralNetwork();
	//�w�K�f�[�^����͂��Ď��s����
	void InputTrainingData(SelectMode mode);
	//�s���p�^�[����I��
	CharaStateID BehaviorSelection();
	//���E����
	void SearchDirection(Character* character, Character* enemy);
	// ���όv�Z
	DirectX::SimpleMath::Vector3 Rotate(float angle, const DirectX::SimpleMath::Vector3& u);

public:
	// ���͂Əo�͂̒l���O���ɏo��
	void OutputDataFile(char* fname);
	//�f�[�^���擾
	const OutputData& GetOutputData() { return m_data; }

public: 
	//�f�[�^���i�[
	std::vector<std::vector<float>>  m_training;
	//�j���[�����l�b�g���[�N
	std::unique_ptr<NeuralNetwork>   m_neuralNetwork;
	//���@
	Character*                       m_character;
	//�G
	Character*                       m_enemy;

	//�v�Z���̃f�[�^
	OutputData					     m_data;
	//�S�Ă̌v�Z�f�[�^
	std::vector<OutputData>          m_outputData;
	//�v�Z���̃G���[��
	float                            m_error;
	//�����ɂ���
	bool                             m_isDirectionLeft;
	//�E���ɂ���
	bool                             m_isDirectionRight;
	//����
	float                            m_distance;

};

