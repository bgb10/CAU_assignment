// -----------------------------------------------------------------------------
// CWall class definition
// -----------------------------------------------------------------------------
#include "CWall.h"

CWall::CWall(void)
{
	D3DXMatrixIdentity(&m_mLocal);
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	m_width = 0;
	m_depth = 0;
	m_pBoundMesh = NULL;
}
CWall::~CWall(void) {}

bool CWall::create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color)
{
	if (NULL == pDevice)
		return false;

	m_mtrl.Ambient = color;
	m_mtrl.Diffuse = color;
	m_mtrl.Specular = color;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 5.0f;

	m_width = iwidth;
	m_depth = idepth;

	if (FAILED(D3DXCreateBox(pDevice, iwidth, iheight, idepth, &m_pBoundMesh, NULL)))
		return false;
	return true;
}
void CWall::destroy(void)
{
	if (m_pBoundMesh != NULL) {
		m_pBoundMesh->Release();
		m_pBoundMesh = NULL;
	}
}
void CWall::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
{
	if (NULL == pDevice)
		return;
	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
	pDevice->SetMaterial(&m_mtrl);
	m_pBoundMesh->DrawSubset(0);
}

bool CWall::hasIntersected(CSphere& ball) {
	// Insert your code here.
	float cord_x = ball.getCenter().x;
	float cord_y = ball.getCenter().y;
	float cord_z = ball.getCenter().z;

	if (cord_x >= (4.5 - M_RADIUS)) {
		return true;
	}
	else if (cord_x <= (-4.5 + M_RADIUS)) {
		return true;
	}
	else if (cord_z <= (-3 + M_RADIUS)) {
		return true;
	}
	else if (cord_z >= (3 - M_RADIUS)) {
		return true;
	}

	return false;
}

void CWall::hitBy(CSphere& ball) {
	// Insert your code here.
	//충돌 구현

	//튕기기
	if (hasIntersected(ball)) {
		float cord_x = ball.getCenter().x;
		float cord_y = ball.getCenter().y;
		float cord_z = ball.getCenter().z;

		if (cord_x >= (4.5 - M_RADIUS)) { //hit on right wall
			cord_x = 4.5 - M_RADIUS;
			ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
		}
		else if (cord_x <= (-4.5 + M_RADIUS)) { //hit on left wall
			cord_x = -4.5 + M_RADIUS;
			ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
		}
		else if (cord_z <= (-3 + M_RADIUS)) { //hit on downward wall
			cord_z = -3 + M_RADIUS;
			ball.setPower(ball.getVelocity_X(), -ball.getVelocity_Z());
		}
		else if (cord_z >= (3 - M_RADIUS)) { //hit on upward wall
			cord_z = 3 - M_RADIUS;
			ball.setPower(ball.getVelocity_X(), -ball.getVelocity_Z());
		}
		ball.setCenter(cord_x, cord_y, cord_z);
	}
}

void CWall::setPosition(float x, float y, float z)
{
	D3DXMATRIX m;
	this->m_x = x;
	this->m_z = z;

	D3DXMatrixTranslation(&m, x, y, z);
	setLocalTransform(m);
}