#pragma once
#include "Direct3D.h"
#include<fbxsdk.h>
#include <DirectXMath.h>
#include"Texture.h"
#include"Transform.h"
#include<vector>
#include<filesystem>

#pragma comment(lib, "LibFbxSDK-MD.lib")
#pragma comment(lib, "LibXml2-MD.lib")
#pragma comment(lib, "zlib-MD.lib")

class FBX
{

	//マテリアル
	struct MATERIAL
	{
		Texture* pTexture;
		XMFLOAT4 diffuse;
	};

	//コンスタントバッファー:アプリ側からシェーダーに毎フレーム渡したい情報
	struct CONSTANT_BUFFER
	{
		XMMATRIX	matWVP;  //ワールドビュープロジェクション
		XMMATRIX	matNormal;    //法線ベクトルの変換用
		XMFLOAT4	diffuseColor;
		int isTextured;
	};

	//頂点情報
	struct VERTEX
	{
		XMVECTOR position;
		XMVECTOR uv;
		XMVECTOR normal;//ノーマル追加（法線ベクトル）
	};

	ID3D11Buffer* pVertexBuffer_;//頂点バッファ用メモリ
	ID3D11Buffer** pIndexBuffer_;//インデックスバッファ用メモリ
	ID3D11Buffer* pConstantBuffer_;//コンスタントバッファ用メモリ
	std::vector<MATERIAL> pMaterialList_;//マテリアルの配列
	std::vector<int> indexCount_;//マテリアルごとのインデックス数
	
	int vertexCount_;	//頂点数
	int polygonCount_;	//ポリゴン数
	int materialCount_;	//マテリアルの個数

	void InitVertex(fbxsdk::FbxMesh* mesh);
	void InitIndex(fbxsdk::FbxMesh* mesh);
	void InitConstantBuffer();
	void InitMaterial(fbxsdk::FbxNode* pNode);

	void PassDataToCB(Transform& transform);   //コンスタントバッファに各種情報を渡す
	void SetBufferToPipeline();
public:
	FBX();
	HRESULT Load(std::string fileName);
	void    Draw(Transform& transform);
	void    Release();
};

