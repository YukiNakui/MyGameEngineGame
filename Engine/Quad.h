#pragma once
#include "Direct3D.h"
#include <DirectXMath.h>
#include"Texture.h"
#include"Transform.h"
#include<vector>

using namespace DirectX;

//コンスタントバッファー:アプリ側からシェーダーに毎フレーム渡したい情報
struct CONSTANT_BUFFER
{
	XMMATRIX	matWVP;
	XMMATRIX	matW;
};

//頂点情報
struct VERTEX
{
	XMVECTOR position;
	XMVECTOR uv;
	XMVECTOR normal;//ノーマル追加（法線ベクトル）
};

class Quad
{
protected:
	int vertexNum_;
	std::vector<VERTEX> vertices_;
	int indexNum_;//インデックス数
	std::vector<int> index_;//インデックス情報

	ID3D11Buffer* pVertexBuffer_;	//頂点バッファ
	ID3D11Buffer* pIndexBuffer_;    //インデックスバッファ
	ID3D11Buffer* pConstantBuffer_;	//コンスタントバッファ
	
	Texture* pTexture_;//テクスチャへのポインタ
public:
	Quad();
	virtual ~Quad();
	HRESULT Initialize();//初期化用（コンストラクタでできない奴はこっちで初期化）
	//void Draw();//描画関数
	void Draw(Transform& transform);//描画関数
	void Release();//解放処理

private:
	virtual void InitVertexData();
	HRESULT CreateVertexBuffer();
	virtual void InitIndexData();
	HRESULT CreateIndexBuffer();
	HRESULT CreateConstantBuffer();
	HRESULT LoadTexture();

	//-------Draw関数から呼ばれる関数--------
	void PassDataToCB(Transform& transform);   //コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();                          //各バッファをパイプラインにセット
};