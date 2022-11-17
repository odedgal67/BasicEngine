#include "game.h"
#include "stb_image.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>


#define UP	(-256 * 4)
#define DOWN	(256 * 4)
#define RIGHT	4
#define LEFT	-4


Game::Game() : Scene()
{
}

Game::Game(float angle ,float relationWH, float near1, float far1) : Scene(angle,relationWH,near1,far1)
{ 	
}

void Game::Init()
{		

	AddShader("../res/shaders/pickingShader");
	AddShader("../res/shaders/basicShader");
	
	const std::string& fileName = "../res/textures/lena256.jpg";
    AddTexture(fileName, false);
    unsigned char* edgeDetectionData = EdgeDetection(fileName);
    unsigned char* halftoneData = Halftone(fileName);

    unsigned char* floydData = Floyd(fileName);

	unsigned char** data = Generate2DMatrix(halftoneData, 256);

	AddShape(Plane,-1,TRIANGLES);
	AddShape(Plane,-1,TRIANGLES);
	AddShape(Plane,-1,TRIANGLES);
	AddShape(Plane,-1,TRIANGLES);

    for(int i=0;i<4;i++) {
        pickedShape = i;
        SetShapeTex(i, i);
    }
	pickedShape = 0;

	SetShapeTex(0,0);
	MoveCamera(0,zTranslate,10);
	pickedShape = -1;
	
	//ReadPixel(); //uncomment when you are reading from the z-buffer
}

void generateFloydFile(unsigned char* data, int size) {
    std::ofstream outfile;
    outfile.open("img6.txt", std::ofstream::out);
    for(int i=0;i<size;i++) {
        outfile << (int)data[i]/16;
        if (i < size- 1) {
            outfile << ",";
        }
    }
    outfile.close();
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
    AddTexture(width, height, data);
    generateFloydFile(data,256 * 255 * 4);
	return data;
}
void generateHalftoneFile(unsigned char* data, int size) {
    std::ofstream outfile;
    outfile.open("img5.txt", std::ofstream::out);
    for(int i=0;i<size;i++) {
        outfile << (int)data[i]/255;
        if (i < size- 1) {
            outfile << ",";
        }
    }
    outfile.close();
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

				//
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
    AddTexture(2 * width, 2 * height, newData);
    generateHalftoneFile(newData, 512*512*4);
	return newData;
}

unsigned char** generateClean2DMatrix(int size) {
    unsigned char** res = new unsigned char*[size];
    for(int i=0; i<size; i++)
    {
        res[i] = new unsigned char[size*4];
    }
    return res;
}
int** generateCleanInt2DMatrix(int size) {
    int** res = new int*[size];
    for(int i=0; i<size; i++)
    {
        res[i] = new int[size*4];
    }
    return res;
}
double** generateCleanDouble2DMatrix(int size) {
    double ** res = new double *[size];
    for(int i=0; i<size; i++)
    {
        res[i] = new double[size*4];
    }
    return res;
}

float calculateNewValue(unsigned char** data, int row, int col, glm::mat3 kernel, int size, int normalFactor) {
    float sum = 0;
    int adjacentRow;
    int adjacentCol;
    // diagonal up left
    adjacentRow = row - 1;
    adjacentCol = col - 4;
    if (adjacentCol >= 0 && adjacentRow >= 0) {
        sum += data[adjacentRow][adjacentCol] * kernel[0][0];
    }
    // left
    adjacentRow = row;
    adjacentCol = col - 4;
    if (adjacentCol >= 0 && adjacentRow >= 0) {
        sum += data[adjacentRow][adjacentCol]  * kernel[1][0];
    }
    // diagonal down left
    adjacentRow = row + 1;
    adjacentCol = col - 4;
    if (adjacentCol >= 0 && adjacentRow < size)
    {
        sum += data[adjacentRow][adjacentCol] * kernel[2][0];
    }
    // down
    adjacentRow = row + 1;
    adjacentCol = col;
    if (adjacentCol >= 0 && adjacentRow < size)
    {
        sum += data[adjacentRow][adjacentCol]  * kernel[2][1];
    }
    // diagonal down right
    adjacentRow = row + 1;
    adjacentCol = col + 4;
    if (adjacentCol <= size * 4 && adjacentRow < size)
    {
        sum += data[adjacentRow][adjacentCol]  * kernel[2][2];
    }
    // right
    adjacentRow = row;
    adjacentCol = col + 4;
    if (adjacentCol <= size * 4 && adjacentRow < size)
    {
        sum += data[adjacentRow][adjacentCol]  * kernel[1][2];
    }
    // diagonal upper right
    adjacentRow = row - 1;
    adjacentCol = col + 4;
    if (adjacentCol <= size * 4 && adjacentRow >= 0)
    {
        sum += data[adjacentRow][adjacentCol]  * kernel[0][2];
    }
    // up
    adjacentRow = row - 1;
    adjacentCol = col;
    if (adjacentCol >= 0 && adjacentRow >= 0)
    {
        sum += data[adjacentRow][adjacentCol]  * kernel[0][1];
    }
    sum += data[row][col] * kernel[1][1];
    return sum / normalFactor;
}

float* getCellNewValue(unsigned char** data, int row, int col, glm::mat3 kernel, float normalFactor, int size) {
    float res[3];
    res[0] = calculateNewValue(data, row, col, kernel, size, normalFactor);
    res[1] = calculateNewValue(data, row, col+1, kernel, size, normalFactor);
    res[2] = calculateNewValue(data, row, col+2, kernel, size, normalFactor);
    return res;
}

unsigned char** applyConvolution(unsigned char** data, glm::mat3 kernel, int size, float normalFactor) {
    unsigned char** res = generateClean2DMatrix(size);
    for(int i = 0; i < size; i++) {
        for(int j=0; j < size * 4; j+=4) {
            float* currCellNewValue = getCellNewValue(data, i, j, kernel, normalFactor, size);
            res[i][j] = currCellNewValue[0];
            res[i][j+1] = currCellNewValue[1];
            res[i][j+2] = currCellNewValue[2];
        }
    }
    return res;
}
int** applyGradient(unsigned char** data, glm::mat3 kernel, int size, float normalFactor) {
    int** res = generateCleanInt2DMatrix(size);
    for(int i = 0; i < size; i++) {
        for(int j=0; j < size * 4; j+=4) {
            float* currCellNewValue = getCellNewValue(data, i, j, kernel, normalFactor, size);
            res[i][j] = currCellNewValue[0];
            res[i][j+1] = currCellNewValue[1];
            res[i][j+2] = currCellNewValue[2];
        }
    }
    return res;
}

unsigned char** applyGausDerivative(unsigned char** data, int size) {
    auto kernel = glm::mat3(
            1,2,1,
            2,4,2,
            1,2,1
            );
    float normalFactor = 16.0;
    return applyConvolution(data, kernel, size, normalFactor);
}
int** getDirectionalGradient(unsigned char** data, int size, bool isX) {
    glm::mat3 kernel;
    if(isX){
        kernel = glm::mat3 (
                -1,0,1,
                -2,0,2,
                -1,0,1
                );
    }
    else {
        kernel = glm::mat3 (
                -1,-2,-1,
                0,0,0,
                1,2,1
                );
    }
    float normalFactor = 1.0; // no need to normalize here since sum is zero
    return applyGradient(data, kernel, size, normalFactor);
}

float* getGeneralGradientNewValue(int** gradX, int** gradY, int row, int col) {
    float res[3];
    res[0] = std::sqrt(std::pow(gradX[row][col], 2) + std::pow(gradY[row][col], 2));
    res[1] = std::sqrt(std::pow(gradX[row][col+1], 2) + std::pow(gradY[row][col+1], 2));
    res[2] = std::sqrt(std::pow(gradX[row][col+2], 2) + std::pow(gradY[row][col+2], 2));
    return res;
}

int** getGeneralGradient(int** gradX, int** gradY, int size) {
    int** res = generateCleanInt2DMatrix(size);
    for (int i=0;i<size;i++) {
        for(int j=0; j< size * 4; j+=4) {
            float* newValue = getGeneralGradientNewValue(gradX, gradY, i,j);
            res[i][j] = newValue[0];
            res[i][j+1] = newValue[1];
            res[i][j+2] = newValue[2];
        }
    }
    return res;
}

double radianToDegree(int radian) {
    double pi = 3.141592654;
    return radian * 180/pi + 180;
}
double* getGradientDirection(int** gradX, int** gradY, int row, int col) {
    double res[3];
    res[0] = radianToDegree(atan2(gradX[row][col], gradY[row][col]));
    res[1] = radianToDegree(atan2(gradX[row][col+1], gradY[row][col+1]));
    res[2] = radianToDegree(atan2(gradX[row][col+2], gradY[row][col+2]));
    return res;
}
double** getGradientDirection(int** gradX, int** gradY, int size) {
    double ** res = generateCleanDouble2DMatrix(size);
    for (int i=0;i<size;i++) {
        for(int j=0; j< size * 4; j+=4) {
            double* newValue = getGradientDirection(gradX, gradY, i,j);
            res[i][j] = newValue[0];
            res[i][j+1] = newValue[1];
            res[i][j+2] = newValue[2];
        }
    }
    return res;
}
int* getNegativeAndPositive(int** gradient,double angle, int row, int col) {
    double pi = 180;
    int res[2];
    if ((0 <= angle < pi/8) ||  (15*pi/8 <= angle <= 2*pi)) {
        res[0] = gradient[row][col-1];
        res[1] = gradient[row][col+1];
    }
    else if ((pi / 8 <= angle * 3 * pi / 8) || (9 * pi / 8 <= angle < 11 * pi / 8))
    {
        res[0] = gradient[row-1][col+1];
        res[1] = gradient[row+1][col-1];
    }
    else if ((3 * pi / 8 <= angle < 5 * pi / 8) || (11 * pi / 8 <= angle < 13 * pi / 8))
    {
        res[0] = gradient[row-1][col];
        res[1] = gradient[row+1][col];
    }
    else
    {
        res[0] = gradient[row-1][col-1];
        res[1] = gradient[row+1][col+1];
    }
    return res;
}

int* getSuppressed(int** gradient, double** gradAngle, int row, int col, int size) {
    int res[3] = {0, 0, 0};
    int negativeR,negativeG,negativeB,positiveR,positiveG,positiveB;
    double angleR,angleG,angleB;
    angleR = gradAngle[row][col];
    angleG = gradAngle[row][col + 1];
    angleB = gradAngle[row][col + 2];
    int* redNegativeAndPositive = getNegativeAndPositive(gradient,angleR,row,col);
    int* greenNegativeAndPositive = getNegativeAndPositive(gradient,angleG,row,col);
    int* blueNegativeAndPositive = getNegativeAndPositive(gradient,angleB,row,col);
    negativeR = redNegativeAndPositive[0];
    positiveR = redNegativeAndPositive[1];
    negativeG = greenNegativeAndPositive[0];
    positiveG = greenNegativeAndPositive[1];
    negativeB = blueNegativeAndPositive[0];
    positiveB = blueNegativeAndPositive[1];
    if (gradient[row][col] >= negativeR && gradient[row][col] >= positiveR) {
        res[0] = gradient[row][col];
    }
    if (gradient[row][col+1] >= negativeG && gradient[row][col+1] >= positiveG) {
        res[1] = gradient[row][col+1];
    }
    if (gradient[row][col+2] >= negativeB && gradient[row][col+2] >= positiveB) {
        res[2] = gradient[row][col+2];
    }
    return res;
}
int** applyNonMaximumSuppression(int** gradient, double** gradDirection, int size) {
    int** res = generateCleanInt2DMatrix(size);
    for(int i=0;i<size;i++) {
        for(int j=0;j<size*4;j+=4) {
            int* afterSuppression = getSuppressed(gradient,gradDirection,i,j,size);
            res[i][j] = afterSuppression[0];
            res[i][j+1] = afterSuppression[1];
            res[i][j+2] = afterSuppression[2];
        }
    }
    return res;
}
unsigned char* getThresholding(int** suppressed, int top, int row, int col) {
    unsigned char res[3] = {0,0,0};
    int suppressedR,suppressedG,suppressedB;
    suppressedR = suppressed[row][col];
    suppressedG = suppressed[row][col+1];
    suppressedB = suppressed[row][col+2];
    if (suppressedR >= top) {
        res[0] = 255;
    }
    if (suppressedG >= top) {
        res[1] = 255;
    }
    if (suppressedB >= top) {
        res[2] = 255;
    }
    return res;
}
unsigned char** thresholding(int** suppressed, int top, int bottom, int size) {
    unsigned char** res = generateClean2DMatrix(size);
    std::ofstream outfile;
    outfile.open("img4.txt", std::ofstream::out);
    for(int i=0;i<size;i++) {
        for(int j=0;j<size*4;j+=4) {
            unsigned char* afterThresholding = getThresholding(suppressed,top,i,j);
            res[i][j] = afterThresholding[0];
            res[i][j+1] = afterThresholding[1];
            res[i][j+2] = afterThresholding[2];
        }
    }
    return res;
}

void generateEdgeFile(unsigned char* data,int size) {
    std::ofstream outfile;
    outfile.open("img4.txt", std::ofstream::out);
    for(int i=0; i< size; i++) {
        if (data[i] == 255) {
            outfile << "1";
        }
        else {
            outfile << "0";
        }
        if (i < size-1) {
            outfile << ",";
        }
    }
    outfile.close();
}

unsigned char* Game::EdgeDetection(const std::string& fileName)
{
	int width, height, numComponents;
    int maxGrad = std::sqrt(255 * 255 * 2);
    unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);
    unsigned char** data2D = Generate2DMatrix(data, 256);
    unsigned char** newData2D = applyGausDerivative(data2D, 256);
    int** gradX = getDirectionalGradient(newData2D, 256, true);
    int** gradY = getDirectionalGradient(newData2D, 256, false);
    int** generalGrad = getGeneralGradient(gradX, gradY, 256);
    double** angle = getGradientDirection(gradX, gradY, 256);
    int** nonMaxSuppressed = applyNonMaximumSuppression(generalGrad,angle, 256);
    data2D = thresholding(nonMaxSuppressed, 0.5 * maxGrad, 0.3 * maxGrad, 256);
	data = Generate1DMatrix(data2D, 256);
    generateEdgeFile(data, 256 * 256 * 4);
    AddTexture(width, height, data);
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
