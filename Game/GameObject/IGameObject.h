//======================================================
// File Name	: IGameObject.h
// Summary	: ゲームオブジェクト
//======================================================
#pragma once

#include <string>

#include <DirectXTK\SimpleMath.h>

#include <Game\Common\StepTimer.h>
#include <Game\GameObject\ObjectTag.h>



class IGameObject
{
private:
	bool m_isValid;
	// 描画順序管理用(小さいほど手前に描画される）
	int m_drawPrio;
	ObjectTag m_tag;


protected:
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;
	DirectX::SimpleMath::Vector3 m_scale;


public:
	IGameObject(const ObjectTag tag = ObjectTag::None);

public:
	virtual ~IGameObject();


public:
	virtual void Update(const DX::StepTimer& timer) = 0;
	virtual void Render(const DX::StepTimer& timer) = 0;

	virtual void OnCollision(IGameObject* object) = 0;

public:
	void Invalidate();
	bool IsValid() const;
	bool IsInvalid() const;

	const ObjectTag GetTag() const;
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	const DirectX::SimpleMath::Vector3& GetScale() const;
	const int GetDrawPrio() const;

	void SetTag(const ObjectTag tag);
	void SetPosition(DirectX::SimpleMath::Vector3& position);
	void SetRotation(DirectX::SimpleMath::Vector3& rotation);
	void SetScale(DirectX::SimpleMath::Vector3& scale);
	void SetDrawPrio(int prio);

public:
	static void Destroy(IGameObject* object);
};