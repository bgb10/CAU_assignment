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

	m_height = iheight;
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
	float cord_z = ball.getCenter().z;

	float hit_boundary_min_x = this->m_x - this->getWidth() / 2 - ball.getRadius();
	float hit_boundary_max_x = this->m_x + this->getWidth() / 2 + ball.getRadius();
	float hit_boundary_min_z = this->m_z - this->getDepth() / 2 - ball.getRadius();
	float hit_boundary_max_z = this->m_z + this->getDepth() / 2 + ball.getRadius();

	if ((hit_boundary_min_x <= cord_x && cord_x <= hit_boundary_max_x) && (hit_boundary_min_z <= cord_z && cord_z <= hit_boundary_max_z)) {
		return true;
	}
	else return false;

	return false;
}

void CWall::hitBy(CSphere& ball) {
	// Insert your code here.
	if (hasIntersected(ball)) {

		float cord_x = ball.getCenter().x;
		float cord_z = ball.getCenter().z;

		float boundary_min_x = this->m_x - this->getWidth() / 2;
		float boundary_max_x = this->m_x + this->getWidth() / 2;
		float boundary_min_z = this->m_z - this->getDepth() / 2;
		float boundary_max_z = this->m_z + this->getDepth() / 2;

		if ((boundary_min_x <= cord_x && cord_x <= boundary_max_x) && !(boundary_min_z <= cord_z && cord_z <= boundary_max_z)){
			if (boundary_min_z - ball.getRadius() <= cord_z && cord_z <= this->m_z) {
				cord_z = boundary_min_z - ball.getRadius() - COR_VAL;
			}
			else {
				cord_z = boundary_max_z + ball.getRadius() + COR_VAL;
			}
			ball.setPower(ball.getVelocity_X(), -ball.getVelocity_Z());
		}

		if (!(boundary_min_x <= cord_x && cord_x <= boundary_max_x) && (boundary_min_z <= cord_z && cord_z <= boundary_max_z)) {
			if (boundary_min_x - ball.getRadius() <= cord_x && cord_x <= this->m_x) {
				cord_x = boundary_min_x - ball.getRadius() - COR_VAL;
			}
			else {
				cord_x = boundary_max_x + ball.getRadius() + COR_VAL;
			}
			ball.setPower(-ball.getVelocity_X(), ball.getVelocity_Z());
		}

		if (ball.isControlBall()) {
			ball.setPower(0.0, 0.0);
		}

		ball.setCenter(cord_x, ball.getCenter().y, cord_z);
	}
}

void CWall::setPosition(float x, float y, float z)
{
	D3DXMATRIX m;
	this->m_x = x;
	this->m_z = y;
	this->m_z = z;

	D3DXMatrixTranslation(&m, x, y, z);
	setLocalTransform(m);
}

D3DXVECTOR3 CWall::getCenter(void) const
{
	D3DXVECTOR3 org(m_x, 0, m_z);
	return org;
}
