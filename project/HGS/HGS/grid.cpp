////////////////////////////////////////////////////
//
//    playerの処理[player.cpp]
//    Author:増澤 未来
//
////////////////////////////////////////////////////


//=============================
// インクルード
//=============================
#include "grid.h"
#include "manager.h"
#include "renderer.h"
#include "scene2d.h"

//**********************************
// マクロ定義
//**********************************
#define TEXTURE_PATH "./data/Textures/grid.png" // テクスチャ
#define GRID_SIZE D3DXVECTOR3(16.0f*4.0f,9.0f*4.0f,0.0f) // グリッドのサイズ
#define SHAKE_COUNT 5

//**********************************
// 静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CGrid::m_pTexture = NULL;                     // テクスチャ
CGrid *CGrid::m_apGrid[GRID_NUM_Y][GRID_NUM_X] = {};             // グリッド
D3DXVECTOR3 CGrid::m_shake = D3DXVECTOR3(0.0f,0.0f,0.0f);        // ブレ
D3DXVECTOR3 CGrid::m_shakeDist = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  // ブレ目標値
bool CGrid::m_bShake = false;                                    // ブレフラグ
int CGrid::m_nCntShake = 0;                                      // ブレカウント

//=============================
// コンストラクタ
//=============================
CGrid::CGrid() : CScene(OBJTYPE_MAP)
{
	m_pScene2d = NULL;        // ポリゴン
	m_gridNum = D3DXVECTOR2(0.0f, 0.0f); // グリッド番号
}

//=============================
// デストラクタ
//=============================
CGrid::~CGrid()
{
}

//=============================
// クリエイト
//=============================
void CGrid::CreateAll(void)
{
	float fPosY = CENTER_POS.y - (((GRID_SIZE.y*2)*GRID_NUM_Y) / 2) + GRID_SIZE.y;// X軸位置
	float fPosX = CENTER_POS.x - (((GRID_SIZE.x*2)*GRID_NUM_X) / 2) + GRID_SIZE.x;// Y軸位置
	
	// 横方向ループ
	for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
	{
		// 縦方向ループ
		for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
		{
			// メモリの確保
			//CGrid*pGrid = NULL;
			m_apGrid[nCntY][nCntX] = new CGrid;

			// NULLチェック
			if (m_apGrid[nCntY][nCntX] != NULL)
			{
				
				// 初期化
				m_apGrid[nCntY][nCntX]->Init();
				// 位置の設定
				m_apGrid[nCntY][nCntX]->m_pScene2d->SetPos(D3DXVECTOR3(fPosX, fPosY, 0.0f));
				m_apGrid[nCntY][nCntX]->m_pScene2d->SetSize(GRID_SIZE);
				// テクスチャの設定
				m_apGrid[nCntY][nCntX]->m_pScene2d->BindTexture(m_pTexture);
				// グリッド番号の設定
				m_apGrid[nCntY][nCntX]->m_gridNum.y = nCntY;
				m_apGrid[nCntY][nCntX]->m_gridNum.x = nCntX;
			}
			else
			{
				return;
			}
			// Y軸をずらす
			fPosX += GRID_SIZE.x*2;
		}
		// Y軸位置の初期化
		fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;
		// X軸をずらす
		fPosY += GRID_SIZE.y*2;
	}
}

//=======================================================================================
// テクスチャのロード
//=======================================================================================
HRESULT CGrid::Load(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//=======================================================================================
// テクスチャのアンロード
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
// 破壊
//=======================================================================================
void CGrid::Break(D3DXVECTOR3 pos)
{
	// 横方向ループ
	for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
	{
		// 縦方向ループ
		for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
		{
			// NULLチェック
			if (m_apGrid[nCntY][nCntX] != NULL)
			{
				// グリッドの座標の取得
				D3DXVECTOR3 gridPos = m_apGrid[nCntY][nCntX]->m_pScene2d->GetPos();
				// グリッドのサイズの取得
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
// 揺らす
//=======================================================================================
void CGrid::Shake(bool bRand)
{
	if (bRand)
	{// 引数がtrueだったとき
		//if (!m_bShake)
		{
			// どれくらいぶれるか乱数で決める
			m_shakeDist.x = -0.6f;
			m_shakeDist.y = 0.6f;
			m_shakeDist.z = 0.0f;
			m_bShake = true;
			m_nCntShake = 0;

			float fPosY = CENTER_POS.y - (((GRID_SIZE.y * 2)*GRID_NUM_Y) / 2) + GRID_SIZE.y;// X軸位置
			float fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;// Y軸位置

																							// 横方向ループ
			for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
			{
				// 縦方向ループ
				for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
				{
					// NULLチェック
					if (m_apGrid[nCntY][nCntX] != NULL)
					{
						// 位置の設定
						m_apGrid[nCntY][nCntX]->m_pScene2d->SetPos(D3DXVECTOR3(fPosX, fPosY, 0.0f));

					}
					// Y軸をずらす
					fPosX += GRID_SIZE.x * 2;
				}
				// Y軸位置の初期化
				fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;
				// X軸をずらす
				fPosY += GRID_SIZE.y * 2;
			}
		}
	}
	else
	{
		// プレイヤーが障害物にぶつかったときにカメラをぶらす
		if (m_bShake)
		{
			// カウントを進める
			m_nCntShake++;
			// 一定のカウントで
			if (m_nCntShake % SHAKE_COUNT == 0)
			{// 反対方向にぶらしつつちょっとずつぶれをちいさくする
				m_shakeDist *= -0.9f;
			}
			if (m_nCntShake > SHAKE_COUNT * 5)
			{
				m_bShake = false;

				float fPosY = CENTER_POS.y - (((GRID_SIZE.y * 2)*GRID_NUM_Y) / 2) + GRID_SIZE.y;// X軸位置
				float fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;// Y軸位置

				// 横方向ループ
				for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
				{
					// 縦方向ループ
					for (int nCntX = 0; nCntX < GRID_NUM_X; nCntX++)
					{
						// NULLチェック
						if (m_apGrid[nCntY][nCntX] != NULL)
						{
							// 位置の設定
							m_apGrid[nCntY][nCntX]->m_pScene2d->SetPos(D3DXVECTOR3(fPosX, fPosY, 0.0f));

						}
						// Y軸をずらす
						fPosX += GRID_SIZE.x * 2;
					}
					// Y軸位置の初期化
					fPosX = CENTER_POS.x - (((GRID_SIZE.x * 2)*GRID_NUM_X) / 2) + GRID_SIZE.x;
					// X軸をずらす
					fPosY += GRID_SIZE.y * 2;
				}
			}

			// 横方向ループ
			for (int nCntY = 0; nCntY < GRID_NUM_Y; nCntY++)
			{
				// 縦方向ループ
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
// 初期化処理
//=============================
HRESULT CGrid::Init(void)
{
	if (m_pScene2d == NULL)
	{
		// ポリゴンの生成
		m_pScene2d = CScene2d::Create();
		// オブジェクトタイプの設定
		m_pScene2d->SetPriority(OBJTYPE_MAP);
	}
	
	// 変数の初期化

	return S_OK;
}

//=============================
// 終了処理
//=============================
void CGrid::Uninit(void)
{
	// NULLチェック
	if (m_pScene2d != NULL)
	{
		// 終了処理
		m_pScene2d->Uninit();
	}

	// リリース
	Release();
}


//=============================
// 更新処理
//=============================
void CGrid::Update(void)
{
	
}


//=============================
// 描画処理
//=============================
void CGrid::Draw(void)
{
	if (m_pScene2d != NULL)
	{
		m_pScene2d->Draw();
	}
}

