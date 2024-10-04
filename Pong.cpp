#include <raylib.h>
#include <math.h>

class Ball{
public: 
    Vector2 position;
    Vector2 speed; 
    float radius; 
    
    Ball(Vector2 ballPosition, float rad, Vector2 ballSpeed) {
	this->position = ballPosition; 
	this->speed = ballSpeed; 
	this->radius = rad;
    }

    void update() {
	position.x += speed.x; 
	position.y += speed.y;
    }
    void draw() {
	DrawCircleV(position, radius, DARKBLUE); 
    }
    void Bounce(float screenWidth, float screenHeight, int* p1, int* p2) {
	if ((position.x >= (screenWidth - radius))) {
	    position.x = screenWidth / 2; 
	    position.y = screenHeight / 2; 
	    *p1 += 1;
        } 
	if (position.x <= radius) {
	    position.x = screenWidth / 2; 
	    position.y = screenHeight / 2; 
	    *p2 += 1; 
	 
	}
	
        if ((position.y >= (screenHeight - radius)) || (position.y <= radius)) {
            speed.y *= -1.0f;  // Reverse vertical speed
        }
    }

    bool CheckCollision(const Rectangle& rect) {
    float closeX = fmax(rect.x, fmin(position.x, rect.x + rect.width)); 
    float closeY = fmax(rect.y, fmin(position.y, rect.y + rect.height)); 

    float distanceX = position.x - closeX; 
    float distanceY = position.y - closeY; 

    float distanceSqr = (distanceX * distanceX) + (distanceY * distanceY); 
    
    return distanceSqr <= (radius * radius); 
    }

};   

class Player{
public:
    Vector2 position;
    Vector2 vectorSize; 
    float speed; 
    Player(Vector2 playerPosition, Vector2 PlayerSize, float speed) {
	this->position = playerPosition; 
	this->vectorSize = PlayerSize; 
	this->speed = speed; 
    }
    void update()  {
	float deltaTime = GetFrameTime();
        if (IsKeyDown(KEY_UP)) position.y -= speed * deltaTime;
        if (IsKeyDown(KEY_DOWN)) position.y += speed * deltaTime;
    }
      void draw() {
        DrawRectangleV(position, vectorSize, DARKBLUE);
    }
    Rectangle GetRectangle() {
        return { position.x, position.y, vectorSize.x, vectorSize.y };
     }

};

class Bot{
public:
    Vector2 position; 
    Vector2 voctorSize;
    float speed;  
    Bot(Vector2 botPosition, Vector2 botSize, float speed) {
	this->position = botPosition;
	this->voctorSize = botSize; 
	this->speed = speed; 
    } 
    void update(Ball& ballPosition) {
	if (ballPosition.position.y < position.y) {
	    position.y -= speed * GetFrameTime(); 
	}
	if (ballPosition.position.y > position.y + voctorSize.y) {
	    position.y += speed * GetFrameTime(); 
	}
    }
     void draw() {
        DrawRectangleV(position, voctorSize, DARKBLUE);
    }
    Rectangle GetRectangle() {
        return { position.x, position.y, voctorSize.x, voctorSize.y };
    }

};
int main() {
	const int screenWidth = 800; 
	const int screenHeight = 450; 
	int p1 = 0;
	int p2 = 0; 
	InitWindow(screenWidth, screenHeight, "Ray-Pong");	
     	SetTargetFPS(60);

	Vector2 ballPosition = { screenWidth / 2.0, screenHeight / 2.0};
	Vector2 ballSpeed = {5.0, 4.0}; 
	Ball ball(ballPosition, 10.0, ballSpeed); 

	Vector2 playerPosition = {100.0, 100.0}; 
	Vector2 playerSize = {10.0, 100.0}; 
	float speed = 300.f; 
	Player player(playerPosition, playerSize, speed); 

	Vector2 botPosition = {700.0, 100.0};
	Vector2 botSize = {10.0, 100.0}; 
	float botSpeed = 400.f; 
	Bot bot(botPosition, botSize, botSpeed);  

	while (!WindowShouldClose()) {
	
	ball.update(); 
	ball.Bounce(screenWidth, screenHeight, &p1, &p2);
	player.update();
	bot.update(ball); 

	if (ball.CheckCollision(player.GetRectangle()) || ball.CheckCollision(bot.GetRectangle())) {
	    ball.speed.x *= -1.0f; 	
	}
	    BeginDrawing(); 
		ClearBackground(RAYWHITE); 
		DrawText(TextFormat("P1    %i", p1), 100, 50, 50, BLACK);
		DrawText(TextFormat("%i    P2", p2), 500, 50, 50, BLACK);
		DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, DARKGRAY);
		ball.draw();  
		player.draw();
		bot.draw(); 
	EndDrawing(); 
	} 
      CloseWindow();           
}
