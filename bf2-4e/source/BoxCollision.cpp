#include "BoxCollision.h"

bool BoxCollision::HitBox(BoxCollision* bCollider)
{
	bool ret = false;	//返り値

	//プレイヤーの当たり判定の範囲
	float player_x1 = location.x -(erea.width * erea.width_rate);
	float player_y1 = location.y - (erea.height * erea.height_rate);
	float player_x2 = player_x1 + erea.width;
	float player_y2 = player_y1 + erea.height;

	//エネミーの当たり判定の範囲
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - ((bCollider->erea.height / 2) * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;

	if ((player_x1 < enemy_x2) && (enemy_x1 < player_x2) && (player_y1 < enemy_y2) && (enemy_y1 < player_y2))
	{
		return true;
	}
	old_location_top = player_y1;
	old_location_bottom = enemy_y2;

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

bool BoxCollision:: HitTopBox(BoxCollision* bCollider) 
{
	bool ret = false;
	//プレイヤーの当たり判定の範囲
	float player_x1 = location.x - (erea.width * erea.width_rate);
	float player_y1 = location.y - (erea.height * erea.height_rate);
	float player_x2 = player_x1 + erea.width;
	float player_y2 = player_y1 + erea.height;

	//エネミーの当たり判定の範囲
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - ((bCollider->erea.height / 2) * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;	

	if ((int)player_y1 <= (int)enemy_y2)
	{
		if ((int)old_location_top >= (int)old_location_bottom)
		{
			enemy_y2 = player_y1;
			bCollider->location.y = enemy_y2 - (bCollider->erea.height / 2);
			ret = true;
		}	
	}
	
	return ret;
}

// 敵とステージの当たり判定
bool BoxCollision::EnemyHitBox(BoxCollision* bCollider)
{
	bool ret = false;	//返り値

	//ステージの当たり判定の範囲
	float stage_x1 = location.x - (erea.width / 2 * erea.width_rate);
	float stage_y1 = location.y - (erea.width / 2 * erea.height_rate);
	float stage_x2 = stage_x1 + erea.width;
	float stage_y2 = stage_y1 + erea.height;

	//エネミーの当たり判定の範囲
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - ((bCollider->erea.height / 2) * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;

	if ((stage_x1 < enemy_x2) && (enemy_x1 < stage_x2) && (stage_y1 < enemy_y2) && (enemy_y1 < stage_y2))
	{
		ret = true;
	}

	return ret;
}

// 敵とステージの上のラインの当たり判定
bool BoxCollision::EnemyHitTopBox(BoxCollision* bCollider)
{
	bool ret = false;	//返り値

	//ステージの当たり判定の範囲
	float stage_x1 = location.x - (erea.width / 2 * erea.width_rate);
	float stage_y1 = location.y - (erea.width / 2 * erea.height_rate);
	float stage_x2 = stage_x1 + erea.width;
	float stage_y2 = stage_y1 + erea.height;

	//エネミーの当たり判定の範囲
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - ((bCollider->erea.height / 2) * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;

	if ((stage_x1 < enemy_x2) && (enemy_x1 < stage_x2) && (stage_y1 < enemy_y2) && (enemy_y2 < stage_y2))
	{
		enemy_y2 = stage_y1;
		bCollider->location.y = enemy_y2 - (bCollider->erea.height / 2);
		ret = true;
	}
	return ret;
}

// 風船部分の当たり判定
bool BoxCollision::HitBealloon(BoxCollision* bCollider)
{
	bool ret = false;	//返り値

	//風船部分の当たり判定の範囲
	float player_x1 = location.x - (erea.width / 2 * erea.width_rate);
	float player_y1 = location.y - (erea.width / 2 * erea.height_rate);
	float player_x2 = player_x1 + erea.width;
	float player_y2 = location.y;

	//体部分の判定の範囲
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y;
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 - ((bCollider->erea.height / 2) * bCollider->erea.height_rate) + bCollider->erea.height;

	if ((player_x1 < enemy_x2) && (enemy_x1 < player_x2) && (player_y1 < enemy_y2) && (enemy_y1 < player_y2))
	{
		return true;
	}

	return ret;
}

// 体部分の当たり判定
bool BoxCollision::HitBody(BoxCollision* bCollider)
{
	bool ret = false;	//返り値

	//体部分の当たり判定の範囲
	float player_x1 = location.x - (erea.width / 2 * erea.width_rate);
	float player_y1 = location.y;
	float player_x2 = player_x1 + erea.width;
	float player_y2 = player_y1 - (erea.width / 2 * erea.height_rate) + erea.height;

	//風船部分の当たり判定の範囲
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = bCollider->location.y;

	if ((player_x1 < enemy_x2) && (enemy_x1 < player_x2) && (player_y1 < enemy_y2) && (enemy_y1 < player_y2))
	{
		return true;
	}

	return ret;
}