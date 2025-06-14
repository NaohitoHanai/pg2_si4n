#pragma once
#include <DxLib.h>
#include <math.h>

namespace DxLib {
	const float DegToRad = DX_PI_F / 180.0f;
	const float RadToDeg = 180.0f / DX_PI_F;

	inline const VECTOR VGet(VECTOR_D v) { return VGet((float)v.x, (float)v.y, (float)v.z);	}
	inline const VECTOR_D VGetD(VECTOR v) { return VGetD((double)v.x, (double)v.y, (double)v.z); }

	inline const VECTOR operator +(const VECTOR& v1, const VECTOR& v2) { return VAdd(v1, v2); }
	inline const VECTOR_D operator +(const VECTOR_D& v1, const VECTOR_D& v2) { return VAddD(v1, v2); }

	inline VECTOR& operator +=(VECTOR& v1, const VECTOR& v2) { return v1 = VAdd(v1, v2); }
	inline VECTOR_D& operator +=(VECTOR_D& v1, const VECTOR_D& v2) { return v1 = VAddD(v1, v2); }

	inline const VECTOR operator -(const VECTOR& v1, const VECTOR& v2) { return VSub(v1, v2); }
	inline const VECTOR_D operator -(const VECTOR_D& v1, const VECTOR_D& v2) { return VSubD(v1, v2); }

	inline VECTOR& operator -=(VECTOR& v1, const VECTOR& v2) { return v1 = VSub(v1, v2); }
	inline VECTOR_D& operator -=(VECTOR_D& v1, const VECTOR_D& v2) { return v1 = VSubD(v1, v2); }

	inline const VECTOR operator *(const VECTOR& v1, const float& scale) { return VScale(v1, scale); }
	inline const VECTOR_D operator *(const VECTOR_D& v1, const double& scale) { return VScaleD(v1, scale); }

	inline const VECTOR operator *(const float& scale, const VECTOR& v1) { return VScale(v1, scale); }
	inline const VECTOR_D operator *(const double& scale, const VECTOR_D& v1) { return VScaleD(v1, scale); }

	inline const VECTOR operator /(const VECTOR& v1, const float& scale) { return VScale(v1, 1.0f/scale); }
	inline const VECTOR_D operator /(const VECTOR_D& v1, const double& scale) { return VScaleD(v1, 1.0/scale); }

	inline VECTOR& operator *=(VECTOR& v1, const float& scale) { return v1 = VScale(v1, scale); }
	inline VECTOR_D& operator *=(VECTOR_D& v1, const double& scale) { return v1 = VScaleD(v1, scale); }

	inline VECTOR& operator *=(const float& scale, VECTOR& v1) { return v1 = VScale(v1, scale); }
	inline VECTOR_D& operator *=(const double& scale, VECTOR_D& v1) { return v1 = VScaleD(v1, scale); }

	inline VECTOR& operator /=(VECTOR& v1, const float& scale) { return v1 = VScale(v1, 1.0f / scale); }
	inline VECTOR_D& operator /=(VECTOR_D& v1, const double& scale) { return v1 = VScaleD(v1, 1.0 / scale); }

	inline const MATRIX operator +(const MATRIX& m1, const MATRIX& m2) { return MAdd(m1, m2); }
	inline const MATRIX_D operator +(const MATRIX_D& m1, const MATRIX_D& m2) { return MAddD(m1, m2); }

	inline MATRIX& operator +=(MATRIX& m1, const MATRIX& m2) { return m1 = MAdd(m1, m2); }
	inline MATRIX_D& operator +=(MATRIX_D& m1, const MATRIX_D& m2) { return m1 = MAddD(m1, m2); }

	inline const MATRIX operator *(const MATRIX& m1, const MATRIX& m2) { return MMult(m1, m2); }
	inline const MATRIX_D operator *(const MATRIX_D& m1, const MATRIX_D& m2) { return MMultD(m1, m2); }

	inline MATRIX& operator *=(MATRIX& m1, const MATRIX& m2) { return m1 = MMult(m1, m2); }
	inline MATRIX_D& operator *=(MATRIX_D& m1, const MATRIX_D& m2) { return m1 = MMultD(m1, m2); }

	inline const VECTOR operator *(const VECTOR& v, const MATRIX& m1) { return VTransform(v, m1); }
	inline const VECTOR_D operator *(const VECTOR_D& v, const MATRIX_D& m1) { return VTransformD(v, m1); }

	inline VECTOR& operator *=(VECTOR& v, const MATRIX& m1) { return v = VTransform(v, m1); }
	inline VECTOR_D& operator *=(VECTOR_D& v, const MATRIX_D& m1) { return v = VTransformD(v, m1); }

	static const VECTOR VZero = { 0,0,0 };
	static const VECTOR VOne = { 1,1,1 };

	class VECTOR3 : public VECTOR {
	public:
		VECTOR3() : VECTOR3(0, 0, 0) {}
		VECTOR3(float _x, float _y, float _z) {
			x = _x;
			y = _y;
			z = _z;
		}
		static const VECTOR3& Zero() {
			return VECTOR3(0, 0, 0);
		}
		static const VECTOR3& One() {
			return VECTOR3(1, 1, 1);
		}
		const float Size() {
			return sqrtf(x*x+y*y+z*z);
		}
		const float SizeSquare() {
			return x*x+y*y+z*z;
		}
	};

	struct VECTOR2 {
		float x, y;
		VECTOR2() : VECTOR2(0, 0) {}
		VECTOR2(float _x, float _y) {
			x = _x;
			y = _y;
		}
		static const VECTOR2& Zero() {
			return VECTOR2(0, 0);
		}
		static const VECTOR2& One() {
			return VECTOR2(1, 1);
		}
		const float Size() const {
			return sqrtf(x * x + y * y);
		}
		const float SizeSquare() const {
			return x * x + y * y;
		}
	};

	inline const VECTOR2 operator +(const VECTOR2& v1, const VECTOR2& v2) { return VECTOR2(v1.x+v2.x, v1.y+v2.y); }
	inline VECTOR2& operator +=(VECTOR2& v1, const VECTOR2& v2) { return v1 = v1 + v2; }

	inline const VECTOR2 operator -(const VECTOR2& v1, const VECTOR2& v2) { return VECTOR2(v1.x - v2.x, v1.y - v2.y); }
	inline VECTOR2& operator -=(VECTOR2& v1, const VECTOR2& v2) { return v1 = v1 - v2; }

	inline const VECTOR2 operator *(const VECTOR2& v1, const float& scale) { return VECTOR2(v1.x * scale, v1.y * scale); }
	inline const VECTOR2 operator *(const float& scale, const VECTOR2& v1) { return VECTOR2(v1.x * scale, v1.y * scale); }
	inline const VECTOR2 operator /(const VECTOR2& v1, const float& scale) { return VECTOR2(v1.x / scale, v1.y / scale); }

	inline VECTOR2& operator *=(VECTOR2& v1, const float& scale) { return v1 = v1 * scale; }
	inline VECTOR2& operator *=(const float& scale, VECTOR2& v1) { return v1 = scale * v1; }
	inline VECTOR2& operator /=(VECTOR2& v1, const float& scale) { return v1 = v1 / scale; }
};

template <class T>
inline void safe_delete(T*& p) {
	if (p != nullptr) {
		delete p;
		p = nullptr;
	}
}

template <class T>
inline void safe_delete_array(T*& p) {
	if (p != nullptr) {
		delete[] p;
		p = nullptr;
	}
}