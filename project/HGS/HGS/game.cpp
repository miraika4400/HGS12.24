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

//=============================
// �ÓI�����o�ϐ��錾
//=============================
CCamera *CGame::m_pCamera = NULL;   // �J����


//=============================
// �R���X�g���N�^
//=============================
CGame::CGame()
{
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

	// �|�[�Y�̏�����
	CManager::SetActivePause(false);
	return S_OK;
}

//=============================
// �I������
//=============================
void CGame::Uninit(void)
{

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
}


//=============================
// �`�揈��
//=============================
void CGame::Draw(void)
{
}