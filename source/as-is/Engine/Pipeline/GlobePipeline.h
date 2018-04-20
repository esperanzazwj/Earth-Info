#pragma once
#include "../Pipeline.h"
#include "../PreDefine.h"
#include <vector>
#include "../../oceanInfo/Camera/worldCamera.h"
#include "../CameraControl.h"

using namespace HW;

struct RayCastedGlobeEffect : PipelineEffect
{
public:
	RayCastedGlobeEffect(VirtualGlobeScene::MomentumCamera *main_camera=NULL, Ellipsoid *earthshape=NULL, float earthRadius=0)
		:main_camera(main_camera), earthshape(earthshape), earthRadius(earthRadius)
    {
        this->name = "RayCastedGlobe";
        globeInteractive = new GlobeInteractive(main_camera, earthshape);
    }
	~RayCastedGlobeEffect()
    {
        if (globeInteractive != NULL)
            delete globeInteractive;
    }
    virtual void Init();
    virtual void Update();
    virtual void GetInputPasses(vector<Pass*>&, vector<pair<Pass*, Pass*>>&, vector<pair<Texture*&, Texture*&>>&);

    string in_scenename;
    string in_cameraname;
private:
    RenderTarget * rt_out{};
	Pass* RayCastedGlobe_pass{};
	//Camera Controller
	GlobeInteractive * globeInteractive;
	VirtualGlobeScene::MomentumCamera *main_camera;
    Ellipsoid *earthshape;
	float earthRadius;
};

struct GlobeEffect: PipelineEffect
{
	GlobeEffect() { this->name = "globe"; }
	virtual void Init();
	virtual void Update();
	virtual void GetInputPasses(vector<Pass*>&, vector<pair<Pass*, Pass*>>&, vector<pair<Texture*&, Texture*&>>&);

	string in_scenename;
	string in_cameraname;

private:
	RenderTarget* rt_out{};
    Pass* globe_pass{};
};

struct GlobePipeline: Pipeline
{
public:
	GlobePipeline(VirtualGlobeScene::MomentumCamera *main_camera=NULL, Ellipsoid *earthshape=NULL, float earthRadius=0)
		:main_camera(main_camera), earthshape(earthshape), earthRadius(earthRadius), fx_main(NULL), fx_main_raycasted(NULL)
    {}
	virtual void Init();
	virtual void Render();
private:
	GlobeEffect* fx_main;//obsolete
    RayCastedGlobeEffect * fx_main_raycasted;
	float earthRadius;
	VirtualGlobeScene::MomentumCamera *main_camera;
    Ellipsoid *earthshape;
};

