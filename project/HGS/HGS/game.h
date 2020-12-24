//=============================================================================
//
// game�w�b�_ [game.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _GAME_H_
#define _GAME_H_

//*****************************
//�C���N���[�h
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// �O���錾
//=============================
class CRenderer;
class CInputKeyboard;
class CInputJoypad;
class CInputMouse;
class CSound;
class CCamera;


//*****************************
//�N���X��`
//*****************************

//2d�|���S���N���X
class CGame : public CScene
{
public:
	//*****************************
	// �񋓒�`
	//*****************************


	//*****************************
	// �����o�֐�
	//*****************************
	CGame();
	~CGame();

	static CGame *Create(void); // �N���X����

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

	static CCamera *GetCamera(void) { return m_pCamera; } // �J�����̎擾����
	
private:
	//*****************************
	// �����o�ϐ�
	//*****************************
	static CCamera*m_pCamera; // �J����

};

#endif