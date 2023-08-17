#pragma once
#include "Player.h"
#include "BoxCollision.h"

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
	float enemy_speed;						// 初速度
	float acceleration;						// 加速度
	float bounce_coefficient;				// 反発係数
	int enemy_type;							// 敵の種類（0：桃色　1：緑色　2：赤色）
	int power_up_flg;						// パワーアップのフラグ（TRUE:パワーアップする　FALSE:パワーアップしない）
	int enemy_death;						// 敵の生死状態（TRUE:死亡　FALSE:生存）
	int enemy_delete;						// 敵の削除（TRUE:削除）
	int bound_flg;							// 敵の跳ね返り状態（1:跳ね返る　0:跳ね返らない）
	int levitation_flg;						// 敵の浮上（TRUE:浮上する）

	// 移動するときの計算に使う変数
	float abs_x;							// X座標の絶対値
	float abs_y;							// Y座標の絶対値
	float distance_x;						// X座標の距離
	float distance_y;						// Y座標の距離

	// アニメーション用カウント
	int inflat_bealloon_count;				// 風船を膨らましきるまでのカウント
	//int flight_count;						// 羽ばたくアニメーション用カウント
	int animation_count;					// アニメーション用カウント
	int levitation_count;					// 浮上するカウント

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

	// 慣性の処理
	void Inertia();

	// 風船を膨らませる処理
	void InflatBealloon();

	// 空中で羽ばたくアニメーション処理
	void Flight();

	// 空中落下アニメーション処理
	void AirFall();

	// パラシュート状態の処理
	void Parachute();

	// 直立状態の処理
	void Upright();

	// 死亡時の処理
	void Death();

	// プレイヤーとの座標の差を取得するかの判定処理
	void CkeckPlayerLocation();

	// X座標のワープをした後の座標変更処理
	void AfterWarp();

	// 下方向に跳ね返る
	void BoundDown();

	// 敵の跳ね返りフラグの設定
	void SetBoundFlg(int set_flg);

	// 浮上する処理
	void Levitation(void);

	// 敵の浮上フラグの設定
	void SetLevitationFlg(int set_flg);

	// 敵の死亡フラグの取得
	int GetEnemyDeathFlg();

	// 敵の死亡フラグの設定
	void SetEnemyDeathFlg(int flg);

	// 敵の削除フラグの取得
	int GetEnemyDeleteFlg();

	//シャボン玉スポーン時の敵の状態からの判断するための処理
	bool EnemyStateJudgment(void);

	public:
		static float get_location_x;		// 敵のX座標参照用の変数
		static float get_location_y;		// 敵ののY座標参照用の変数
};

