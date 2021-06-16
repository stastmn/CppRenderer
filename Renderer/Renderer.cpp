// Renderer.cpp : Определяет точку входа для приложения.
//only x64 build


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <SDL.h>

#include "framework.h"
#include "Renderer.h"
#include "Texture.h"
#include "model.h"
#include <chrono>



const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
SDL_Texture* g_targetTexture = nullptr;

bool g_IsRun = false;
SDL_Event events;

void InitSdlResourses();
void FreeSdlResourses();
void HandleEvents();

void line(int x0, int y0, int x1, int y1, Texture& renderTarget, int r, int g, int b, int a);
void line(int x0, int y0, int x1, int y1, Texture& renderTarget, DirectX::XMINT4& collor);
void DrawModel(Model& model, Texture& renderTarget, DirectX::XMINT4 colorVec);
void Triangle(DirectX::XMINT2 t0, DirectX::XMINT2 t1, DirectX::XMINT2 t2, Texture& renderTarget, DirectX::XMINT4 colorVec);


//ImGui global variables
DirectX::XMFLOAT3 g_lightDir(0.f, 0.f, -1.f);
bool wireRendering = false;


//TODO: swap buffer
//

int main(int argc, char * argv[])
{
	InitSdlResourses();
	Texture texture(WINDOW_WIDTH, WINDOW_HEIGHT);

	Model model("../obj/african_head.obj");
	DirectX::XMINT4 white(255, 255, 255, 255);

	DirectX::XMFLOAT4 screen = { (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT };
	DirectX::XMVECTOR screenVec = XMLoadFloat4(&screen);

	//	DrawModel(model, texture, white);
			//for (int i = 0; i < model.nfaces(); i++) {
			//	std::vector<int> face = model.face(i);
			//	for (int j = 0; j < 3; j++) {
			//		using namespace DirectX;

			//		DirectX::XMFLOAT3 v0 = model.vert(face[j]);
			//		DirectX::XMFLOAT3 v1 = model.vert(face[(j + 1) % 3]);

			//		
			//		DirectX::XMVECTOR tmp = XMVectorSet(v0.x, v0.y, v1.x, v1.y);
			//		tmp = tmp + XMVectorSet(1, 1, 1, 1);
			//		tmp = tmp * XMVectorSet(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
			//		tmp = tmp / XMVectorSet(2, 2, 2, 2);
			//		XMFLOAT4 result;  XMStoreFloat4(&result, tmp);
			//		line(result.x, result.y, result.z, result.w, texture, white);
			//		

			//		/*
			//		int x0 = (v0.x + 1.)*WINDOW_WIDTH / 2.;
			//		int y0 = (v0.y + 1.)*WINDOW_HEIGHT / 2.;
			//		int x1 = (v1.x + 1.)*WINDOW_WIDTH / 2.;
			//		int y1 = (v1.y + 1.)*WINDOW_HEIGHT / 2.;

			//		line(x0, y0, x1, y1, texture, white);
			//		*/
			//	}
			//}
	//{
	//	using namespace DirectX;

	//	XMINT4 t0[3] = { XMINT4(10,70,0,0), XMINT4(50,160,0,0),XMINT4(70,80,0,0) };
	//	XMINT4 t1[3] = { XMINT4(180,50,0,0), XMINT4(150,1,0,0),XMINT4(70,180,0,0) };
	//	XMINT4 t2[3] = { XMINT4(180,150,0,0), XMINT4(120,160,0,0),XMINT4(130,180,0,0) };

	//	Triangle(t0[0], t0[1], t0[2], texture, white);
	//	Triangle(t1[0], t1[1], t1[2], texture, XMINT4(255, 0, 0, 0));
	//	Triangle(t2[0], t2[1], t2[2], texture, XMINT4(255, 255, 0, 0));

	//}

	DirectX::XMFLOAT3 foo(1, 2, 3);
	//std::cout << foo.x + foo.y + foo.z;
	int i = 0;


	while (g_IsRun)
	{
		/*int y = i;
		for (; y < model.nfaces();) {
			std::vector<int> face = model.face(i);
			for (int j = 0; j < 3; j++) {
				using namespace DirectX;

				DirectX::XMFLOAT3 v0 = model.vert(face[j]);
				DirectX::XMFLOAT3 v1 = model.vert(face[(j + 1) % 3]);*/


		//		DirectX::XMVECTOR tmp = XMVectorSet(v0.x, v0.y, v1.x, v1.y);
		//		tmp = tmp + XMVectorSet(1, 1, 1, 1);
		//		tmp = tmp * XMVectorSet(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
		//		tmp = tmp / XMVectorSet(2, 2, 2, 2);
		//		XMFLOAT4 result;  XMStoreFloat4(&result, tmp);
		//		line(result.x, result.y, result.z, result.w, texture, white);


		//		/*
		//		int x0 = (v0.x + 1.)*WINDOW_WIDTH / 2.;
		//		int y0 = (v0.y + 1.)*WINDOW_HEIGHT / 2.;
		//		int x1 = (v1.x + 1.)*WINDOW_WIDTH / 2.;
		//		int y1 = (v1.y + 1.)*WINDOW_HEIGHT / 2.;

		//		line(x0, y0, x1, y1, texture, white);
		//		*/
		//	}
		//	break;
		//}

		//i++;

	
		HandleEvents();
		DrawModel(model, texture, DirectX::XMINT4(255, 0, 255, 255));
		SDL_RenderCopy(g_renderer, g_targetTexture, NULL, NULL);
		SDL_RenderPresent(g_renderer);
		SDL_UpdateTexture(g_targetTexture, NULL, (void*)texture.getPixel(), sizeof(Uint32) * WINDOW_WIDTH);

	}


	FreeSdlResourses();
	return 0;
}

void InitSdlResourses()
{
	g_IsRun = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(SDL_GetError());
	}
	else
	{
		std::cout << "SDL initialization succeeded!" << std::endl;
	}


	g_window = SDL_CreateWindow("Renderer", 100, 100,
		WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window == nullptr)
	{
		std::cout << "SDL window creating failed. SDL Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(SDL_GetError());
	}


	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if (g_renderer == nullptr)
	{
		std::cout << "SDL renderer creating failed. SDL Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(SDL_GetError());
	}

	g_targetTexture = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (g_targetTexture == nullptr)
	{
		std::cout << "SDL texture creating failed. SDL Error: " << SDL_GetError() << std::endl;
		throw std::runtime_error(SDL_GetError());
	}
}

void FreeSdlResourses()
{
	//cleanup
	g_IsRun = false;
	if (g_targetTexture != nullptr) {
		SDL_DestroyTexture(g_targetTexture);
		g_targetTexture = nullptr;
	}
	if (g_renderer != nullptr)
	{
		SDL_DestroyRenderer(g_renderer);
		g_renderer = nullptr;
	}
	if (g_window != nullptr)
	{
		SDL_DestroyWindow(g_window);
		g_window = nullptr;
	}
	SDL_Quit();

}


void HandleEvents() {

	while (SDL_PollEvent(&events) != NULL)
	{
		if (events.type == SDL_QUIT)
			g_IsRun = false;

		if (events.type == SDL_KEYDOWN) {

			switch (events.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				g_IsRun = false;
				break;

			case SDLK_SPACE:
				g_lightDir.x += 0.1;
				g_lightDir.y += 0.1;
				break;
			


			default:
				break;
			}



		}

	}

}

void line(int x0, int y0, int x1, int y1, Texture& texture, int r, int g, int b, int a) {

	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))	//line is steep? 
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	if (x0 > x1)	// 0th point righter than 1th? 
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror2 = std::abs(dy) * 2;
	float error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {

		if (steep)	//if transpose 
			texture.setCollor(y, x, r, g, b, a);
		else
			texture.setCollor(x, y, r, g, b, a);

		error2 += derror2;

		if (error2 >= dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}



	}

}



void line(int x0, int y0, int x1, int y1, Texture& texture, DirectX::XMINT4& collor) {

	bool steep = false;
	if (std::abs(x0 - x1) < std::abs(y0 - y1))	//line is steep? 
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}
	if (x0 > x1)	// 0th point righter than 1th? 
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;
	float derror2 = std::abs(dy) * 2;
	float error2 = 0;
	int y = y0;
	for (int x = x0; x <= x1; x++) {

		if (steep)	//if transpose 
			texture.setCollor(y, x, collor.x, collor.y, collor.z, collor.w);
		else
			texture.setCollor(x, y, collor.x, collor.y, collor.z, collor.w);

		error2 += derror2;

		if (error2 >= dx) {
			y += (y1 > y0 ? 1 : -1);
			error2 -= dx * 2;
		}
	}
}

void DrawModel(Model& model, Texture& renderTarget, DirectX::XMINT4 colorVec) {

	for (int i = 0; i < model.nfaces(); i++) {
		using namespace DirectX;
		XMINT4 color = colorVec;
		std::vector<int> face = model.face(i);
		XMINT2  screen_coords[3];
		XMVECTOR world_coords[3];

		for (int j = 0; j < 3; j++) {

			XMFLOAT3 tmp = model.vert(face[j]);
			world_coords[j] = XMLoadFloat3(&tmp);
			screen_coords[j] = XMINT2((tmp.x + 1.f)* WINDOW_WIDTH / 2, (tmp.y + 1.f)*WINDOW_HEIGHT / 2);



#ifdef zero



			DirectX::XMFLOAT3 v0 = model.vert(face[j]);
			DirectX::XMFLOAT3 v1 = model.vert(face[(j + 1) % 3]);
			DirectX::XMVECTOR tmp = XMVectorSet(v0.x, v0.y, v1.x, v1.y);
			tmp = tmp + XMVectorSet(1, 1, 1, 1);
			tmp = tmp * XMVectorSet(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT);
			tmp = tmp / XMVectorSet(2, 2, 2, 2);
			XMFLOAT4 result;  XMStoreFloat4(&result, tmp);
			line(result.x, result.y, result.z, result.w, renderTarget, colorVec);

#endif // 0
		}
		//XMFLOAT3 n;

		//XMStoreFloat3(&n, XMVector3Normalize( XMVectorPow((world_coords[2] - world_coords[0]), (world_coords[1] - world_coords[0])) ) * XMLoadFloat3(&g_lightDir));

		auto n = XMVector3Normalize(
					XMVector3Cross((world_coords[2] - world_coords[0]), (world_coords[1] - world_coords[0]))); //, XMLoadFloat3(&g_lightDir);
		
		float intensity = XMVectorGetX( XMVector3Dot(n, XMLoadFloat3(&g_lightDir)));
		XMStoreSInt4(&color, XMLoadSInt4(&colorVec) * intensity);



		/*	colorVec.w = 255;
			colorVec.y = 255;
			colorVec.z = 255;
			colorVec.x = 255;*/
		std::cout << colorVec.x << " " << colorVec.y << " " << colorVec.z << " \n";
		if(intensity >0)
		Triangle(screen_coords[0], screen_coords[1], screen_coords[2], renderTarget, color);
	}
}

void Triangle(DirectX::XMINT2 t0, DirectX::XMINT2 t1, DirectX::XMINT2 t2, Texture& renderTarget, DirectX::XMINT4 colorVec) {
	if (t0.y == t1.y && t0.y == t2.y) return;
	using namespace DirectX;
	if (t0.y > t1.y) std::swap(t1, t0);
	if (t0.y > t2.y) std::swap(t2, t0);
	if (t1.y > t2.y) std::swap(t2, t1);

	XMVECTOR vec0 = XMVectorSet(t0.x, t0.y, 0, 0);
	XMVECTOR vec1 = XMVectorSet(t1.x, t1.y, 0, 0);
	XMVECTOR vec2 = XMVectorSet(t2.x, t2.y, 0, 0);

	int total_height = t2.y - t0.y;
	for (int i = 0; i < total_height; i++) {
		bool second_half = i > t1.y - t0.y || t1.y == t0.y;
		int segment_height = second_half ? t2.y - t1.y : t1.y - t0.y;
		float alpha = (float)i / total_height;
		float beta = (float)(i - (second_half ? t1.y - t0.y : 0)) / segment_height;

		XMINT2 A = XMINT2(t0.x + (t2.x - t0.x)*alpha, t0.y + (t2.y - t0.y)*alpha);
		XMINT2 B = XMINT2(second_half ? t1.x + (t2.x - t1.x)*beta : t0.x + (t1.x - t0.x)*beta,
			second_half ? t1.y + (t2.y - t1.y)*beta : t0.y + (t1.y - t0.y)*beta);

		if (A.x > B.x) std::swap(A, B);
		for (int j = A.x; j <= B.x; j++) {
			renderTarget.setCollor(j, t0.y + i, colorVec.x, colorVec.y, colorVec.z, colorVec.w); // attention, due to int casts t0.y+i != A.y
		}
	}
}

