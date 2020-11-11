#ifndef __CSSPHERE__
#define __CSSPHERE__

#include "d3dUtility.h"
#include <cmath>

// There are four balls
// initialize the position (coordinate) of each ball (ball0 ~ ball3)
const float spherePos[4][2] = { {-2.7f,0} , {+2.4f,0} , {3.3f,0} , {-2.7f,-0.9f} };
// initialize the color of each ball (ball0 ~ ball3)
const D3DXCOLOR sphereColor[4] = { d3d::RED, d3d::RED, d3d::YELLOW, d3d::WHITE };

#define M_RADIUS 0.21   // ball radius
#define PI 3.14159265
#define M_HEIGHT 0.01
#define DECREASE_RATE 0.9982


// -----------------------------------------------------------------------------
// CSphere class declaration
// -----------------------------------------------------------------------------

class CSphere {
private:
	float					center_x, center_y, center_z;
	float                   m_radius;
	float					m_velocity_x;
	float					m_velocity_z;

public:
	CSphere(void);
	~CSphere(void);

public:
	bool create(IDirect3DDevice9* pDevice, D3DXCOLOR color = d3d::WHITE);

	void destroy(void);

	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);

	bool hasIntersected(CSphere& ball);

	void hitBy(CSphere& ball);

	void ballUpdate(float timeDiff);

	double getVelocity_X() { return this->m_velocity_x; }
	double getVelocity_Z() { return this->m_velocity_z; }

	void setPower(double vx, double vz);

	void setCenter(float x, float y, float z);

	float getRadius(void)  const { return (float)(M_RADIUS); }
	const D3DXMATRIX& getLocalTransform(void) const { return m_mLocal; }
	void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
	D3DXVECTOR3 getCenter(void) const;

private:
	D3DXMATRIX              m_mLocal;
	D3DMATERIAL9            m_mtrl;
	ID3DXMesh* m_pSphereMesh;
};

#endif