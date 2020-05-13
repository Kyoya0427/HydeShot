//======================================================
// File Name	: Enemy.h
// Summary	: �G�l�~�[
// Date		: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>


class Enemy : public IGameObject
{
public:
	// �G�̃^�C�v�ʃ��f��
	enum ModelType
	{
		NORMAL,	// �ʏ�
		

		MODEL_TYPE_NUM
	};
	// �G�̏��
	enum STATE
	{
		STANDING,	// �ʏ�
		MOVE,
		ATTACK,
		DEAD,		// ���S
		NEXT
	};
	
	// �v�l�Ԋu�i�P�ʁF�b�j
	static const float THINK_INTERVAL;

public: 
	Enemy(const ObjectTag tag);
	// ������
	void Initialize(int x, int y);
	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��
	void Render(const DX::StepTimer & timer) override;
	//�Փˌ�̏���
	void OnCollision(IGameObject* object) override;

public:
	// ���f���ݒ�
	void SetModel(ModelType modelType, DirectX::Model* model);
	
private:
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models[MODEL_TYPE_NUM];
	// �v���C���[�̏��


};