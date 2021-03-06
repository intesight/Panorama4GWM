#ifndef _PANORAMA3D_SCENE_H__
#define _PANORAMA3D_SCENE_H__
#include "OGLEGL.h"
#include "OGLWin.h"
#include "UnMergedPanorama3D.h"
#include "MergedPanorama3D.h"
#include "TrackBall.h"
#include "ModelRender.h"
#include "Model3D.h"
#include "PanoramaParam.h"
#include "MyMatrix.h"

#include <vector>
#include <glm/glm.hpp>

class Panorama3DScene
{
public:
	Panorama3DScene();
	~Panorama3DScene(void);
public:
    void setNextCameraViewByThetaPhei(float theta,float phei,int motionLen);
	void draw(float* delta, bool isFullScreen = true);
	void initDrawScene(GLuint *imageTextureId);
	void setPanorama3dParam(float theta,float phei,bool m_forceReload = false);
    TrackBall *getTrackBall(){return m_trackBall;}
    void setCurCameraPosition(int position);
    void setLocalLuminParam(float *luminParam);
    void setGlobalLuminParam(float *luminParam);
    bool isAnimationCompleted();
    void draw3DScene(float* delta);
    MyMatrix getCameraViewMatrix();

	enum ViewMode { VIEW_MODE_TRACKBALL = 0, VIEW_MODE_PRESET = 1, VIEW_MODE_DIRECT = 2 };
	void setViewMode(ViewMode mode) { viewMode = mode; }
	void setViewMatrix(const glm::mat4& m) { viewMatrix = m; }


	enum ViewPreset { BLIND_LEFT_A = 0, BLIND_RIGHT_A, BLIND_LEFT_B, BLIND_RIGHT_B, NUM_VIEW_PRESETS };
	void setViewPreset(int i) { viewMatrix = viewPresets[i]; }

	inline void setViewport(int x, int y, int width, int height)
	{
		viewX = x;
		viewY = y;
		viewWidth = width;
		viewHeight = height;
	}


private:
    TrackBall *m_trackBall;
    int m_curCameraPosition;
private:
    float m_endPhei;
    float m_endTheta;
    float m_intervalPhei;
    float m_intervalTheta;
    bool m_isInit;
    bool m_isLoadVetex;
	MergedPanorama3D m_mergedPanorama3D[4];
	UnMergedPanorama3D m_unmergedPanorama3D[4];
	ModelRender m_modelRender;
	Model3D m_carModel;
	GLuint m_imageTextureID[4];
	GLuint m_warningTextureID[3];
	float m_panoramaMatrix[16];
	float m_modelMatrix[16];
	void drawPanorama3D(double x,double y,double width,double height, float* delta);

	int viewX, viewY, viewWidth, viewHeight;

	ViewMode viewMode;
	glm::mat4 viewMatrix;
	std::vector<glm::mat4> viewPresets;
	void loadViewPresets(std::vector<glm::mat4>& presets);
};
Panorama3DScene &getPanorama3DScene();
#endif // _PANORAMA3D_SCENE_H__
