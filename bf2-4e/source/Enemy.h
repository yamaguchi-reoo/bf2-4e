#pragma once

class Enemy
{
private:
	// 画像用変数
	int enemy_pink_image[19];				// 桃色の敵の画像
	int enemy_green_image[19];				// 緑色の敵の画像
	int enemy_red_image[19];				// 赤色の敵の画像

	int enemy_x;							// 敵のX座標
	int enemy_y;							// 敵のY座標
	int enemy_speed;						// 敵のスピード

	int fps_count;							// fpsのカウント
	//int animation_pattern_number;			// アニメーションパターンの番号
	int second;								// 秒数のカウント

	int inflat_bealloon_count;				// 風船を膨らましきるまでのカウント

	int now_image;							// 今から表示される画像
	int next_image;							// 次に表示される画像

	enum class EnemyState
	{
		kInflatBealloon,					// 風船を膨らませる
		kFlight,							// 空中で羽ばたく
		kParachute,							// パラシュート
		kUpright,							// 直立
		kDeath								// 死亡
	};

	EnemyState enemy_state;						// 敵の状態

public:
	// コンストラクタ
	Enemy();
	// デストラクタ
	~Enemy();

	// 描画以外の更新を実装
	void Update();

	// 描画に関することを実装
	void  Draw() const;

	// 敵の上下左右移動処理
	void EnemyMove();

	// 敵の回避行動処理
	void Avoidance();

	// 風船を膨らませるアニメーション処理
	void InflatBealloon();

	// 空中で羽ばたくアニメーション処理
	void Flight();

	// パラシュート状態のアニメーション処理
	void Parachute();

	// 直立状態の処理
	void Upright();

	// 死亡時のアニメーション処理
	void Death();
};

