////////////////////////////////////////////////////
//
//    scene3d�N���X�̏���[scene3d.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////

//******************************
// �C���N���[�h
//******************************
#include "scene3d.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
#include "keyboard.h"
#include "joypad.h"

//******************************
// �}�N����`
//******************************
#define POLYGON_SIZE 200 // �|���S���̏����T�C�Y

//===================================
// �R���X�g���N�^
//===================================
CScene3d::CScene3d(int nPriority) :CScene(OBJTYPE_NONE)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);

	m_col = { 1.0f,1.0f,1.0f,1.0f };
	m_size = { 0.0f,0.0f,0.0f };
	m_fAngle = 0.0f;
	m_mtxWorld = {};
	m_pldxBuff = NULL;
	m_bAddMode = false;
}

//===================================
// �f�X�g���N�^
//===================================
CScene3d::~CScene3d()
{
}

//===================================
// �N���G�C�g�֐�
//===================================
CScene3d * CScene3d::Create(void)
{
	// �������̊m��
	CScene3d *pScene3d;
	pScene3d = new CScene3d;
	// ������
	pScene3d->Init();

	return pScene3d;
}

//===================================
// ����������
//===================================
HRESULT CScene3d::Init(void)
{
	VERTEX_3D *pVtx;// ���_���|�C���^

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	// �����o�ϐ��̏�����
	m_size = { POLYGON_SIZE,POLYGON_SIZE,0.0f };
	m_col = { 1.0f,1.0f,1.0f,1.0f };

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���S���璸�_�̋���
	float fDistance = sqrtf(powf(m_size.x, 2) + powf(m_size.y, 2));
	// ���S����E��̒��_�̊p�x
	float fAngle = atan2f(m_size.y, m_size.x);
	// ���S���獶��̒��_�̊p�x
	float  fAngle2 = atan2f(m_size.y, -m_size.x);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(fAngle + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle + D3DXToRadian(m_fAngle))  * fDistance), m_pos.y + (sinf(-fAngle + D3DXToRadian(m_fAngle))  * fDistance), 0);

	// �e�N�X�`��UV���W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		// �F�̐ݒ�
		pVtx[nCnt].col = m_col;
		// �@��
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
	}

	// �A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//===================================
// �I������
//===================================
void CScene3d::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	Release();
}

//===================================
// �X�V����
//===================================
void CScene3d::Update(void)
{
}

//===================================
// �`�揈��
//===================================
void CScene3d::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans,mtxScail;//�s��v�Z�p�}�g���N�X

	// ���Z���[�h�̎�
	if (m_bAddMode)
	{
		// ���Z����
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

	// �}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	D3DXMatrixIdentity(&mtxRot);
	D3DXMatrixIdentity(&mtxTrans);
	D3DXMatrixIdentity(&mtxScail);

	// �T�C�Y
	D3DXMatrixScaling(&mtxScail, 1.0f, 1.0f, 1.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxScail);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	pDevice->SetTexture(0, m_pTexture);

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	pDevice->SetTexture(0, 0);

	// ���Z���[�h�̎�
	if (m_bAddMode)
	{
		// �ʏ퍇���ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}
}

//===================================
// ���W�̃Z�b�g
//===================================
void CScene3d::SetPos(const D3DXVECTOR3 pos)
{
	VERTEX_3D *pVtx;// ���_���|�C���^

					//pos�̑��
	m_pos = pos;

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���S���璸�_�̋���
	float fDistance = sqrtf(powf(m_size.x, 2) + powf(m_size.y, 2));
	// ���S����E��̒��_�̊p�x
	float fAngle = atan2f(m_size.y, m_size.x);
	// ���S���獶��̒��_�̊p�x
	float  fAngle2 = atan2f(m_size.y, -m_size.x);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (cosf(fAngle + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(fAngle + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), m_pos.y + (sinf(-fAngle2 + D3DXToRadian(m_fAngle)) * fDistance), 0);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (cosf(-fAngle + D3DXToRadian(m_fAngle))  * fDistance), m_pos.y + (sinf(-fAngle + D3DXToRadian(m_fAngle))  * fDistance), 0);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

//===================================
// �p�x�̃Z�b�g
//===================================
void CScene3d::SetAngle(const float fAngle)
{
	m_fAngle = fAngle; 
	SetPos(m_pos);
}

//===================================
// �A�j���[�V�������̃Z�b�g
//===================================
void CScene3d::SetTextureUV(const D3DXVECTOR2 uv[NUM_VERTEX])
{
	VERTEX_3D *pVtx;// ���_���|�C���^

					// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].tex = uv[0];
	pVtx[1].tex = uv[1];
	pVtx[2].tex = uv[2];
	pVtx[3].tex = uv[3];

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

//===================================
// �T�C�Y�̃Z�b�g
//===================================
void CScene3d::SetSize(const D3DXVECTOR3 size)
{
	m_size = size;

	// ���_���W�̍Đݒ�
	SetPos(m_pos);
}

//===================================
// �F�̃Z�b�g
//===================================
void CScene3d::SetColor(const D3DXCOLOR col)
{
	VERTEX_3D *pVtx;// ���_���|�C���^

	m_col = col;

	// ���b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// �A�����b�N
	m_pVtxBuff->Unlock();
}