#include <raylib.h>

int main(void)
{
    const int screenWidth = 450;
    const int screenHeight = 800;

    const float halfScreen = screenWidth / 2.0f;
    const float fourthHeight = screenHeight / 4.0f;

    InitWindow(screenWidth, screenHeight, "Asteroids");
    SetWindowIcon(LoadImage("resources/icon.png"));
    SetTargetFPS(60);

    // SCORE
    int score = 0;
    Vector2 scorePosition = {10.0f, 10.0f};

    // ASTEROID
    float asteroidRadius = 15.0f;
    Vector2 asteroid = {halfScreen, fourthHeight};

    // SHIP
    float shipWidth = 20.0f;
    float shipHeight = 30.0f;
    Vector2 shipPoint = {halfScreen, fourthHeight * 3};
    Vector2 shipBottomLeft = {halfScreen - (shipWidth / 2), (fourthHeight * 3) + shipHeight};
    Vector2 shipBottomRight = {halfScreen + (shipWidth / 2), (fourthHeight * 3) + shipHeight};

    // BULLET
    Vector2 bullet;
    bool fired = false;
    float bulletRadius = 2.0f;
    float bulletVelocity = 5.0f;

    // MOVEMENT
    float hVelocity = 5.0f;
    float hPosition = halfScreen;

    // GAME LOOP
    while (!WindowShouldClose())
    {
        // CALCULATE SHIP POSITION
        hPosition -= IsKeyDown(KEY_LEFT) ? hVelocity : 0;
        hPosition += IsKeyDown(KEY_RIGHT) ? hVelocity : 0;
        shipPoint.x = hPosition;
        shipBottomLeft.x = hPosition - (shipWidth / 2);
        shipBottomRight.x = hPosition + (shipWidth / 2);

        // BULLET DISPLACEMENT
        if (!fired && IsKeyPressed(KEY_SPACE))
        {
            bullet = shipPoint;
            fired = true;
        }

        if (fired)
        {
            bullet.y -= bulletVelocity;
            if (bullet.y <= 0)
                fired = false;
        }

        // HIT
        if (CheckCollisionCircles(bullet, bulletRadius, asteroid, asteroidRadius))
        {
            bullet = (Vector2){-50, -50};
            fired = false;
            score += 1;
        }

        // DRAW
        ClearBackground(BLACK);
        BeginDrawing();
        DrawText(TextFormat("%i", score), scorePosition.x, scorePosition.y, 26, WHITE);
        DrawCircleV(asteroid, asteroidRadius, BROWN);
        DrawTriangle(shipPoint, shipBottomLeft, shipBottomRight, fired ? RED : WHITE);
        DrawCircleV(bullet, bulletRadius, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}