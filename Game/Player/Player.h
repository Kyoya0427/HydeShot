//======================================================
// File Name	: Player.h
// Summary		: �v���C���[�N���X
// Date			: 2019/12/05
// Author		: Takafumi Ban
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>



class Player : public IGameObject
{
public:
	// �v���C���[�̃^�C�v�ʃ��f��
	enum ModelType
	{
		NORMAL,	// �ʏ�
		WING,	// �E�C���O�t��

		MODEL_TYPE_NUM
	};

	// �v���C���[�̏��
	enum STATE
	{
		STATE_NORMAL,	// �ʏ�
		STATE_JUMP,		// �W�����v��
		STATE_HIT,		// ������΂�����
		STATE_FALL,		// ������
		STATE_DEAD,		// ���S
	};

	// ���Ƃ̔���p�̕��ƍ���
	static const float WIDTH;
	static const float HEIGHT;

	// �v���C���[�̍ő�ړ����x
	static const float MAX_SPEED;

	// �v���C���[�̏d��
	static const float WEIGHT;

	// ���ɑ΂��門�C�W��
	static const float FRICTION;

	// �W�����v���Ă���t���[����
	static const int JUMP_FRAME;
	// �W�����v�̍���
	static const float JUMP_HEIGHT;


private:
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models[MODEL_TYPE_NUM];

	// �v���C���[�̏��
	STATE m_state;

	// �p���[�A�b�v
	int m_powerupParts;

	// �W�����v�p�[�c�𑕒����Ă��邩�H
	bool m_jumpParts;

	// �W�����v�J�E���^�[
	int m_jumpCounter;
	// �������̉�]
	float m_fallRotateAngle;

public:
	// �R���X�g���N�^
	Player(const ObjectTag tag);
	~Player();
	// �������֐�
	void Initialize(int x, int y);

	// ���f���ݒ�֐�
	void SetModel(ModelType modelType, DirectX::Model* model);


	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render(const DX::StepTimer & timer) override;

	void OnCollision(IGameObject* object) override;


	float SLerap(float start, float end, float t);
private:

};
