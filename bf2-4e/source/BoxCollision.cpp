#include "BoxCollision.h"

bool BoxCollision::HitBox(BoxCollision* bCollider)
{
	bool ret = false;	//返り値

	//プレイヤーの当たり判定の範囲
	float player_x1 = location.x -(erea.width * erea.width_rate);
	float player_y1 = location.y - (erea.height * erea.height_rate);
	float player_x2 = player_x1 + erea.width;
	float player_y2 = player_x2 + erea.height;

	//エネミーの当たり判定の範囲
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - ((bCollider->erea.height / 2) * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;

	if ((player_x1 < enemy_x2) && (enemy_x1 < player_x2) && (player_y1 < enemy_y2) && (enemy_y1 < player_y2))
	{
		return true;
	}

	return ret;
}

//中心座標の取得
Location BoxCollision::GetLocation() const
{
	Location ret = { location.x,location.y };
	return ret;
}

//半径の取得
Erea BoxCollision::GetErea()const
{
	return erea;
}

//中心座標の設定
void BoxCollision::SetLocation(Location location)
{
	this->location = location;
}