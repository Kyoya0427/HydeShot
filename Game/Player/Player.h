//======================================================
// File Name	: Player.h
// Summary		: �v���C���[�N���X
// Date			: 2019/12/05
// Author		: Takafumi Ban
//======================================================
#pragma once

#include <Game\GameObject\IGameObject.h>

class Stage;

class Player : public IGameObject
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


	struct Map
	{
		int size;
		int map[9][9];
	};

	struct RangeMap
	{
		Map move;
		Map attack;
	};

private:
	// ���f���f�[�^�ւ̃|�C���^
	DirectX::Model* m_models[MODEL_TYPE_NUM];

	// �v���C���[�̏��
	STATE m_state;

	// �X�e�[�W�ւ̃|�C���^
	Stage* m_stage;
	
	RangeMap m_rangeMap;

	DirectX::SimpleMath::Vector3 m_cursorPos;

	bool     m_isChoice;
public:
	// �R���X�g���N�^
	Player(const ObjectTag tag);
	~Player();
	// �������֐�
	void Initialize(int x, int y, Stage* stage);

	// ���f���ݒ�֐�
	void SetModel(ModelType modelType, DirectX::Model* model);

	// �X�V
	void Update(const DX::StepTimer& timer) override;
	// �`��֐�
	void Render(const DX::StepTimer & timer) override;

	void OnCollision(IGameObject* object) override;



	float SLerap(float start, float end, float t);

	void MoveRange(Map* map, int x, int y, int step_count);
	void AttackRange(Map* map, int x, int y, int range_count);
	void MovePhaseRender();
	void MoveCursor();

private:
	void GetMap(int x, int y, int size1, int size2);
};
