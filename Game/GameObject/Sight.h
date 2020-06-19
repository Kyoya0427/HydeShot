#pragma once
#include <DirectXTK/PrimitiveBatch.h>
#include <Game/GameObject/GameObject.h>

#include <Game/Collider/RayCollider.h>

class Character;

class Sight : public GameObject
{
public:
	Sight(Character* chara);
	~Sight();

public:
	// 更新
	void Update(const DX::StepTimer& timer) override;
	// 描画
	void Render() override;
	//当たった後の処理
	void OnCollision(GameObject* object) override;

private:
	std::unique_ptr<DirectX::GeometricPrimitive> m_sightCollider;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>  m_lineCollider;
	std::unique_ptr<DirectX::BasicEffect> m_basicEffect;
	//当たり判定
	std::unique_ptr<RayCollider>				 m_collider;
	DirectX::SimpleMath::Vector3                 m_size;
	DirectX::SimpleMath::Vector3                 m_posA;
	DirectX::SimpleMath::Vector3                 m_posB;

	Character*                                   m_chara;
	bool                                         m_contact;
};

