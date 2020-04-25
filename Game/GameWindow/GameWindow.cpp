//======================================================
// File Name	: GameWindow.cpp
// Summary		: �Q�[���E�B���h�E
// Date			: 2019/11/26
// Author		: Takafumi Ban
//======================================================
#include "GameWindow.h"

#include <DirectXTK\WICTextureLoader.h>

#include <Game\Stage\Stage.h>

#include <Game\Common\GameContext.h>
#include <Game\Common\DeviceResources.h>

#include <Game\Camera\Camera.h>
#include <Game\GameObject\ObjectManager.h>
#include <Game\GameObject\GameObjectManager.h>

#include <Game\UI\InfoWindow.h>


#include <Game\GameState\GameStateManager.h>

#include "Bg.h"

const float GameWindow::DIR_ANGLE[] =
{
	DirectX::XMConvertToRadians(45.0f * 0),
	DirectX::XMConvertToRadians(45.0f * 1),
	DirectX::XMConvertToRadians(45.0f * 2),
	DirectX::XMConvertToRadians(45.0f * 3),
	DirectX::XMConvertToRadians(45.0f * 4),
	DirectX::XMConvertToRadians(45.0f * 5),
	DirectX::XMConvertToRadians(45.0f * 6),
	DirectX::XMConvertToRadians(45.0f * 7),
};

const float GameWindow::GRAVITY = 9.8f;
const float GameWindow::FALL_SPEED = 8.0f;
const float GameWindow::FALL_DISTANCE = 10.0f;
const float GameWindow::FALL_ROTATE_SPEED = 180.0f;
// ���E���h��
const int GameWindow::ROUND_MAX = 3;
// �n�C�X�R�A�̏����l�i1000 �_�j
const int GameWindow::HIGH_SCORE = 1000;

GameWindow::GameWindow()
	: m_gameState(STATE_PARTS_SELECT)
	, m_round(0)
	, m_life(0)
	, m_getPowerupParts(0)
	, m_powerupParts(0)
	, m_usePowerupParts(0)
	, m_getJumpParts(0)
	, m_jumpParts(0)
	, m_useJumpParts(0)
	, m_selectParts(POWERUP)
	, m_selectPartsDisplayFlag(false)
	, m_highScore(HIGH_SCORE)
	, m_score(0)
	, m_highScoreUpdate(false)
{
	SetDrawPrio(GameWindow::DRAW_TOP);
}

GameWindow::~GameWindow()
{
	if (m_bg != nullptr)
	{
		m_bg->Invalidate();
		m_bg = nullptr;
	}
}

void GameWindow::Initialize()
{
	m_camera = std::make_unique<Camera>();
	m_camera->Initialize();
	GameContext::Register<Camera>(m_camera.get());

	m_bg = std::make_unique<Bg>();
	m_bg->Initialize();
	GameContext::Get<ObjectManager>()->GetGameOM()->Add(std::move(m_bg));

	m_stage = std::make_unique<Stage>();
	m_stage->Initialize(); 


	InitializeGame();
	// �G�t�F�N�g�̍쐬
	m_batchEffect = std::make_unique<DirectX::BasicEffect>(GameContext().Get<DX::DeviceResources>()->GetD3DDevice());
	m_batchEffect->SetTextureEnabled(true);
	m_batchEffect->SetVertexColorEnabled(true);

	// ���̓��C�A�E�g����
	void const* shaderByteCode;
	size_t byteCodeLength;
	m_batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	GameContext().Get<DX::DeviceResources>()->GetD3DDevice()->CreateInputLayout(DirectX::VertexPositionColorTexture::InputElements, 
																				DirectX::VertexPositionColorTexture::InputElementCount,
																				shaderByteCode, byteCodeLength, m_inputLayout.GetAddressOf());
	// �v���~�e�B�u�o�b�`�̍쐬
	m_primitiveBatch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColorTexture>>(GameContext().Get<DX::DeviceResources>()->GetD3DDeviceContext());
	// �q�b�g�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\hit_effect.png", nullptr, m_hitEffectTexture.GetAddressOf());
	// �W�����v�G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\jump_effect.png", nullptr, m_jumpEffectTexture.GetAddressOf());
	// ���G�t�F�N�g�p�e�N�X�`���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\smoke_effect.png", nullptr, m_smokeEffectTexture.GetAddressOf());
	// �p�[�c�I����ʗp�̃e�N�X�`���̓ǂݍ���
	DirectX::CreateWICTextureFromFile(GameContext().Get<DX::DeviceResources>()->GetD3DDevice(), L"Resources\\Textures\\partsSelect.png", nullptr, m_partsSelectTexture.GetAddressOf());

	
}

void GameWindow::OnCollision(IGameObject * object)
{
}

void GameWindow::Update(const DX::StepTimer& timer)
{
	auto kb = DirectX::Keyboard::Get().GetState();
	m_tracker.Update(kb);
	float elapsedTime = float(timer.GetElapsedSeconds());

	
	

	switch (m_gameState)
	{
	case STATE_PARTS_SELECT: // �p�[�c�I�����
							 // ��ʂ��J���܂ő҂�
		ActiveOff();
	
		break;
	case STATE_START: // �J�n
					  // �Q�[���X�^�[�g
		m_gameState = StartGame(elapsedTime);
		break;
	case STATE_GAME: // �Q�[����
		m_gameState = PlayGame(elapsedTime);
		if (m_gameState != STATE_GAME)
		{
			
		}
		break;
	case STATE_AGAIN: // �v���C���[�����񂾂̂ōăX�^�[�g
					  // ��ʂ��^�����ɂȂ�܂ő҂�
	
		break;
	case STATE_NEXT: // ���̃X�e�[�W��
					 // ��ʂ��^�����ɂȂ�܂ő҂�
		
		break;
	case STATE_GAMEOVER: // �Q�[���I�[�o�[
						 // ��ʂ��^�����ɂȂ�܂ő҂�
	
		break;
	}
}

void GameWindow::Render(const DX::StepTimer& timer)
{
	DirectX::SimpleMath::Matrix world;
	world = DirectX::SimpleMath::Matrix::CreateTranslation(4.5f, 0.0f, 5.5f);

	if (m_selectPartsDisplayFlag)
	{
		// �p�[�c�I����ʗp�̑���������̕\��
		GameContext::Get<DirectX::SpriteBatch>()->Draw(m_partsSelectTexture.Get(), DirectX::SimpleMath::Vector2(288, 200));
	}
	
}

void GameWindow::GetPowerupParts()
{
	

}

void GameWindow::GetJumpParts()
{
	
}

void GameWindow::ResetPowerupParts()
{


}

void GameWindow::ResetJumpParts()
{
}

GameWindow::GAME_STATE GameWindow::InitializeGame()
{
	InfoWindow* infoWindow = GameContext::Get<InfoWindow>();
	// ���_��������
	SetScore(0);
	// �n�C�X�R�A�X�V�t���O�𗎂Ƃ�
	m_highScoreUpdate = false;
	// �n�C�X�R�A�X�V�ʒm���R�b�Ԃɐݒ�
	m_highScoreBlinkTime = 3.0f;
	// ���E���h����ݒ�
	m_round = 1;

	// �c�@����ݒ�
	m_life = 3;
	// �p���[�A�b�v�p�[�c�̃��Z�b�g
	ResetPowerupParts();
	// �W�����v�p�[�c�̃��Z�b�g
	ResetJumpParts();
	// �X�e�[�W�f�[�^�̓ǂݍ���
	m_stage->LoadStageData(GetStageFilename(m_round));
	// �X�e�[�W�f�[�^�̐ݒ�
	m_stage->SetStageData();
// �p�[�c�I����ʂ�
	return STATE_PARTS_SELECT;

}

GameWindow::GAME_STATE GameWindow::SelectParts(float elapsedTime)
{
	InfoWindow* infoWindow = GameContext::Get<InfoWindow>();
	// �p�[�c������������Ă��Ȃ���΃p�[�c�I����ʂ̓X���[
	if (m_powerupParts == 0 && m_jumpParts == 0) return STATE_START;
	switch (m_selectParts)
	{
	case POWERUP: // �p���[�A�b�v�p�[�c�I��
	
		// ���L�[�������ꂽ
		if (m_tracker.IsKeyPressed(DirectX::Keyboard::Left))
		{
			if (m_usePowerupParts > 0)
			{
				m_usePowerupParts--;
			}
		}

		break;
	case JUMP: // �W�����v�p�[�c�I��
		// ���L�[�������ꂽ
		if (m_tracker.IsKeyPressed(DirectX::Keyboard::Left))
		{
			if (m_useJumpParts > 0)
			{
				m_useJumpParts--;
			}
		}
		// �X�y�[�X�L�[�Ŏ���
		
		break;
	}
	return STATE_PARTS_SELECT;

}

GameWindow::GAME_STATE GameWindow::StartGame(float elapsedTime)
{

	// �Q�[������
	return STATE_GAME;
}

GameWindow::GAME_STATE GameWindow::PlayGame(float elapsedTime)
{
	InfoWindow* infoWindow = GameContext::Get<InfoWindow>();
	GAME_STATE state = STATE_GAME;
	// �v���C���[�̈ړ�����
	return STATE_GAME;
}

void GameWindow::ActiveOff()
{
	
}

void GameWindow::SetScore(int score)
{
	

}

int GameWindow::GetScore()
{
	return m_score;
}

wchar_t * GameWindow::GetStageFilename(int round)
{
	static wchar_t fname[32];
	wsprintfW(fname, L"Resources\\StageData\\Stage01.csv", round);
	return fname;
}

bool GameWindow::CheckEnemyAllDead()
{
	
	return true;
}

void GameWindow::UpdateParts(bool stageClearFlag)
{
	

}
