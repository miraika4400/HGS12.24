////////////////////////////////////////////////////
//
//    �Q�[���N���X�̏���[game.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//=============================
// �C���N���[�h
//=============================
#include "game.h"
#include "bg.h"
#include "number.h"
#include "score.h" 
#include "mouse.h"
#include "camera.h"
#include "fade.h"
#include "keyboard.h"
#include "particle.h"
#include "time.h"
#include "player.h"
#include "enemy.h"

//=============================
// �}�N����`
//=============================
#define ENEMY_FIRST_INTER		(150)
#define ENEMY_SECOND_INTER		(100)
#define ENEMY_THIRD_INTER		(80)
#define ENEMY_FOURS_INTER		(60)
#define ENEMY_FIVE_INTER		(45)
#define ENEMY_SIX_INTER			(30)
#define ENEMY_SEVEN_INTER		(20)
#define ENEMY_EIGHT_INTER		(15)

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CCamera *CGame::m_pCamera = NULL;   // �J����
CPlayer *CGame::m_pPlayer = NULL;	// �v���C���[

//=============================
// �R���X�g���N�^
//=============================
CGame::CGame()
{
	m_nEnemyFlame = 0;			// �G�̏o��t���[��
	m_nGameFlame = 0;			// �Q�[���̃J�E���^�[
	m_bSpeedUp = false;
}

//=============================
// �f�X�g���N�^
//=============================
CGame::~CGame()
{
}

//=============================
// �N���G�C�g
//=============================
CGame * CGame::Create(void)
{
	// �������̊m��
	CGame *pGame = new CGame;
	// ������
	pGame->Init();

	return pGame;
}

//=============================
// ����������
//=============================
HRESULT CGame::Init(void)
{
	// �v���C���[�̏���������
	if (m_pPlayer == NULL)
	{
		// �C���X�^���X����
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0.0f), 
			D3DXVECTOR3(PLAYER_SIZE_X, PLAYER_SIZE_Y, 0.0f));
	}

	m_nEnemyFlame = ENEMY_FIRST_INTER;			// �G�̏o��t���[��

	// �|�[�Y�̏�����
	CManager::SetActivePause(false);
	return S_OK;
}

//=============================
// �I������
//=============================
void CGame::Uninit(void)
{
	// �v���C���[���g���Ă�����
	if (m_pPlayer != NULL)
	{
		m_pPlayer = NULL;	// �v���C���[
	}

	// �J������
	Release();
}

//=============================
// �X�V����
//=============================
void CGame::Update(void)
{
	if (CManager::GetKeyboard()->GetKeyTrigger(DIK_RETURN))
	{
		CManager::GetFade()->SetFade(CManager::MODE_RESULT);
	}

	// �Q�[���̐ݒ�
	SetGame();
}

//=============================
// �`�揈��
//=============================
void CGame::Draw(void)
{
}

//=============================================================================
// �Q�[���̐ݒ�
//=============================================================================
void CGame::SetGame(void)
{
	m_nGameFlame++;			// �Q�[���̃J�E���^�[

	// �G�l�~�[�̏o���Ԋu
	if (m_nGameFlame % m_nEnemyFlame == 0)
	{
		int nNum = rand() % 4;
		float fPosX = 0.0f, fPosY = 0.0f;
		switch (nNum)
		{
		case 0:
			fPosX = -ENEMY_SIZE_X;
			fPosY = (float)(rand() % SCREEN_HEIGHT);
			break;
		case 1:
			fPosX = (float)(rand() % SCREEN_WIDTH);
			fPosY = -ENEMY_SIZE_Y ;
			break;
		case 2:
			fPosX = SCREEN_WIDTH + ENEMY_SIZE_X;
			fPosY = (float)(rand() % SCREEN_HEIGHT);
			break;
		case 3:
			fPosX = (float)(rand() % SCREEN_WIDTH);
			fPosY = SCREEN_HEIGHT + ENEMY_SIZE_Y;
			break;
		default:
			break;
		}

		D3DXVECTOR3 pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);

		// �G�l�~�[�̏o��
		CEnemy::Create(pos, D3DXVECTOR3(ENEMY_SIZE_X / 2, ENEMY_SIZE_Y/2, 0.0f));
	}

	// ��i�K��
	if (m_nGameFlame == 600)	// 10�b
	{
		m_nEnemyFlame = ENEMY_SECOND_INTER;
	}
	if (m_nGameFlame == 1200)	// 20�b
	{
		m_nEnemyFlame = ENEMY_THIRD_INTER;
	}
	if (m_nGameFlame == 2100)	// 35�b
	{
		m_nEnemyFlame = ENEMY_FOURS_INTER;
	}
	if (m_nGameFlame == 3000)	// 50�b
	{
		m_nEnemyFlame = ENEMY_FIVE_INTER;
		m_bSpeedUp = true;
	}
	if (m_nGameFlame == 3900)	// 65�b
	{
		m_nEnemyFlame = ENEMY_SIX_INTER;
	}
	if (m_nGameFlame == 4800)	// 80�b
	{
		m_nEnemyFlame = ENEMY_SEVEN_INTER;
	}
	if (m_nGameFlame == 5700)	// 95�b
	{
		m_nEnemyFlame = ENEMY_SEVEN_INTER;
	}


}