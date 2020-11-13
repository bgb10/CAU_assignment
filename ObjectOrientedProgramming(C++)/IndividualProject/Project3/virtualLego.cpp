////////////////////////////////////////////////////////////////////////////////
//
// File: virtualLego.cpp
//
// Original Author: 박창현 Chang-hyeon Park, 
// Modified by Bong-Soo Sohn and Dong-Jun Kim
// 
// Originally programmed for Virtual LEGO. 
// Modified later to program for Virtual Billiard.
//        
////////////////////////////////////////////////////////////////////////////////

#include "virtualLego.h"

#define brickCount 52
#define wallCount 4

// There are four balls
// initialize the position (coordinate) of each ball (ball0 ~ ball3)
float spherePos[brickCount][2] = {};
// initialize the color of each ball (ball0 ~ ball3)
D3DXCOLOR sphereColor[brickCount] = {};

IDirect3DDevice9* Device = NULL;

// window size
const int Width = 1024;
const int Height = 768;

// game start
bool game_start = false;

// -----------------------------------------------------------------------------
// Transform matrices
// -----------------------------------------------------------------------------
D3DXMATRIX g_mWorld;
D3DXMATRIX g_mView;
D3DXMATRIX g_mProj;

// -----------------------------------------------------------------------------
// Global variables
// -----------------------------------------------------------------------------
CWall	g_legoPlane;
CWall	g_legowall[wallCount];
CSphere	g_sphere[brickCount];
CSphere	g_controlball;
CSphere g_moveball;
CLight	g_light;

// -----------------------------------------------------------------------------
// Functions
// -----------------------------------------------------------------------------


void destroyAllLegoBlock(void)
{
}

// initialization
bool Setup()
{
	int i;

	D3DXMatrixIdentity(&g_mWorld);
	D3DXMatrixIdentity(&g_mView);
	D3DXMatrixIdentity(&g_mProj);

	// create plane and set the position
	if (false == g_legoPlane.create(Device, -1, -1, 9, 0.03f, 6, d3d::GREEN)) return false;
	g_legoPlane.setPosition(0.0f, -0.0006f / 5, 0.0f);

	// create walls and set the position. note that there are four walls
	if (false == g_legowall[0].create(Device, -1, -1, 9, 0.3f, 0.12f, d3d::DARKRED)) return false;
	g_legowall[0].setPosition(0.0f, 0.12f, 3.06f);
	if (false == g_legowall[1].create(Device, -1, -1, 9, 0.3f, 0.12f, d3d::DARKRED)) return false;
	g_legowall[1].setPosition(0.0f, 0.12f, -3.06f);
	if (false == g_legowall[2].create(Device, -1, -1, 0.12f, 0.3f, 6.24f, d3d::DARKRED)) return false;
	g_legowall[2].setPosition(4.56f, 0.12f, 0.0f);
	if (false == g_legowall[3].create(Device, -1, -1, 0.12f, 0.3f, 6.24f, d3d::DARKRED)) return false;
	g_legowall[3].setPosition(-4.56f, 0.12f, 0.0f);

	// set position and color for the bricks
	// set position
	for (int layer = 0; layer < 4; layer++) {
		for (int nth = 0; nth < 13; nth++) {
			spherePos[layer * 13 + nth][0] = 0.9f + (-0.9f * layer);
			spherePos[layer * 13 + nth][1] = 0.43f * (nth - 6);
		}
	}
	// set color
	for (int i = 0; i < brickCount; i++) {
		sphereColor[i] = d3d::YELLOW;
	}

	// create balls and set the position
	for (i = 0; i < brickCount; i++) {
		if (false == g_sphere[i].create(Device, sphereColor[i])) return false;
		g_sphere[i].setCenter(spherePos[i][0], (float)M_RADIUS, spherePos[i][1]);
		g_sphere[i].setPower(0, 0);
	}

	// create controlball for control direction of moveball
	if (false == g_controlball.create(Device, d3d::BLUE)) return false;
	g_controlball.setCenter(4.5f - M_RADIUS, (float)M_RADIUS, .0f);
	g_controlball.setControlBall(true);

	// create moveball for destroy bricks
	if (false == g_moveball.create(Device, d3d::WHITE)) return false;
	g_moveball.setCenter(4.5f - 3 * M_RADIUS, (float)M_RADIUS, .0f);

	// light setting 
	D3DLIGHT9 lit;
	::ZeroMemory(&lit, sizeof(lit));
	lit.Type = D3DLIGHT_POINT;
	lit.Diffuse = d3d::WHITE;
	lit.Specular = d3d::WHITE * 0.9f;
	lit.Ambient = d3d::WHITE * 0.9f;
	lit.Position = D3DXVECTOR3(0.0f, 6.0f, 0.0f);
	lit.Range = 100.0f;
	lit.Attenuation0 = 0.0f;
	lit.Attenuation1 = 0.7f;
	lit.Attenuation2 = 0.0f;
	if (false == g_light.create(Device, lit))
		return false;

	// Position and aim the camera.
	D3DXVECTOR3 pos(9.0f, 9.0f, 0.0f);
	D3DXVECTOR3 target(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 up(0.0f, 2.0f, 0.0f);
	D3DXMatrixLookAtLH(&g_mView, &pos, &target, &up);
	Device->SetTransform(D3DTS_VIEW, &g_mView);

	// Set the projection matrix.
	D3DXMatrixPerspectiveFovLH(&g_mProj, D3DX_PI / 4,
		(float)Width / (float)Height, 1.0f, 100.0f);
	Device->SetTransform(D3DTS_PROJECTION, &g_mProj);

	// Set render states.
	Device->SetRenderState(D3DRS_LIGHTING, TRUE);
	Device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);
	Device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	g_light.setLight(Device, g_mWorld);
	return true;
}

void Cleanup(void)
{
	g_legoPlane.destroy();
	for (int i = 0; i < wallCount; i++) {
		g_legowall[i].destroy();
	}
	destroyAllLegoBlock();
	g_light.destroy();
}


// timeDelta represents the time between the current image frame and the last image frame.
// the distance of moving balls should be "velocity * timeDelta"
bool Display(float timeDelta)
{
	int i = 0;
	int j = 0;


	if (Device)
	{
		Device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0x00afafaf, 1.0f, 0);
		Device->BeginScene();

		// update the position of each ball. during update, check whether each ball hit by walls.
		for (i = 0; i < brickCount; i++) {
			//g_sphere[i].ballUpdate(timeDelta);
			for (j = 0; j < wallCount; j++) { g_legowall[j].hitBy(g_moveball); }
		}

		// Modified: update the position of moveball. Check whether any two balls hit together and update the direction of moveball.
		g_moveball.ballUpdate(timeDelta);
		for (i = 0; i < brickCount; i++) {
			g_sphere[i].hitBy(g_moveball);
		}
		g_moveball.ballUpdate(timeDelta);

		// Added: update the position of controlball. Check whether legowall hit by controlball.
		g_controlball.ballUpdate(timeDelta);
		for (i = 0; i < wallCount; i++) {
			g_legowall[i].hitBy(g_controlball);
		}

		// Added: update the position of moveball. Check whether controlball hit by moveball.
		g_moveball.ballUpdate(timeDelta);
		g_controlball.hitBy(g_moveball);

		// If game not started, moveball follows controlball
		if(!game_start) g_moveball.setCenter(g_controlball.getCenter().x - 2 * M_RADIUS, g_controlball.getCenter().y, g_controlball.getCenter().z);

		// draw plane, walls, and spheres
		g_legoPlane.draw(Device, g_mWorld);
		for (i = 0; i < wallCount; i++) {
			g_legowall[i].draw(Device, g_mWorld);
		}

		for (int i = 0; i < brickCount; i++) {
			g_sphere[i].draw(Device, g_mWorld);
		}
		g_controlball.draw(Device, g_mWorld);
		g_moveball.draw(Device, g_mWorld);
		g_light.draw(Device);

		Device->EndScene();
		Device->Present(0, 0, 0, 0);
		Device->SetTexture(0, NULL);
	}
	return true;
}

LRESULT CALLBACK d3d::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool wire = false;
	static bool isReset = true;
	static int old_x = 0;
	static int old_y = 0;
	static enum { WORLD_MOVE, LIGHT_MOVE, BLOCK_MOVE } move = WORLD_MOVE;

	switch (msg) {
	case WM_DESTROY:
	{
		::PostQuitMessage(0);
		break;
	}
	case WM_KEYDOWN:
	{
		switch (wParam) {
		case VK_ESCAPE:
			::DestroyWindow(hwnd);
			break;
		case VK_RETURN:
			if (NULL != Device) {
				wire = !wire;
				Device->SetRenderState(D3DRS_FILLMODE,
					(wire ? D3DFILL_WIREFRAME : D3DFILL_SOLID));
			}
			break;
		case VK_SPACE:
			//D3DXVECTOR3 targetpos = g_controlball.getCenter();
			//D3DXVECTOR3	whitepos = g_moveball.getCenter();
			//double theta = acos(sqrt(pow(targetpos.x - whitepos.x, 2)) / sqrt(pow(targetpos.x - whitepos.x, 2) +
			//	pow(targetpos.z - whitepos.z, 2)));		// 기본 1 사분면
			//if (targetpos.z - whitepos.z <= 0 && targetpos.x - whitepos.x >= 0) { theta = -theta; }	//4 사분면
			//if (targetpos.z - whitepos.z >= 0 && targetpos.x - whitepos.x <= 0) { theta = PI - theta; } //2 사분면
			//if (targetpos.z - whitepos.z <= 0 && targetpos.x - whitepos.x <= 0) { theta = PI + theta; } // 3 사분면
			//double distance = sqrt(pow(targetpos.x - whitepos.x, 2) + pow(targetpos.z - whitepos.z, 2));
			//g_moveball.setPower(distance * cos(theta), distance * sin(theta));
			//break;
			if (!game_start) {
				game_start = true;

				g_moveball.setPower(1.0f, 0.0f);
			}
			break;
		}
		break;
	}

	case WM_MOUSEMOVE:
	{
		int new_x = LOWORD(lParam);
		int new_y = HIWORD(lParam);
		float dx;
		float dy;

		if (LOWORD(wParam) & MK_RBUTTON) {

			dx = (old_x - new_x);// * 0.01f;
			dy = (old_y - new_y);// * 0.01f;

			D3DXVECTOR3 coord3d = g_controlball.getCenter();
			g_controlball.setCenter(coord3d.x, coord3d.y, coord3d.z + dx * (-0.01f));
			old_x = new_x;
			old_y = new_y;

			move = WORLD_MOVE;
		}


		//if (LOWORD(wParam) & MK_LBUTTON) {

		//	if (isReset) {
		//		isReset = false;
		//	}
		//	else {
		//		D3DXVECTOR3 vDist;
		//		D3DXVECTOR3 vTrans;
		//		D3DXMATRIX mTrans;
		//		D3DXMATRIX mX;
		//		D3DXMATRIX mY;

		//		switch (move) {
		//		case WORLD_MOVE:
		//			/*dx = (old_x - new_x) * 0.01f;
		//			dy = (old_y - new_y) * 0.01f;
		//			D3DXMatrixRotationY(&mX, dx);
		//			D3DXMatrixRotationX(&mY, dy);
		//			g_mWorld = g_mWorld * mX * mY;*/
		//			break;
		//		}
		//	}

		//	old_x = new_x;
		//	old_y = new_y;

		//}
		//else {
		//	isReset = true;

		//	if (LOWORD(wParam) & MK_RBUTTON) {
		//		dx = (old_x - new_x);// * 0.01f;
		//		dy = (old_y - new_y);// * 0.01f;

		//		D3DXVECTOR3 coord3d = g_controlball.getCenter();
		//		g_controlball.setCenter(coord3d.x, coord3d.y, coord3d.z + dy * (0.1f));
		//	}
		//	old_x = new_x;
		//	old_y = new_y;

		//	move = WORLD_MOVE;
		//}

		break;
	}
	}

	return ::DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hinstance,
	HINSTANCE prevInstance,
	PSTR cmdLine,
	int showCmd)
{
	srand(static_cast<unsigned int>(time(NULL)));

	if (!d3d::InitD3D(hinstance,
		Width, Height, true, D3DDEVTYPE_HAL, &Device))
	{
		::MessageBox(0, "InitD3D() - FAILED", 0, 0);
		return 0;
	}

	if (!Setup())
	{
		::MessageBox(0, "Setup() - FAILED", 0, 0);
		return 0;
	}

	d3d::EnterMsgLoop(Display); //Display 이름 자체를 주면 함수 포인터를 주는 격이다.

	Cleanup();

	Device->Release();

	return 0;
}