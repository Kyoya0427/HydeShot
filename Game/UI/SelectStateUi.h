//======================================================
// File Name	: SelectStateUi.h
// Summary		: �I�������X�e�C�g
// Date			: 2020/6/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <Game/GameObject/GameObject.h>

#include <Game/CharaState/CharaStateID.h>

class SelectStateUi :public GameObject
{
public:
	//�R���X�g���N�^
	SelectStateUi();
	~SelectStateUi();

public:
	void Initialize();
	void Update(const DX::StepTimer& timer) override;
	void Render() override;
	void OnCollision(GameObject* object) override;

public:
	void SetSelectState(wchar_t* state)  { m_selectState = state; }
	void SetSelectMode(wchar_t* mode)    { m_selectMode = mode; }

private:
	wchar_t*        m_selectState;
	wchar_t*		 m_selectMode;
};