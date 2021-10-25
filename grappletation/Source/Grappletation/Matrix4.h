// COMP710 GP Framework 2021
#ifndef __MATRIX4_H__
#define __MATRIX4_H__
struct Matrix4
{
	float m[4][4];
};
void SetZero(Matrix4& mat);
void SetIdentity(Matrix4& mat);
void CreateOrthoProjection(Matrix4& mat, float width, float height);
#endif // __MATRIX4_H__