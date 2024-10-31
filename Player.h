#pragma once
#include "Engine/GameObject.h"

class Player :
	public GameObject
{
	enum ODEN_STATE {
		STICK, //–_‚¾‚¯
		T,     //‚¿‚­‚í‚ ‚è
		DT,    //‘åª‚¿‚­‚í‚ ‚è
		KDT,   //‚±‚ñ‚É‚á‚­‘åª‚¿‚­‚í‚ ‚è
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

