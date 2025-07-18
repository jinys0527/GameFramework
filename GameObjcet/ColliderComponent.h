#pragma once
#include "Component.h"
#include "SimpleMathHelper.h"

using Vec2F = Math::Vector2F;

struct CollisionInfo
{
	ColliderComponent* self;         // 자신
	ColliderComponent* other;        // 충돌 상대
	Vec2F normal;                    // 충돌 노멀 (self 기준)
	Vec2F contactPoint;              // 접촉 지점 (필요할 경우)
	float penetrationDepth;          // 침투 깊이 (분리 계산에 사용)
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

