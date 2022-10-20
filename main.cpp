#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LC1A_28_ヨシダメイ";

///構造体
typedef struct Vector2 {
	float x;
	float y;
};
typedef struct Matrix2x2 {
	float m[2][2];
};

//回転の関数
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix,Vector2 pos) {
	Vector2 Multiply;
	Multiply.x = ((vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0])) + pos.x;
	Multiply.y = ((vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1])) + pos.y;
	return Multiply;
}


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	//画像
	int whiteTextureHandle = Novice::LoadTexture("white1x1.png");

	float betaTheta = 0.0f;

	Vector2 pos = { 400.0f,100.0f };
	int width = 200;
	int height = 100;

	//回転前
	Vector2 leftTop = { -width / 2,height / 2 };
	Vector2 rightTop = { width / 2, height / 2 };
	Vector2 leftBottom = { -width / 2, -height / 2 };
	Vector2 rightBottom = { width / 2,-height / 2 };




	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		betaTheta += 1.0 / 32.0f * M_PI;

		///変数の初期化
		Matrix2x2 theta;
		theta.m[0][0] = cosf(betaTheta);
		theta.m[0][1] = sinf(betaTheta);
		theta.m[1][0] = -sinf(betaTheta);
		theta.m[1][1] = cosf(betaTheta);
		//回転後
		Vector2 rotatedLeftTop = Multiply(leftTop, theta, pos);
		Vector2 rotatedRightTop = Multiply(rightTop, theta, pos);
		Vector2 rotatedLeftBottom = Multiply(leftBottom, theta, pos);
		Vector2 rotatedRightBottom = Multiply(rightBottom, theta, pos);

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawQuad(
			rotatedLeftTop.x, rotatedLeftTop.y * -1 + 400,
			rotatedRightTop.x, rotatedRightTop.y * -1 + 400,
			rotatedLeftBottom.x, rotatedLeftBottom.y * -1 + 400,
			rotatedRightBottom.x, rotatedRightBottom.y * -1 + 400,
			0, 0, 1, 1,
			whiteTextureHandle, WHITE
		);

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
