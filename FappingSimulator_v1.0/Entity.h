#pragma once
class Entity
{
public:
	Entity();
	~Entity();

	void Init(int posx, int posy, int w, int h, int s);
	void GetRect(int* posx, int* posy, int* w, int* h);
	int  GetX();
	void SwapState();
	bool IsAlive();
	void Move(int dx, int dy);

	bool is_alive;

private:
	int x, y;
	int width, height;
	int speed;
};