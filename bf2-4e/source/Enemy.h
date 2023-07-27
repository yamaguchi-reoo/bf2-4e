#pragma once
#include "Player.h"
#include "BoxCollision.h"

// 敵の最大数
//#define ENEMY_MAX (6)

// 敵の状態
enum class EnemyState
{
	kInflatBealloon = 0,				// 風船を膨らませる
	kFlight,							// 空中で羽ばたく
	kParachute,							// パラシュート
	kUpright,							// 直立
	kDeath								// 死亡
};

// 当たり判定あり
class Enemy : public BoxCollision
{
private:
	// 画像用変数
	int enemy_pink_image[18];				// 桃色の敵の画像
	int enemy_green_image[18];				// 緑色の敵の画像
	int enemy_red_image[18];				// 赤色の敵の画像

	// 敵の情報
	//float enemy_x;							// 敵のX座標
	//float enemy_y;							// 敵のY座標
	float enemy_speed;						// 敵のスピード
	float acceleration;						// 加速度
	int enemy_angle;						// 敵の移動角度
	int enemy_type;							// 敵の種類（0：桃色　1：緑色　2：赤色）
	int power_up_flg;						// パワーアップのフラグ（TRUE:パワーアップする　FALSE:パワーアップしない）
	int enemy_life;							// 敵の生死状態（TRUE:生きている　FALSE:死亡）

	int inertia_count;						// 慣性が働くカウント
	int inertia_flg;						// 慣性フラグ

	// 移動するときの計算に使う変数
	float xc;								// 三平方の定理（斜辺）
	float yc;								// 三平方の定理（斜辺）
	float x;								// 計算後move_xに代入用
	float y;								// 計算後move_yに代入用

	// 後で消すやつ
	int fps_count;							// fpsのカウント
	int second;								// 秒数のカウント

	// アニメーション用カウント
	int inflat_bealloon_count;				// 風船を膨らましきるまでのカウント
	//int flight_count;						// 羽ばたくアニメーション用カウント
	int animation_count;					// アニメーション用カウント

	int now_image;							// 今から表示される画像
	int next_image;							// 次に表示される画像

	// 追いかける対象の座標
	float player_x;							// プレイヤーのX座標
	float player_y;							// プレイヤーのY座標

	// 移動するときに使う変数
	float move_x;							// 敵の座標Xの移動量
	float move_y;							// 敵の座標Yの移動量

	int turn_flg;							// 画像の左右反転状態（TRUE:反転　FALSE:普通に描画）
	int old_turn_flg;						// 前回の画像の状態を保存

	int ckeck_flg;							// プレイヤーとの座標の差を取得するフラグ
	int ckeck_count;						// ckeck_flg用カウント

	float angle;							// パラシュート状態の左右移動用
	float angle2;							// パラシュート状態の左右移動用
	float amplitude;						// パラシュート状態で下降するときの振れ幅
	float enemy_start_x;					// パラシュート状態になったx座標

	int avoidance_count;					// 回避時間
	int avoidance_flg;						// 回避行動のフラグ
	float difference_y;						// 回避行動の条件用のプレイヤーと敵の座標の差

public:
	EnemyState enemy_state;					// 敵の状態

	// コンストラクタ
	Enemy(float set_x, float set_y, int set_type);
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

	// 空中落下アニメーション処理
	void AirFall();

	// パラシュート状態のアニメーション処理
	void Parachute();

	// 直立状態の処理
	void Upright();

	// 死亡時のアニメーション処理
	void Death();

	// プレイヤーとの座標の差を取得するかの判定処理
	void CkeckPlayerLocation();

	// X座標のワープをした後の座標変更処理
	void AfterWarp();
};

