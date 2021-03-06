//===================================================
//
//    ナンバークラスの処理[number.cpp]
//    Author:増澤 未来
//
//====================================================

//**********************************
// インクルード
//**********************************
#include "number.h"
#include "manager.h"
#include "renderer.h"

//**********************************
// マクロ定義
//**********************************
#define NUMBER_TEXTURE_PATH "./data/Textures/number_H2.png" // テクスチャのパス

//**********************************
// 静的メンバ変数宣言
//**********************************
LPDIRECT3DTEXTURE9 CNumber::m_pTexture = NULL;

//==================================
// コンストラクタ
//==================================
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_nNumber = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//==================================
// デストラクタ
//==================================
CNumber::~CNumber()
{
}

//==================================
// クリエイト
//==================================
CNumber * CNumber::Create(const int nNum, const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col)
{
	// メモリの確保
	CNumber * pNumber = new CNumber;
	
	// 初期化処理
	pNumber->Init(pos, size, col);
	pNumber->SetNumber(nNum);

	return pNumber;
}

//==================================
// ロード
//==================================
HRESULT CNumber::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// テクスチャの生成
	D3DXCreateTextureFromFile(pDevice, NUMBER_TEXTURE_PATH, &m_pTexture);

	return S_OK;
}

//==================================
// アンロード
//==================================
void CNumber::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==================================
// 初期化処理
//==================================
HRESULT CNumber::Init(const D3DXVECTOR3 pos, const D3DXVECTOR3 size, const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D)*NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_pVtxBuff, NULL);

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0);
	pVtx[1].pos = D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0);
	pVtx[2].pos = D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0);
	pVtx[3].pos = D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0);

	// テクスチャUV座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * m_nNumber)        , 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * m_nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * m_nNumber)        , 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * m_nNumber), 1.0f);

	m_col = col;
	for (int nCnt = 0; nCnt < NUM_VERTEX; nCnt++)
	{
		pVtx[nCnt].col = m_col;
		pVtx[nCnt].rhw = 1.0f;
	}
	// アンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}

//==================================
// 終了処理
//==================================
void CNumber::Uninit(void)
{
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//==================================
// 更新処理
//==================================
void CNumber::Update(void)
{
}

//==================================
// 描画処理
//==================================
void CNumber::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	if (m_pTexture != NULL)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, m_pTexture);
	}

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetTexture(0, 0);
}

//==================================
// 数字のセット
//==================================
void CNumber::SetNumber(const int nNumber)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	m_nNumber = nNumber;

	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャUV座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * m_nNumber), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (0.1f * m_nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (0.1f * m_nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * m_nNumber), 1.0f);

	m_pVtxBuff->Unlock();
}


void CNumber::SetColor(const D3DXCOLOR col)
{
	VERTEX_2D *pVtx;// 頂点情報ポインタ

	m_col = col;

	// ロック
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラーの設定
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	// アンロック
	m_pVtxBuff->Unlock();
}
