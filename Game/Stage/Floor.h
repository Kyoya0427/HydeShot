//======================================================
// File Name	: Floor.h
// Summary	: ���N���X
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once


#include <Game\GameObject\IGameObject.h>
#include <DirectXTK\Model.h>

class Stage;

class Floor : public IGameObject
{
public:
	// ���̏��
	enum State
	{
		NONE,
		NORMAL,		// �ʏ�
		WATER,

		STATE_NUM,
		
	};

	

private:
	// �X�e�[�W�ւ̃|�C���^
	Stage* m_stage;

	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models[STATE_NUM];

	// ���̏��
	State m_state;

	// �ʒu
	DirectX::SimpleMath::Vector3 m_pos;

	// �_���[�W�t���O�i�P�t���[���ɂP�񂵂��_���[�W������Ȃ��悤�ɂ��邽�߂̃t���O�j
	bool m_damageFlag;

	// �_���[�W�������Ď��̏�ԂɈڍs����܂ł̃^�C�}�[
	float m_damageTimer;

public:
	// �R���X�g���N�^
	Floor();

	// �������֐�
	void Initialize(Stage* stage, int x, int y);

	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render(const DX::StepTimer & timer) override;

	void OnCollision(IGameObject* object) override;

	// ���f���ݒ�֐�
	void SetModel(State state, DirectX::Model* model);

	// ���̏�Ԃ�ݒ肷��֐�
	void SetState(Floor::State state) { m_state = state; }

	// ���̏�Ԃ��擾����֐�
	Floor::State GetState() { return m_state; }

	

	// ���Z�b�g�֐�
	void Reset();
};
