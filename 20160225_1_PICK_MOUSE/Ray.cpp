#include "stdafx.h"
#include "Ray.h"


Ray::Ray()
{
}


Ray::~Ray()
{
}

Ray Ray::CalcRayFromScreenPoint(POINT mousePoint)
{
	D3DVIEWPORT9 viewPort;
	GameManager::GetDevice()->GetViewport(&viewPort);
	D3DXMATRIXA16 projection;
	GameManager::GetDevice()->GetTransform(
		D3DTS_PROJECTION, &projection);

	Ray resultRay;
	//뷰포트와 프로젝션의 영향을 제거
	resultRay.direction.x = ((2.0f * mousePoint.x) / viewPort.Width - 1.0f) / projection(0, 0);
	resultRay.direction.y = ((-2.0f * mousePoint.y) / viewPort.Height + 1.0f) / projection(1, 1);
	resultRay.direction.z = 1.0f;

	//projection(0, 0);
	//projection._11;

	D3DXMATRIXA16 view, inverseView;
	GameManager::GetDevice()->GetTransform(D3DTS_VIEW, &view);
	D3DXMatrixInverse(&inverseView, nullptr, &view);

	D3DXVec3TransformCoord(&resultRay.origin, &resultRay.origin, &inverseView);
	D3DXVec3TransformNormal(&resultRay.direction, &resultRay.direction, &inverseView);
	D3DXVec3Normalize(&resultRay.direction, &resultRay.direction);

	return resultRay;
}