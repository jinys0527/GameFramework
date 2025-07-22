#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"

using Vec2F = Math::Vector2F;

class ColliderComponent;

struct CollisionInfo
{
	ColliderComponent* self;         // �ڽ�
	ColliderComponent* other;        // �浹 ���
	Vec2F normal;                    // �浹 ��� (self ����)
	Vec2F contactPoint;              // ���� ���� (�ʿ��� ���)
	float penetrationDepth;          // ħ�� ���� (�и� ��꿡 ���)
};

class ColliderComponent : public Component, public IEventListener
{
	
public:
	virtual ~ColliderComponent() { OnDestroy(); }
	virtual void Start();
	void SetCenter(const Vec2F& center)
	{
		this->center = center;
	}
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	virtual void OnDestroy();

protected:
	virtual void OnCollisionEnter(const CollisionInfo* info) {}
	virtual void OnCollisionStay(const CollisionInfo* info)  {}
	virtual void OnCollisionExit(const CollisionInfo* info)  {}

	bool isTrigger;
	Vec2F center;
};

