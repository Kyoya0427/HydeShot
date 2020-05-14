//======================================================
// File Name	: Player.h
// Summary	: �v���C���[�N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once
#include <DirectXTK\GeometricPrimitive.h>

#include <Game\Controller\CharacterController.h>

class Stage;

class Player : public CharacterController
{
public:
	// �v���C���[�̃^�C�v�ʃ��f��
	enum ModelType
	{
		NORMAL,	// �ʏ�
		SELECTION_RANGE,
		CURSOR,

		MODEL_TYPE_NUM
	};

	// �v���C���[�̏��
	enum STATE
	{
		STANDING,	// �ʏ�
		MOVE,
		ATTACK,
		DEAD,		// ���S
		NEXT
	};

	// ���Ƃ̔���p�̕��ƍ���
	static const float WIDTH;
	static const float HEIGHT;


	;

private:
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models[MODEL_TYPE_NUM];

	// �v���C���[�̏��
	STATE m_state;

	// �X�e�[�W�ւ̃|�C���^
	Stage* m_stage;
	
	std::unique_ptr<DirectX::GeometricPrimitive> m_geometricPrimitive;

	bool     m_isChoice;
public:
	// �R���X�g���N�^
	Player(const ObjectTag tag);
	~Player();
	// �������֐�
	void Initialize(int x, int y, Stage* stage);

public:
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render(const DX::StepTimer& timer) override;

	void OnCollision(IGameObject* object) override;

public:
	// ���f���ݒ�֐�
	void SetModel(ModelType modelType, DirectX::Model* model);

	float SLerap(float start, float end, float t);

	

private:

};
