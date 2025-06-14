#pragma once

/// <summary>
/// シーンが変わっても、変数を保持するためのクラス
/// PlayerをUserにするか、Comにするかを保持している
/// シングルトンで作っています
/// </summary>
class DataCarrier {
private:
	DataCarrier();
	~DataCarrier();
public:
	static DataCarrier* GetInstance() {
		static DataCarrier inst;
		return &inst;
	}

	/// <summary>
	/// それぞれの色をUserにするか、Comにするか
	/// </summary>
	/// <param name="id">色番号(0:黒、1:白)</param>
	/// <param name="user">userの場合true</param>
	void SetPlayUser(int id, bool user);

	/// <summary>
	/// UserかComかを返す
	/// </summary>
	/// <param name="id">色番号(0:黒、1:白)</param>
	/// <returns>userの場合にtrue</returns>
	bool IsPlayUser(int id) const;
private:
	bool player[2];
};