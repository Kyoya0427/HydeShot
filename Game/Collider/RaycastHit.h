//======================================================
// File Name	: RaycastHit.h
// Summary		: レイキャストヒット
// Author		: Kyoya Sakamoto
//======================================================
#pragma once

struct RaycastHit
{
	RaycastHit() :distNear(), distFar(), posNear(), posFar(), normNear(), normFar() {}
	float distNear;
	float distFar;
	DirectX::SimpleMath::Vector3 posNear;
	DirectX::SimpleMath::Vector3 posFar;
	DirectX::SimpleMath::Vector3 normNear;
	DirectX::SimpleMath::Vector3 normFar;
};