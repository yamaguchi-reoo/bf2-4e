#pragma once

enum class EnemyState
{
	kInflatBealloon,					// 風船を膨らませる
	kFlight,							// 空中で羽ばたく
	kParachute,							// パラシュート
	kUpright,							// 直立
	kDeath								// 死亡
};

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
	int enemy_angle;						// 敵の移動角度
	float c;

	int fps_count;							// fpsのカウント
	int second;								// 秒数のカウント

	int inflat_bealloon_count;				// 風船を膨らましきるまでのカウント

	int now_image;							// 今から表示される画像
	int next_image;							// 次に表示される画像

	EnemyState enemy_state;					// 敵の状態

	int mouse_x;							// マウスのX座標
	int mouse_y;							// マウスのY座標

	float radian;							// 敵とプレイヤーの角度

	int move_x;								// 敵の座標Xの移動量
	int move_y;								// 敵の座標Yの移動量

	int turn_flg;							// 画像の左右反転状態（TRUE:反転　FALSE:普通に描画）

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

