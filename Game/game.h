#pragma once
#include "scene.h"

class Game : public Scene
{
public:
	
	Game();
	Game(float angle,float relationWH,float near, float far);
	void Init();
	unsigned char** Game::Generate2DMatrix(unsigned char* data, int size);
	unsigned char* Game::Generate1DMatrix(unsigned char** data2D, int size);
	unsigned char* Game::Halftone(const std::string& fileName);
	unsigned char* Game::Floyd(const std::string& fileName);
	unsigned char* Game::EdgeDetection(const std::string& fileName);
	void Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx);
	void ControlPointUpdate();
	void WhenRotate();
	void WhenTranslate();
	void Motion();
	~Game(void);
};

