//=============================================================================
//
//  [titlemenu.h]
// Author : Masuzawa Mirai
//
//=============================================================================

// ��d�C���N���[�h�h�~
#ifndef _PAUSE_H_
#define _PAUSE_H_

//***************************************************************************************
// �C���N���[�h�t�@�C��
//***************************************************************************************
#include "scene.h"

//***************************************************************************************
// �O���錾
//***************************************************************************************
class CPolygon;

//***************************************************************************************
// �N���X��`
//***************************************************************************************

// �|�[�Y�N���X
class CPause
{
public:

	//============
	// ��ԗ�
	//============
	// �|�[�Y�p�[�c��
	typedef enum
	{
		BACK = 0,
		RESUME,
		RESTART,
		EXIT,
		PARTS_MAX
	}MENU_PARTS;

	//============
	// �����o�֐�
	//============
	CPause();
	~CPause();

	// staic
	static CPause* Create(void); // �N���X����
	static HRESULT Load(void);   // �e�N�X�`�����[�h
	static void Unload(void);    // �e�N�X�`���A�����[�h

	HRESULT Init(void); // ������
	void Uninit(void);  // �I��
	void Update(void);  // �X�V
	void Draw(void);    // �`��

private:
	//============
	// �����o�ϐ�
	//============
	static LPDIRECT3DTEXTURE9 m_apTexture[PARTS_MAX]; // �e�N�X�`��
	CPolygon* m_pPolygon[PARTS_MAX];                  // �|���S��
	int m_nMenu;                                      // ���j���[�I��p
	bool m_bMove;                                     // �ړ��t���O
};

#endif // !_TITEL_H_