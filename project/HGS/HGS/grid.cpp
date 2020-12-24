////////////////////////////////////////////////////
//
//    player�̏���[player.cpp]
//    Author:���V ����
//
////////////////////////////////////////////////////


//=============================
// �C���N���[�h
//=============================
#include "grid.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//**********************************
// �}�N����`
//**********************************
#define TEXTURE_PATH "./data/Textures/grid.png" // �e�N�X�`��
#define GRID_SIZE D3DXVECTOR3(16.0f*4.0f,9.0f*4.0f,0.0f) // �O���b�h�̃T�C�Y
#define SHAKE_COUNT 5

//**********************************
// �ÓI�����o�ϐ��錾
//**********************************
LPDIRECT3DTEXTURE9 CGrid::m_pTexture = NULL;                     // �e�N�X�`��
CGrid *CGrid::m_apGrid[GRID_NUM_Y][GRID_NUM_X] = {};             // �O���b�h
D3DXVECTOR3 CGrid::m_shake = D3DXVECTOR3(0.0f,0.0f,0.0f);        // �u��
D3DXVECTOR3 CGrid::m_shakeDist = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // �u���ڕW�l
bool CGrid::m_bShake = false;                                    // �u���t���O
int CGrid::m_nCntShake = 0;                                      // �u���J�E���g

//=============================
// �R���X�g���N�^
//=============================
CGrid::CGrid() : CScene(OBJTYPE_MAP)
{
	m_pScene2d = NULL;        // �|���S��
	m_gridNum = D3DXVECTOR2(0.0f, 0.0f); // �O���b�h�ԍ�
}

//=============================
// �f�X�g���N�^
//=============================
CGrid::~CGrid()
{
}

//=============================
// �N���G�C�g
//=============================
void CGrid::CreateAll(void)
{
	float fPosY = CENTER_POS.y - (((GRID_SIZE.y*2)*GRID_NUM_Y) / 2) + GRID_SIZE.y;// X���ʒu
	float fPosX = CENTER_POS.x - (((GRID_SIZE.x*2)*GRID_NUM_X) / 2) + GRID_SIZE.x;// Y���ʒu
	
	// ���������[�v
	for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
	{
		// �c�������[�v
		for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
		{
			// �������̊m��
			//CGrid*pGrid = NULL;
			m_apGrid[nCntY][nCntX] = new CGrid;

			// NULL�`�F�b�N
			if (m_apGrid[nCntY][nCntX] != NULL)
			{
				
				// ������
				m_apGrid[nCntY][nCntX]->Init();
				// �ʒu�̐ݒ�
				m_apGrid[nCntY][nCntX]->m_pScene2d->SetPos(D3DXVECTOR3(fPosX, fPosY, 0.0f));
				m_apGrid[nCntY][nCntX]->m_pScene2d->SetSize(GRID_SIZE);
				// �e�N�X�`���̐ݒ�
				m_apGrid[nCntY][nCntX]->m_pScene2d->BindTexture(m_pTexture);
				// �O���b�h�ԍ��̐ݒ�
				m_apGrid[nCntY][nCntX]->m_gridNum.y = nCntY;
				m_apGrid[nCntY][nCntX]->m_gridNum.x = nCntX;
			}
			else
			{
				return;
			}
			// Y�������炷
			fPosX += GRID_SIZE.x*2;
		}
		// Y���ʒu�̏�����
		fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;
		// X�������炷
		fPosY += GRID_SIZE.y*2;
	}
}

//=======================================================================================
// �e�N�X�`���̃��[�h
//=======================================================================================
HRESULT CGrid::Load(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//=======================================================================================
// �e�N�X�`���̃A�����[�h
//=======================================================================================
void CGrid::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//=======================================================================================
// �j��
//=======================================================================================
void CGrid::Break(D3DXVECTOR3 pos)
{
	// ���������[�v
	for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
	{
		// �c�������[�v
		for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
		{
			// NULL�`�F�b�N
			if (m_apGrid[nCntY][nCntX] != NULL)
			{
				// �O���b�h�̍��W�̎擾
				D3DXVECTOR3 gridPos = m_apGrid[nCntY][nCntX]->m_pScene2d->GetPos();
				// �O���b�h�̃T�C�Y�̎擾
				D3DXVECTOR3 gridSize = m_apGrid[nCntY][nCntX]->m_pScene2d->GetSize();
				if (pos.x > gridPos.x - gridSize.x && pos.x < gridPos.x + gridSize.x  &&
					pos.y > gridPos.y - gridSize.y && pos.y < gridPos.y + gridSize.y)
				{
					m_apGrid[nCntY][nCntX]->m_pScene2d->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
					Shake(true);
					break;
				}
			}
		}
	}
}

//=======================================================================================
// �h�炷
//=======================================================================================
void CGrid::Shake(bool bRand)
{
	if (bRand)
	{// ������true�������Ƃ�
		//if (!m_bShake)
		{
			// �ǂꂭ�炢�Ԃ�邩�����Ō��߂�
			m_shakeDist.x = -0.6f;
			m_shakeDist.y = 0.6f;
			m_shakeDist.z = 0.0f;
			m_bShake = true;
			m_nCntShake = 0;

			float fPosY = CENTER_POS.y - (((GRID_SIZE.y * 2)*GRID_NUM_Y) / 2) + GRID_SIZE.y;// X���ʒu
			float fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;// Y���ʒu

																							// ���������[�v
			for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
			{
				// �c�������[�v
				for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
				{
					// NULL�`�F�b�N
					if (m_apGrid[nCntY][nCntX] != NULL)
					{
						// �ʒu�̐ݒ�
						m_apGrid[nCntY][nCntX]->m_pScene2d->SetPos(D3DXVECTOR3(fPosX, fPosY, 0.0f));

					}
					// Y�������炷
					fPosX += GRID_SIZE.x * 2;
				}
				// Y���ʒu�̏�����
				fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;
				// X�������炷
				fPosY += GRID_SIZE.y * 2;
			}
		}
	}
	else
	{
		// �v���C���[����Q���ɂԂ������Ƃ��ɃJ�������Ԃ炷
		if (m_bShake)
		{
			// �J�E���g��i�߂�
			m_nCntShake++;
			// ���̃J�E���g��
			if (m_nCntShake % SHAKE_COUNT == 0)
			{// ���Ε����ɂԂ炵������Ƃ��Ԃ��������������
				m_shakeDist *= -0.9f;
			}
			if (m_nCntShake > SHAKE_COUNT * 5)
			{
				m_bShake = false;

				float fPosY = CENTER_POS.y - (((GRID_SIZE.y * 2)*GRID_NUM_Y) / 2) + GRID_SIZE.y;// X���ʒu
				float fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;// Y���ʒu

				// ���������[�v
				for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
				{
					// �c�������[�v
					for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
					{
						// NULL�`�F�b�N
						if (m_apGrid[nCntY][nCntX] != NULL)
						{
							// �ʒu�̐ݒ�
							m_apGrid[nCntY][nCntX]->m_pScene2d->SetPos(D3DXVECTOR3(fPosX, fPosY, 0.0f));

						}
						// Y�������炷
						fPosX += GRID_SIZE.x * 2;
					}
					// Y���ʒu�̏�����
					fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;
					// X�������炷
					fPosY += GRID_SIZE.y * 2;
				}
			}

			// ���������[�v
			for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
			{
				// �c�������[�v
				for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
				{
					m_apGrid[nCntY][nCntX]->m_pScene2d->SetPos( m_apGrid[nCntY][nCntX]->m_pScene2d->GetPos()+ m_shakeDist);
				}
			}
		}
		else
		{
			m_nCntShake = 0;
			m_shakeDist = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		}

		m_shake += (m_shakeDist - m_shake)*0.05f;

	}

	
}

//=============================
// ����������
//=============================
HRESULT CGrid::Init(void)
{
	if (m_pScene2d == NULL)
	{
		// �|���S���̐���
		m_pScene2d = CScene2d::Create();
		// �I�u�W�F�N�g�^�C�v�̐ݒ�
		m_pScene2d->SetPriority(OBJTYPE_MAP);
	}
	
	// �ϐ��̏�����

	return S_OK;
}

//=============================
// �I������
//=============================
void CGrid::Uninit(void)
{
	// NULL�`�F�b�N
	if (m_pScene2d != NULL)
	{
		// �I������
		m_pScene2d->Uninit();
	}

	// �����[�X
	Release();
}


//=============================
// �X�V����
//=============================
void CGrid::Update(void)
{
	
}


//=============================
// �`�揈��
//=============================
void CGrid::Draw(void)
{
	if (m_pScene2d != NULL)
	{
		m_pScene2d->Draw();
	}
}

