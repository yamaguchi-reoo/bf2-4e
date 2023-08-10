#include "BoxCollision.h"

bool BoxCollision::HitBox(BoxCollision* bCollider)
{
	bool ret = false;	//�Ԃ�l

	//�v���C���[�̓����蔻��͈̔�
	float player_x1 = location.x -(erea.width * erea.width_rate);
	float player_y1 = location.y - (erea.height * erea.height_rate);
	float player_x2 = player_x1 + erea.width;
	float player_y2 = player_y1 + erea.height;

	//�G�l�~�[�̓����蔻��͈̔�
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

//���S���W�̎擾
Location BoxCollision::GetLocation() const
{
	Location ret = { location.x,location.y };
	return ret;
}

//���a�̎擾
Erea BoxCollision::GetErea()const
{
	return erea;
}

//���S���W�̐ݒ�
void BoxCollision::SetLocation(Location location)
{
	this->location = location;
}

bool BoxCollision:: HitTopBox(BoxCollision* bCollider) 
{
	bool ret = false;
	//�v���C���[�̓����蔻��͈̔�
	float player_x1 = location.x - (erea.width * erea.width_rate);
	float player_y1 = location.y - (erea.height * erea.height_rate);
	float player_x2 = player_x1 + erea.width;
	float player_y2 = player_y1 + erea.height;

	//�G�l�~�[�̓����蔻��͈̔�
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - ((bCollider->erea.height / 2) * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;

	

	if ((int)player_y1 <= (int)enemy_y2)
	{
		if ((int)old_location_top >= (int)old_location_bottom) {
			enemy_y2 = player_y1;
			bCollider->location.y = enemy_y2 - (bCollider->erea.height / 2);
			ret = true;
		}	
	}
	

	return ret;
}

// �G�ƃX�e�[�W�̓����蔻��
bool BoxCollision::EnemyHitBox(BoxCollision* bCollider)
{
	bool ret = false;	//�Ԃ�l

	//�X�e�[�W�̓����蔻��͈̔�
	float stage_x1 = location.x - (erea.width * erea.width_rate);
	float stage_y1 = location.y - (erea.width * erea.height_rate);
	float stage_x2 = stage_x1 + erea.width;
	float stage_y2 = stage_y1 + erea.height;

	//�G�l�~�[�̓����蔻��͈̔�
	float enemy_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - ((bCollider->erea.height / 2) * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;

	if ((stage_x1 < enemy_x2) && (enemy_x1 < stage_x2) && (stage_y1 < enemy_y2) && (enemy_y1 < stage_y2))
	{
		ret = true;
	}

	//enemy_old_location_top = stage_y1;
	//enemy_old_location_bottom = enemy_y2;

	return ret;
}

// �G�ƃX�e�[�W�̏�̃��C���̓����蔻��
bool BoxCollision::EnemyHitTopBox(BoxCollision* bCollider)
{
	bool ret = false;	//�Ԃ�l

	//�X�e�[�W�̓����蔻��͈̔�
	float stage_x1 = location.x - (erea.width * erea.width_rate);
	float stage_y1 = location.y - (erea.width * erea.height_rate);
	float stage_x2 = stage_x1 + erea.width;
	float stage_y2 = stage_y1 + erea.height;

	//�G�l�~�[�̓����蔻��͈̔�
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

	//if ((int)stage_y1 <= (int)enemy_y2)
	//{
	//	if ((int)enemy_old_location_top >= (int)enemy_old_location_bottom) {
	//		enemy_y2 = stage_y1;
	//		bCollider->location.y = enemy_y2 - (bCollider->erea.height / 2);
	//		ret = true;
	//	}
	//}

	return ret;
}

// �G���m�̓����蔻��i���j
// �܂������Ă��Ȃ������蔻��͋�`�̂܂�
bool BoxCollision::EnemyHitSideBox(BoxCollision* bCollider)
{
	bool ret = false;	//�Ԃ�l

	//�G�l�~�[�P�̓����蔻��͈̔�
	float enemy1_x1 = location.x - (erea.width / 2 * erea.width_rate);
	float enemy1_y1 = location.y - (erea.width / 2 * erea.height_rate);
	float enemy1_x2 = enemy1_x1 + erea.width;
	float enemy1_y2 = enemy1_y1 + erea.height;

	//�G�l�~�[�Q�̓����蔻��͈̔�
	float enemy2_x1 = bCollider->location.x - ((bCollider->erea.width / 2) * bCollider->erea.width_rate);
	float enemy2_y1 = bCollider->location.y - ((bCollider->erea.height / 2) * bCollider->erea.height_rate);
	float enemy2_x2 = enemy2_x1 + bCollider->erea.width;
	float enemy2_y2 = enemy2_y1 + bCollider->erea.height;

	if ((enemy1_x1 < enemy2_x2) && (enemy2_x1 < enemy1_x2) && (enemy1_y1 < enemy2_y2) && (enemy2_y1 < enemy1_y2))
	//if ((enemy1_x2 < enemy2_x1) /*&& (enemy2_x1 < enemy1_x2)*/ && (enemy1_y1 < enemy2_y2) && (enemy2_y1 < enemy1_y2))
	{
		ret = true;
	}

	return ret;
}
