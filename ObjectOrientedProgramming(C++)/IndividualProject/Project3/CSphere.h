#ifndef __CSSPHERE__
#define __CSSPHERE__

#include "d3dUtility.h"
#include <cmath>

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

	bool					isControlball = false;

public:
	CSphere(void);
	~CSphere(void);

public:
	bool create(IDirect3DDevice9* pDevice, float radius, D3DXCOLOR color = d3d::WHITE);

	void destroy(void);

	void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);

	bool hasIntersected(CSphere& ball);

	void hitBy(CSphere& ball);

	void ballUpdate(float timeDiff);

	double getVelocity_X() { return this->m_velocity_x; }
	double getVelocity_Z() { return this->m_velocity_z; }

	void setPower(double vx, double vz);

	void setCenter(float x, float y, float z);

	float getRadius(void)  const { return m_radius; }
	const D3DXMATRIX& getLocalTransform(void) const { return m_mLocal; }
	void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }
	D3DXVECTOR3 getCenter(void) const;

	void setControlBall(bool l_isControlball) { isControlball = l_isControlball; }
	bool isControlBall(void) { return isControlball; }

private:
	D3DXMATRIX              m_mLocal;
	D3DMATERIAL9            m_mtrl;
	ID3DXMesh* m_pSphereMesh;
};

#endif