#include "game.h"
#include "stb_image.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#define UP	(-256 * 4)
#define DOWN	(256 * 4)
#define RIGHT	4
#define LEFT	-4

static void printMat(const glm::mat4 mat)
{
	std::cout<<" matrix:"<<std::endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			std::cout<< mat[j][i]<<" ";
		std::cout<<std::endl;
	}
}

Game::Game() : Scene()
{
}

Game::Game(float angle ,float relationWH, float near1, float far1) : Scene(angle,relationWH,near1,far1)
{ 	
}

void Game::Init()
{		

	AddShader("../../res/shaders/pickingShader");	
	AddShader("../../res/shaders/basicShader");
	
	const std::string& fileName = "../../res/textures/lena256.jpg";
	//unsigned char* floydData = Floyd(fileName);
	unsigned char* halftoneData = Halftone(fileName);
	//unsigned char** data = Generate2DMatrix(halftoneData, 256); 
	//unsigned char* edgeDetectionData = EdgeDetection(fileName);
	//AddTexture(fileName, false);
	//AddTexture(256,256,floydData);
	AddTexture(512,512,halftoneData);
	//AddTexture(256,256,edgeDetectionData);

	AddShape(Plane,-1,TRIANGLES);
	
	pickedShape = 0;
	
	SetShapeTex(0,0);
	MoveCamera(0,zTranslate,10);
	pickedShape = -1;
	
	//ReadPixel(); //uncomment when you are reading from the z-buffer
}

unsigned char* Game::Floyd(const std::string& fileName)
{
	int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

    int i = 0;
    for(int i=0; i < 256 * 255 * 4; i = i+4)
	{
		int P = (data[i]/16) * 16;
        double e = data[i] - P;
		//R
        data[i] = P;
        data[i + DOWN] = data[i + DOWN] + (e * 7/16);
        data[i + RIGHT + UP] = data[i + RIGHT + UP] + (e * 3/16);
        data[i + RIGHT] = data[i + RIGHT] + (e * 5/16);
        data[i + RIGHT + DOWN] = data[i + RIGHT + DOWN] + (e * 1/16);
		//G
		data[i+1] = P;
        data[i+1 + DOWN] = data[i+1 + DOWN] + (e * 7/16);
        data[i+1 + RIGHT + UP] = data[i+1 + RIGHT + UP] + (e * 3/16);
        data[i+1 + RIGHT] = data[i+1 + RIGHT] + (e * 5/16);
        data[i+1 + RIGHT + DOWN] = data[i+1 + RIGHT + DOWN] + (e * 1/16);
		//B
		data[i+2] = P;
        data[i+2 + DOWN] = data[i+2 + DOWN] + (e * 7/16);
        data[i+2 + RIGHT + UP] = data[i+2 + RIGHT + UP] + (e * 3/16);
        data[i+2 + RIGHT] = data[i+2 + RIGHT] + (e * 5/16);
        data[i+2 + RIGHT + DOWN] = data[i+2 + RIGHT + DOWN] + (e * 1/16);
		//Dont change Alpha (i+3)
	}

	return data;
}

unsigned char* Game::Halftone(const std::string& fileName)
{
	int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
	unsigned char** data2D = Generate2DMatrix(data, 256);

	//initialize new 2d matrix
	unsigned char** newData2D = new unsigned char*[256*2];
	for(int i=0; i<256*2; i++)
	{
		newData2D[i] = new unsigned char[256*2*4];
	}

	for(int i=0; i<256; i++)
	{
		for(int j=0; j<256*4; j=j+4)
		{
			if(data2D[i][j] <= 51)
			{
				//R
				newData2D[2*i][2*j] = 0;
				newData2D[2*i + 1][2*j] = 0; //Down
				newData2D[2*i][2*j + 4] = 0; //Right
				newData2D[2*i + 1][2*j + 4] = 0;//DownRight

				//G
				newData2D[2*i][2*j + 1] = 0;
				newData2D[2*i + 1][2*j + 1] = 0; //Down
				newData2D[2*i][2*j + 4 + 1] = 0; //Right
				newData2D[2*i + 1][2*j + 4 + 1] = 0;//DownRight

				//B
				newData2D[2*i][2*j + 2] = 0;
				newData2D[2*i + 1][2*j + 2] = 0; //Down
				newData2D[2*i][2*j + 4 + 2] = 0; //Right
				newData2D[2*i + 1][2*j + 4 + 2] = 0;//DownRight
			}
			else if(data2D[i][j] <= 102)
			{
				//R
				newData2D[2*i][2*j] = 0;
				newData2D[2*i + 1][2*j] = 255; //Down
				newData2D[2*i][2*j + 4] = 0; //Right
				newData2D[2*i + 1][2*j + 4] = 0;//DownRight

				//G
				newData2D[2*i][2*j + 1] = 0;
				newData2D[2*i + 1][2*j + 1] = 255; //Down
				newData2D[2*i][2*j + 4 + 1] = 0; //Right
				newData2D[2*i + 1][2*j + 4 + 1] = 0;//DownRight

				//B
				newData2D[2*i][2*j + 2] = 0;
				newData2D[2*i + 1][2*j + 2] = 255; //Down
				newData2D[2*i][2*j + 4 + 2] = 0; //Right
				newData2D[2*i + 1][2*j + 4 + 2] = 0;//DownRight
			}
			else if (data2D[i][j] <= 153)
			{
				//R
				newData2D[2*i][2*j] = 0;
				newData2D[2*i + 1][2*j] = 255; //Down
				newData2D[2*i][2*j + 4] = 255; //Right
				newData2D[2*i + 1][2*j + 4] = 0;//DownRight

				//G
				newData2D[2*i][2*j + 1] = 0;
				newData2D[2*i + 1][2*j + 1] = 255; //Down
				newData2D[2*i][2*j + 4 + 1] = 255; //Right
				newData2D[2*i + 1][2*j + 4 + 1] = 0;//DownRight

				//B
				newData2D[2*i][2*j + 2] = 0;
				newData2D[2*i + 1][2*j + 2] = 255; //Down
				newData2D[2*i][2*j + 4 + 2] = 255; //Right
				newData2D[2*i + 1][2*j + 4 + 2] = 0;//DownRight
			}
			else if (data2D[i][j] <= 204)
			{
				//R
				newData2D[2*i][2*j] = 0;
				newData2D[2*i + 1][2*j] = 255; //Down
				newData2D[2*i][2*j + 4] = 255; //Right
				newData2D[2*i + 1][2*j + 4] = 255;//DownRight

				//G
				newData2D[2*i][2*j + 1] = 0;
				newData2D[2*i + 1][2*j + 1] = 255; //Down
				newData2D[2*i][2*j + 4 + 1] = 255; //Right
				newData2D[2*i + 1][2*j + 4 + 1] = 255;//DownRight

				//B
				newData2D[2*i][2*j + 2] = 0;
				newData2D[2*i + 1][2*j + 2] = 255; //Down
				newData2D[2*i][2*j + 4 + 2] = 255; //Right
				newData2D[2*i + 1][2*j + 4 + 2] = 255;//DownRight
			}
			else
			{
				//R
				newData2D[2*i][2*j] = 255;
				newData2D[2*i + 1][2*j] = 255; //Down
				newData2D[2*i][2*j + 4] = 255; //Right
				newData2D[2*i + 1][2*j + 4] = 255;//DownRight

				//G
				newData2D[2*i][2*j + 1] = 255;
				newData2D[2*i + 1][2*j + 1] = 255; //Down
				newData2D[2*i][2*j + 4 + 1] = 255; //Right
				newData2D[2*i + 1][2*j + 4 + 1] = 255;//DownRight

				//B
				newData2D[2*i][2*j + 2] = 255;
				newData2D[2*i + 1][2*j + 2] = 255; //Down
				newData2D[2*i][2*j + 4 + 2] = 255; //Right
				newData2D[2*i + 1][2*j + 4 + 2] = 255;//DownRight
			}
		}
	}
	unsigned char* newData = Generate1DMatrix(newData2D, 512);
	return newData;
}


unsigned char* Game::EdgeDetection(const std::string& fileName)
{
	int width, height, numComponents;
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
	
    // int i =0;
    // for(int i=0; i < 256 * 256 * 4; i++)
	// {
	// 	data[i] = (data[i] / 16) * 16;
	// }

	return data;
}

unsigned char** Game::Generate2DMatrix(unsigned char* data, int size)
{
	unsigned char** res = new unsigned char*[size];
	for(int i=0; i<size; i++)
	{
		res[i] = new unsigned char[size*4];
	}

	int counter = 0;
	for(int i=0; i < size; i++)
	{
		for(int j=0; j <size*4; j++)
		{
			res[i][j] = data[counter];
			counter++;
		}
	}

	return res;
}

unsigned char* Game::Generate1DMatrix(unsigned char** data2D, int size)
{
	unsigned char* res = new unsigned char[size*size*4];
	int counter = 0;
	for(int i=0; i < size; i++)
	{
		for(int j=0; j <size*4; j++)
		{
			res[counter] = data2D[i][j];
			counter++;
		}
	}

	return res;
}


void Game::Update(const glm::mat4 &MVP,const glm::mat4 &Model,const int  shaderIndx)
{
	Shader *s = shaders[shaderIndx];
	int r = ((pickedShape+1) & 0x000000FF) >>  0;
	int g = ((pickedShape+1) & 0x0000FF00) >>  8;
	int b = ((pickedShape+1) & 0x00FF0000) >> 16;
	s->Bind();
	s->SetUniformMat4f("MVP", MVP);
	s->SetUniformMat4f("Normal",Model);
	s->SetUniform4f("lightDirection", 0.0f , 0.0f, -1.0f, 0.0f);
	if(shaderIndx == 0)
		s->SetUniform4f("lightColor",r/255.0f, g/255.0f, b/255.0f,1.0f);
	else 
		s->SetUniform4f("lightColor",0.7f,0.8f,0.1f,1.0f);
	s->Unbind();
}

void Game::WhenRotate()
{
}

void Game::WhenTranslate()
{
}

void Game::Motion()
{
	if(isActive)
	{
	}
}

Game::~Game(void)
{
}
