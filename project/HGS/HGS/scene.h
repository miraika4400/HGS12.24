//=============================================================================
//
// scene�w�b�_ [scene.h]
// Author : ���V ����
//
//=============================================================================

//��d�C���N���[�h�h�~
#ifndef _SCENE_H_
#define _SCENE_H_

//�C���N���[�h
#include "main.h"

//***********************************
//�}�N����`
//***********************************
#define MAX_SCENE 1280   // �|���S���̍ő吔
#define PRIORITY_NUM OBJTYPE_MAX
//=============================
//�N���X��`
//=============================

//�V�[���N���X
class CScene
{
public:
	//============
	// ��ԗ�
	//============
	// �I�u�W�F�N�g�^�C�v��
	// �`�揇
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_BG,         // �w�i
		OBJTYPE_MAP,        // �X�e�[�W
		OBJTYPE_ENEMY,		// �G�l�~�[
		OBJTYPE_PLAYER,     // �v���C���[
		OBJTYPE_BULLET,		// �o���b�g
		OBJTYPE_MOTION,     // ���[�V����
		OBJTYPE_PARTICLE,   // �p�[�e�B�N��
		OBJTYPE_UI,         // UI
		OBJTYPE_MAX,        // �^�C�v�̍ő吔
	}OBJTYPE;

	//============
	// �����o�֐�
	//============
	CScene(int nPriority = OBJTYPE_NONE);
	virtual ~CScene();
	static void ReleaseAll(void);                   // ���ׂĉ��
	static void UpdateAll(void);                    // ���ׂčX�V
	static void DrawAll(void);                      // ���ׂĕ`��
	static int GetNumAll(void) { return m_nIDAll; } // ����܂Ő������ꂽ�I�u�W�F�N�g�̐�
	 
	void SetPriority(const int  nPriority);   // �v���C�I���e�B�̐ݒ�
	OBJTYPE GetType(void) { return m_type; }  // �I�u�W�F�N�g�^�C�v�̎擾
	int GetID(void) { return m_nNumID; }      // �z��ԍ��̎擾

	CScene *GetNext(void);
	static CScene *GetTop(int nNum);

	// �������z�֐�
	virtual HRESULT Init(void) = 0; // ������
	virtual void Uninit(void) = 0;  // �I��
	virtual void Update(void) = 0;  // �X�V
	virtual void Draw(void) = 0;    // �`��

protected:
	void Release(void);      // �������
private:
	void ReConnection(void); // ���X�g�\�����玩�g�������ĂȂ��Ȃ���

	//============
	// �����o�ϐ�
	//============
	static int m_nIDAll;                   // ���������|���S����
	int     m_nNumID;                      // ���������|���S���̔z��
	OBJTYPE m_type;                        // �I�u�W�F�N�g�^�C�v
	int     m_nPriority;                   // �v���C�I���e�B
	bool    m_bReleasFlag;                 // �폜�t���O

	// ���X�g�\��
	static CScene * m_pTop[PRIORITY_NUM];  // �擪
	static CScene * m_pCur[PRIORITY_NUM];  // �Ō�
	CScene * m_pNext;                      // �� 
	CScene * m_pPrev;                      // �O
};

#endif