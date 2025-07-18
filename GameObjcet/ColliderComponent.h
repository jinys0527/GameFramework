#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"

using Vec2F = Math::Vector2F;

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
	virtual ~ColliderComponent() = default;
	void Start();
	void Update(float deltaTime) override;
	void OnEvent(EventType type, const void* data) override;
	void OnDestroy();

protected:
	virtual void OnCollisionEnter(const CollisionInfo* info) {}
	virtual void OnCollisionStay(const CollisionInfo* info)  {}
	virtual void OnCollisionExit(const CollisionInfo* info)  {}

	bool isTrigger;
	Vec2F center;
};

