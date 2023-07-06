#include "Collision.h"

bool BoxCollider::HitBox(BoxCollider* bCollider)
{
	bool ret = false;

	//プレイヤーの当たり判定の範囲
	float player_x1 = location.x - (erea.width * erea.width_rate);
	float player_y1 = location.y - (erea.height * erea.height_rate);
	float player_x2 = player_x1 + erea.width;
	float player_y2 = player_x2 + erea.height;

	//エネミーの当たり判定の範囲
	float enemy_x1 = bCollider->location.x - (bCollider->erea.width * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - (bCollider->erea.height * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;

	//エネミーとプレイヤーの当たり判定


	return false;
}

Location BoxCollider::GetLocation() const
{
	Location ret = { location.x,location.y };
	return ret;
}
