#pragma once

#pragma once

class Thunder
{
private:
	/* 画像用変数 */
	//雷
	int thunder_cloud_image[3];
	int thunder_image[6];
	int thunder_effect_image[3];

	//サカナ
	int fish_image;

	/*アニメーションの待機変数*/
	//雷雲
	int cloud_time;
	int cloud_anime_num;

	//かみなり
	int thunder_time;
	int thunder_anime_num;

	//雷モドキ
	int thunder_effect_time;
	int thunder_effect_anime_num;

public:
	//コンストラクタ
	Thunder();

	//デストラクタ
	~Thunder();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

};

