#ifndef __CWALL__
#define __CWALL__

#include "d3dUtility.h"
#include "CSphere.h"

// -----------------------------------------------------------------------------
// CWall class definition
// -----------------------------------------------------------------------------

#define COR_VAL 0.01f //오차 보정값

class CWall {

private:

    float					m_x;
    float					m_z;
    float                   m_width;
    float                   m_depth;
    float					m_height;

public:
    CWall(void);
    ~CWall(void);
public:
    bool create(IDirect3DDevice9* pDevice, float ix, float iz, float iwidth, float iheight, float idepth, D3DXCOLOR color = d3d::WHITE);
    void destroy(void);
    void draw(IDirect3DDevice9* pDevice, const D3DXMATRIX& mWorld);

    bool hasIntersected(CSphere& ball);

    void hitBy(CSphere& ball);

    void setPosition(float x, float y, float z);

    float getHeight(void) const { return m_height; }
    float getWidth(void) const { return m_width; }
    float getDepth(void) const { return m_depth; }
    D3DXVECTOR3 getCenter(void) const;

private:
    void setLocalTransform(const D3DXMATRIX& mLocal) { m_mLocal = mLocal; }

    D3DXMATRIX              m_mLocal;
    D3DMATERIAL9            m_mtrl;
    ID3DXMesh* m_pBoundMesh;
};

#endif