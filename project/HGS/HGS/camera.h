//=============================================================================
//
// cameraヘッダ [camera.h]
// Author : 増澤 未来
//
//=============================================================================

//二重インクルード防止
#ifndef _CAMERA_H_
#define _CAMERA_H_

//*****************************
// インクルード
//*****************************
#include "main.h"
#include "scene2d.h"

//*****************************
// クラス定義
//*****************************

//カメラクラス
class CCamera
{
public:
	//============
	// メンバ関数
	//============
	CCamera();
	~CCamera();

	// static
	static CCamera *Create();  // クラス生成
	static void Release(void); // リリース

	HRESULT Init(void);   // 初期化
	void Uninit(void);	  // 終了
	void Update(void);	  // 更新
	void SetCamera(void); // カメラのセット

	// 取得
	D3DXVECTOR3 GetPos(void) { return m_posV; }                                     // 座標の取得
	D3DXMATRIX GetViewMtx(void) { return m_mtxView; }                                  // ビューマトリックスの取得
	D3DXMATRIX GetProjectionMtx(void) { return m_mtxProjection; }                            // プロジェクションマトリックスの取得

private:
	//============
	// メンバ変数
	//============
	static CCamera *m_pCamera;   // 自分のポインタ

	D3DXVECTOR3 m_posV;          // カメラの座標
	D3DXVECTOR3 m_posR;          // 注視点
	D3DXVECTOR3 m_vecU;          // 上方向ベクトル
	D3DXMATRIX  m_mtxProjection; // プロジェクションマトリックス
	D3DXMATRIX  m_mtxView;       // ビューマトリックス
};

#endif