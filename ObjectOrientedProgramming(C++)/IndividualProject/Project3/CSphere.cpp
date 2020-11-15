// -----------------------------------------------------------------------------
// CSphere class definition
// -----------------------------------------------------------------------------

#include "CSphere.h"

CSphere::CSphere(void)
{
	D3DXMatrixIdentity(&m_mLocal);
	ZeroMemory(&m_mtrl, sizeof(m_mtrl));
	m_radius = 0;
	m_velocity_x = 0;
	m_velocity_z = 0;
	m_pSphereMesh = NULL;
}
CSphere::~CSphere(void) {}

bool CSphere::create(IDirect3DDevice9* pDevice, float radius, D3DXCOLOR color)
{
	if (NULL == pDevice)
		return false;

	m_mtrl.Ambient = color;
	m_mtrl.Diffuse = color;
	m_mtrl.Specular = color;
	m_mtrl.Emissive = d3d::BLACK;
	m_mtrl.Power = 5.0f;

	m_radius = radius;

	if (FAILED(D3DXCreateSphere(pDevice, radius, 50, 50, &m_pSphereMesh, NULL)))
		return false;
	return true;
}

void CSphere::destroy(void)
{
	if (m_pSphereMesh != NULL) {
		m_pSphereMesh->Release();
		m_pSphereMesh = NULL;
	}
}

void CSphere::draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld)
{
	if (NULL == pDevice)
		return;
	pDevice->SetTransform(D3DTS_WORLD, &mWorld);
	pDevice->MultiplyTransform(D3DTS_WORLD, &m_mLocal);
	pDevice->SetMaterial(&m_mtrl);
	m_pSphereMesh->DrawSubset(0);
}

bool CSphere::hasIntersected(CSphere& ball)
{
	// Insert your code here.
	D3DXVECTOR3 distance_vector = this->getCenter() - ball.getCenter();

	float distance_scala;
	distance_scala = sqrt(distance_vector.x * distance_vector.x + distance_vector.y * distance_vector.y + distance_vector.z * distance_vector.z);
	
	//Intersected
	if (distance_scala <= this->getRadius() + ball.getRadius()) {
		return true;
	}

	//Not Intersected
	return false;
}

void CSphere::hitBy(CSphere& ball)
{
	// Insert your code here.
	if (hasIntersected(ball)) {
		//충돌 구현

		//moveball을 튕기기(맞은 속도가 중요한게 아니라, 맞은 방향이 중요하다, 벡터 차만큼 이동하도록 한다)

		float delta_x = ball.getCenter().x - this->getCenter().x;
		float delta_z = ball.getCenter().z - this->getCenter().z;
		float multiple;

		float velocity_vector_scala = sqrt(ball.getVelocity_X() * ball.getVelocity_X() + ball.getVelocity_Z() * ball.getVelocity_Z());
		float distance_vector_scala = sqrt(delta_x * delta_x + delta_z * delta_z); //방향 벡터
		multiple = velocity_vector_scala / distance_vector_scala;

		float new_velocity_x = multiple * delta_x;
		float new_velocity_z = multiple * delta_z;

		ball.setPower(new_velocity_x, new_velocity_z);

		// this가 controlball이면, ball을 사라지게 하지 않기
		if (!this->isControlBall()) {
			this->setCenter(-10.0f, -10.0f, 0.0f);
		}
	}
}

void CSphere::ballUpdate(float timeDiff)
{
	const float TIME_SCALE = 3.3;
	D3DXVECTOR3 cord = this->getCenter();
	double vx = abs(this->getVelocity_X());
	double vz = abs(this->getVelocity_Z());

	if (vx > 0.01 || vz > 0.01)
	{
		float tX = cord.x + TIME_SCALE * timeDiff * getVelocity_X();
		float tZ = cord.z + TIME_SCALE * timeDiff * getVelocity_Z();

		//correction of position of ball
		/*Please uncomment this part because this correction of ball position is necessary when a ball collides with a wall
		if (tX >= (4.5 - M_RADIUS)) {
			tX = 4.5 - M_RADIUS;
		}
		else if (tX <= (-4.5 + M_RADIUS)) {
			tX = -4.5 + M_RADIUS;
		}
		else if (tZ <= (-3 + M_RADIUS)) {
			tZ = -3 + M_RADIUS;
		}
		else if (tZ >= (3 - M_RADIUS)) {
			tZ = 3 - M_RADIUS;
		}*/
		this->setCenter(tX, cord.y, tZ);
	}
	else { this->setPower(0, 0); }
	//Decrease speed
	//this->setPower(this->getVelocity_X() * DECREASE_RATE, this->getVelocity_Z() * DECREASE_RATE);
	/*double rate = 1 - (1 - DECREASE_RATE) * timeDiff * 400;
	if (rate < 0)
		rate = 0;
	this->setPower(getVelocity_X() * rate, getVelocity_Z() * rate);*/
}

void CSphere::setPower(double vx, double vz)
{
	this->m_velocity_x = vx;
	this->m_velocity_z = vz;
}

void CSphere::setCenter(float x, float y, float z)
{
	D3DXMATRIX m;
	center_x = x;	center_y = y;	center_z = z;
	D3DXMatrixTranslation(&m, x, y, z);
	setLocalTransform(m);
}

D3DXVECTOR3 CSphere::getCenter(void) const
{
	D3DXVECTOR3 org(center_x, center_y, center_z);
	return org;
}

