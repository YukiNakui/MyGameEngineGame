#pragma once
#include "Engine/GameObject.h"

class Player :
	public GameObject
{
	enum ODEN_STATE {
		STICK, //�_����
		T,     //�����킠��
		DT,    //�卪�����킠��
		KDT,   //����ɂႭ�卪�����킠��
		MAX
	};

	int hModel[ODEN_STATE::MAX];
	int HP;
	bool isDead;
public:
	Player(GameObject* parent);
	~Player();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	bool IsPlayerDead() { return isDead; }
	void OnCollision(GameObject* pTarget) override;
};

