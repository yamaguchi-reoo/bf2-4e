#include "Collision.h"

bool BoxCollider::HitBox(BoxCollider* bCollider)
{
	bool ret = false;	//�Ԃ�l

	//�v���C���[�̓����蔻��͈̔�
	float player_x1 = location.x - (erea.width * erea.width_rate);
	float player_y1 = location.y - (erea.height * erea.height_rate);
	float player_x2 = player_x1 + erea.width;
	float player_y2 = player_x2 + erea.height;

	//�G�l�~�[�̓����蔻��͈̔�
	float enemy_x1 = bCollider->location.x - (bCollider->erea.width * bCollider->erea.width_rate);
	float enemy_y1 = bCollider->location.y - (bCollider->erea.height * bCollider->erea.height_rate);
	float enemy_x2 = enemy_x1 + bCollider->erea.width;
	float enemy_y2 = enemy_y1 + bCollider->erea.height;


	//�X�e�[�W�̓����蔻��͈̔�
	for (int i = 0; i < 7; i++) {
		float stage_x1 = bCollider->stage[i].x;
		float stage_y1 = bCollider->stage[i].y;
		float stage_x2 = stage_x1 + bCollider->stage[i].w;
		float stage_y2 = stage_y1 + bCollider->stage[i].h;

		//�X�e�[�W�ƃv���C���[�̓����蔻��
		if ((player_x1 < stage_x2) && (stage_x1 < player_x2) && (player_y1 < stage_x2) && (player_y1 < stage_y2)) //�����蔻��
		{
			ret = true;
		}

	}
	
	//�G�l�~�[�ƃv���C���[�̓����蔻��
	return false;

	if ((player_x1 < enemy_x2) && (enemy_x1 < player_x2) && (player_y1 < enemy_y2) && (enemy_y1 < player_y2))
	{
		return true;
	}
	return ret;
}

//���S���W�̎擾
Location BoxCollider::GetLocation() const
{
	Location ret = { location.x,location.y };
	return ret;
}

//���a�̎擾
Erea BoxCollider::GetErea()const
{
	return erea;
}

//���S���W�̐ݒ�
void BoxCollider::SetLocation(Location location)
{
	this->location = location;
}