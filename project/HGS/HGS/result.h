//=============================================================================
//
// resultヘッダ [result.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _RESULT_H_
#define _RESULT_H_

//*****************************
//インクルード
//*****************************
#include "main.h"
#include "scene.h"

//=============================
// 前方宣言
//=============================
class CPolygon;
class CRanking;

//*****************************
//クラス定義
//*****************************

//リザルトクラス
class CResult : public CScene
{
public:
	//============
	// メンバ関数
	//============
	CResult();
	~CResult();

	static CResult *Create(void); //クラス生成

	HRESULT Init(void); // 初期化
	void Uninit(void);  // 終了
	void Update(void);  // 更新
	void Draw(void);    // 描画

private:
	//============
	// メンバ変数
	//============
	static LPDIRECT3DTEXTURE9 m_pTexture; // テクスチャへのポインタ
	CPolygon *m_pPolygon;                 // ポリゴン
	static CRanking *m_pRanking;					// ランキング

};

#endif