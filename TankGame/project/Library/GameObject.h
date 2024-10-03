#pragma once
/// <summary>
/// ゲームオブジェクトの基底クラス
/// </summary>
/// <author>N.Hanai</author>

#include <DxLib.h>
#include <string>
#include "SceneBase.h"
#include "ObjectManager.h"
#include "Time.h"

class GameObject
{
public:
	GameObject() : tag(""), destroy(false), drawOrder(0) { ObjectManager::Push(this); }
	virtual ~GameObject() {}

	/// <summary>
	/// 毎フレームの更新処理のために呼ばれます
	/// </summary>
	virtual void Update() {}

	/// <summary>
	/// 毎フレームの描画処理のために呼ばれます
	/// </summary>
	virtual void Draw() {}

	/// <summary>
	/// 自分のインスタンスを削除する時に呼び出してください
	/// 次回のUpdateの前に削除されます
	/// </summary>
	void DestroyMe() { destroy = true; }

	bool DestroyRequested() { return destroy; }

	/// <summary>
	/// 描画の優先順位を指定します
	/// 数値が高いほど、後から描画されるので、
	/// 2Dであれば、手前に表示されます
	/// 何も指定しなければ０です
	/// </summary>
	/// <param name="odr">描画順位</param>
	void SetDrawOrder(int order) {
		drawOrder = order;
		ObjectManager::SortByDrawOrder();
	}

	inline int GetDrawOrder() {	return drawOrder; }

	/// <summary>
	/// タグをつける
	/// タグは１つだけ付けることができます
	/// </summary>
	/// <param name="_tag">タグ</param>
	void SetTag(std::string _tag) { tag = _tag; }

	/// <summary>
	/// 指定されたタグと同じかを返す
	/// </summary>
	/// <param name="_tag">タグ</param>
	/// <returns>同じであればtrue</returns>
	bool IsTag(std::string _tag) const { return tag == _tag; }
private:
	std::string tag;     // タグ
	bool destroy;
	int drawOrder;
};
