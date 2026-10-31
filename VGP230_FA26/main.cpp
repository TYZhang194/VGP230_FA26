#include <raylib.h>
#include <string>
#include <iostream>
#include <raymath.h>

//TianYi Zhang's Repo

void FirstFunction()
{
    InitWindow(500, 500, "VGP230_FA26_C1a");
    SetTargetFPS(30);

    const char* title = "Cool Math Games";
    std::string Signiture = "W.Z";
    std::string author = "By: " + Signiture;

    int fontSize = 20;
    int titleWidth = MeasureText(title, fontSize);
    int authorWidth = MeasureText(author.c_str(), fontSize);

    Vector2 center = { 250, 250 };
    float rotation = -18.0f;
    float rotationSpeed = 45.0f;
    float radius = 150.0f;

    while (!WindowShouldClose())
    {
        rotation += rotationSpeed * GetFrameTime();

        if (rotation >= 360.0f)
        {
            rotation -= 360.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircle(250, 250, radius, BLUE);

        DrawPolyLinesEx(center, 5, radius, rotation, 5.0f, RED);

        DrawText(title, (GetScreenWidth() - titleWidth) / 2,
            240, fontSize, BLACK);

        DrawText(author.c_str(), (GetScreenWidth() - authorWidth) / 2,
            270, fontSize, BLACK);

        EndDrawing();
    }
}

void MovingBall()
{
    int width = 1600;
    int height = 800;
    InitWindow(width, height, "Moving Ball");
    SetTargetFPS(30);

    int radius = 20;
    int centerX = radius;
    int centerY = height / 2;
    int traillength = 100;
    int speed = 5;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);



        DrawCircle(centerX, centerY, radius, ORANGE);

        centerX += speed;

        if (centerX - radius >= width)
        {
            centerX = -radius + 1;
        }



        EndDrawing();
    }

    CloseWindow();
}

void NewMovingBall()
{
    int width = 1600;
    int height = 800;
    InitWindow(width, height, "New Moving Ball");
    SetTargetFPS(60);

    int radius = 20;
    int centerX = radius;
    int centerY = height / 2;
    int traillength = 100;
    int speed = 5;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = traillength - 1; i >= 0; i--)
        {
            int alpha = 255 * (traillength - i) / traillength;

            Color trailColor = {
                255, 165, 0, static_cast<unsigned char>(alpha)
            };

            DrawCircle(centerX - (i * speed * 2),
                centerY, radius, trailColor);
        }

        DrawCircle(centerX, centerY, radius, ORANGE);

        centerX += speed;

        if (centerX - radius >= width)
        {
            centerX = -radius + 1;
        }

        EndDrawing();
    }

    CloseWindow();
}

void TwoBallImpact()
{
    int WindowWidth = 500;
    int WindowHeight = 500;

    InitWindow(WindowWidth, WindowHeight, "Two Ball Impact");
    SetTargetFPS(60);

    int radius = 20;

    int centerX1 = radius;
    int centerY1 = WindowHeight / 2;
    int speedX1 = 5;
    int speedY1 = 5;

    int centerX2 = WindowWidth - radius;
    int centerY2 = WindowHeight / 2;
    int speedX2 = -5;
    int speedY2 = -5;

    int combinedRadius = radius * 2;
    bool pause = false;

    while (!WindowShouldClose())
    {
        if (!pause)
        {
            centerX1 += speedX1;
            centerY1 += speedY1;
            centerX2 += speedX2;
            centerY2 += speedY2;

            // ball One
            // Right wall
            if (centerX1 + radius >= WindowWidth)
            {
                centerX1 = WindowWidth - radius;
                speedX1 = -GetRandomValue(2, 5);
                speedY1 = GetRandomValue(-5, 5);
            }
            // Left wall
            else if (centerX1 - radius <= 0)
            {
                centerX1 = radius;
                speedX1 = GetRandomValue(2, 5);
                speedY1 = GetRandomValue(-5, 5);
            }

            // Bottom wall
            if (centerY1 + radius >= WindowHeight)
            {
                centerY1 = WindowHeight - radius;
                speedY1 = -GetRandomValue(2, 5);
                speedX1 = GetRandomValue(-5, 5);
            }
            // Top wall
            else if (centerY1 - radius <= 0)
            {
                centerY1 = radius;
                speedY1 = GetRandomValue(2, 5);
                speedX1 = GetRandomValue(-5, 5);
            }

            // Corners
            if (centerX1 <= radius && speedX1 < 0)
            {
                speedX1 *= -1;
            }

            if (centerX1 >= WindowWidth - radius && speedX1 > 0)
            {
                speedX1 *= -1;
            }

            // Ball Two
            // Right wall
            if (centerX2 + radius >= WindowWidth)
            {
                centerX2 = WindowWidth - radius;
                speedX2 = -GetRandomValue(2, 5);
                speedY2 = GetRandomValue(-5, 5);
            }
            // Left wall
            else if (centerX2 - radius <= 0)
            {
                centerX2 = radius;
                speedX2 = GetRandomValue(2, 5);
                speedY2 = GetRandomValue(-5, 5);
            }

            // Bottom wall
            if (centerY2 + radius >= WindowHeight)
            {
                centerY2 = WindowHeight - radius;
                speedY2 = -GetRandomValue(2, 5);
                speedX2 = GetRandomValue(-5, 5);
            }
            // Top wall
            else if (centerY2 - radius <= 0)
            {
                centerY2 = radius;
                speedY2 = GetRandomValue(2, 5);
                speedX2 = GetRandomValue(-5, 5);
            }

            // Corners
            if (centerX2 <= radius && speedX2 < 0)
            {
                speedX2 *= -1;
            }

            if (centerX2 >= WindowWidth - radius && speedX2 > 0)
            {
                speedX2 *= -1;
            }

            // Collision Box Calculation
            int distanceX = centerX2 - centerX1;
            int distanceY = centerY2 - centerY1;

            // Collision
            if (distanceX * distanceX + distanceY * distanceY
                <= combinedRadius * combinedRadius)
            {
                pause = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircle(centerX1, centerY1, radius, ORANGE);
        DrawCircle(centerX2, centerY2, radius, BLUE);

        // Collision Message
        if (pause)
        {
            DrawText("Collision - paused", 10, 10, 30, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
}

void TriangleFunction()
{
    int wh = 800;
    InitWindow(wh, wh, "Triangle Function");
    SetTargetFPS(60);

    Vector2 Top = { wh / 2.0f, 100.0f };
    Vector2 Left = { 100.0f, wh - 100.0f };
    Vector2 Right = { wh - 100.0f, wh - 100.0f };

    float r = 80;
    int isDragging = 0;

    while (!WindowShouldClose())
    {
        Vector2 Mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            float TopDist = Vector2Distance(Mouse, Top);
            float LeftDist = Vector2Distance(Mouse, Left);
            float RightDist = Vector2Distance(Mouse, Right);

            if (TopDist <= r)
            {
                isDragging = 1;
            }
            else if (LeftDist <= r)
            {
                isDragging = 2;
            }
            else if (RightDist <= r)
            {
                isDragging = 3;
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            isDragging = 0;
        }

        switch (isDragging)
        {
        case 1: Top = Mouse; break;
        case 2: Left = Mouse; break;
        case 3: Right = Mouse; break;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTriangleLines(Top, Left, Right, BLACK);

        DrawCircle(Top.x, Top.y, r, RED);
        DrawCircle(Left.x, Left.y, r, GREEN);
        DrawCircle(Right.x, Right.y, r, BLUE);

        EndDrawing();
    }

    CloseWindow();
}

void TriangleColorFunction()
{
    int wh = 800;
    InitWindow(wh, wh, "Triangle Color Function");
    SetTargetFPS(60);
    Vector2 Center = { wh / 2.0f, wh / 2.0f };
    Vector2 Top = { Center.x, Center.y };
    Vector2 Left = { Center.x, Center.y };
    Vector2 Right = { Center.x, Center.y };

    float r = 120;
    int isDragging = 0;

    while (!WindowShouldClose())
    {
        Vector2 Mouse = GetMousePosition();

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            float TopDist = Vector2Distance(Mouse, Top);
            float LeftDist = Vector2Distance(Mouse, Left);
            float RightDist = Vector2Distance(Mouse, Right);

            if (TopDist <= r)
            {
                isDragging = 1;
            }
            else if (LeftDist <= r)
            {
                isDragging = 2;
            }
            else if (RightDist <= r)
            {
                isDragging = 3;
            }
        }

        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        {
            isDragging = 0;
        }

        if (isDragging != 0)
        {
			//Calculation Block, Determine the offset of the mouse from the center of the triangle
            Vector2 offset = { Mouse.x - Center.x, Mouse.y - Center.y };

			//2D Rotation Equation: x = xcos(Theta) - ysin(Theta), x = xcos(Theta) + ysin(Theta), Theta = 120 degrees, cos(Theta) = -0.5, sin(Theta) = 0.86602540378
            Vector2 plus120 = { -0.5f * offset.x - 0.86602540378f * offset.y, 0.86602540378f * offset.x - 0.5f * offset.y }; 

            Vector2 minus120 = { -0.5f * offset.x + 0.86602540378f * offset.y, -0.86602540378f * offset.x - 0.5f * offset.y };

            switch (isDragging) //Does the actual moving
            {
            case 1:
                Top = Mouse;
                Left = Vector2Add(Center, minus120);
                Right = Vector2Add(Center, plus120);
                break;

            case 2:
                Left = Mouse;
                Top = Vector2Add(Center, plus120);
                Right = Vector2Add(Center, minus120);
                break;

            case 3:
                Right = Mouse;
                Top = Vector2Add(Center, minus120);
                Left = Vector2Add(Center, plus120);
                break;
            }
        }


        BeginDrawing();

		BeginBlendMode(BLEND_ADDITIVE); //Additive Colour Blending Mode

        ClearBackground(BLACK);

        DrawTriangleLines(Top, Left, Right, GRAY);

        DrawCircle(Top.x, Top.y, r, RED);
        DrawCircle(Left.x, Left.y, r, GREEN);
        DrawCircle(Right.x, Right.y, r, BLUE);

        EndDrawing();
    }

    CloseWindow();
}

void TriangleShapeFunction()
{
    int wh = 800;
    InitWindow(wh, wh, "Triangle Shapes");
    SetTargetFPS(60);

    Vector2 center = { wh / 2.0f, wh / 2.0f };
    float radius = 250.0f;

    int triangles = 6;

    while (!WindowShouldClose())
    {
		//Increase the number of triangles when the W key is pressed
        if (IsKeyPressed(KEY_W))
        {
            triangles++;
        }

		//Limit the number of triangles to a minimum of 6
        if (IsKeyPressed(KEY_S) && triangles > 6)
        {
            triangles--;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < triangles; i++)
        {
			//Calculate the angles for the current triangle
            float angle1 = i * (360.0f / triangles) - 90.0f;
            float angle2 = (i + 1) * (360.0f / triangles) - 90.0f;

			//Calculate the points for the current triangle using the angles and radius, then rotate them around the center point 
			//Equation: x = center.x + radius * cos(theta)
            Vector2 point1 = Vector2Add(center,Vector2Rotate (Vector2 { radius, 0.0f }, angle1 * DEG2RAD));

            Vector2 point2 = Vector2Add(center, Vector2Rotate (Vector2{ radius, 0.0f }, angle2 * DEG2RAD));

            //Generate a different rainbow color for each triangle
            float color = i * (360.0f / triangles);
            //Raylib Color Hue/Saturation?Value 
            Color triangleColor = ColorFromHSV(color, 1.0f, 1.0f);

            DrawTriangle(center, point2, point1, triangleColor);
            DrawTriangleLines(center, point2, point1, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
}

void HypotrochoidDrawing()
{
    InitWindow(800, 800, "Animated Hypotrochoid");
    SetTargetFPS(60);

	float R = 150.0f; // Radius of the fixed circle
	float r = 60.0f;  // Radius of the rolling circle
	float d = 90.0f;  // Distance from the center of the rolling circle to the drawing point

    Vector2 center = { 400.0f, 400.0f };

	float maxT = 0.0f; // Angle of the hypotrochoid drawing point, in radians
	float speed = 2.0f; // Speed of the drawing point

    while (!WindowShouldClose())
    {
		maxT += speed * GetFrameTime(); // Update the angle based on the speed and frame time

		if (IsKeyPressed(KEY_R)) // Reset the angle to 0 when the R key is pressed, part of the drawing alteration
        {
            maxT = 0.0f; 
        }

		if (IsKeyPressed(KEY_Q)) { R += 10.0f; } // At the press of Q/W/E key, the values of R/r/d will increase by 10
        if (IsKeyPressed(KEY_W)) { r += 10.0f; }
        if (IsKeyPressed(KEY_E)) { d += 10.0f; }

		if (IsKeyPressed(KEY_A)) { R -= 10.0f; } // Vise versa, at the press of A/S/D key, the values of R/r/d will decrease by 10
        if (IsKeyPressed(KEY_S)) { r -= 10.0f; }
        if (IsKeyPressed(KEY_D)) { d -= 10.0f; }

		if (R < 5.0f) { R = 5.0f; } // Limit the values of R/r/d to a minimum of 5/0/0, respectively
        if (r < 5.0f) { r = 5.0f; }
        if (d < 0.0f) { d = 0.0f; }

		float smallX = center.x + (R - r) * cosf(maxT); // Calculate the position of the center of the rolling circle, for drawing the CircleLines
		float smallY = center.y + (R - r) * sinf(maxT); 

		float penX = smallX + d * cosf((R - r) / r * maxT); // Calculate the position of the drawing point, for drawing the line from the center of the rolling circle to the drawing point
        float penY = smallY - d * sinf((R - r) / r * maxT);

        BeginDrawing();
        ClearBackground(BLACK);
		DrawCircle((int)center.x, (int)center.y, 4, WHITE); // Draw the center point of the larger fixed circle
		DrawCircleLines((int)center.x, (int)center.y, R, GRAY); // Draw the larger fixed circle

		for (float t = 0.0f; t < maxT; t += 0.01f) // Draw the hypotrochoid curve by connecting points with lines
        {
			float nextT = fminf(t + 0.01f, maxT); // nextT always returns the next point in the hypotrochoid curve, but will not exceed maxT

            float x1 = (R - r) * cosf(t) + d * cosf((R - r) / r * t); 

            float y1 = (R - r) * sinf(t) - d * sinf((R - r) / r * t); 

			float x2 = (R - r) * cosf(nextT) + d * cosf((R - r) / r * nextT); // This is doing the calculation for the next point in the hypotrochoid curve, not necessary if we were to only use dots.

			float y2 = (R - r) * sinf(nextT) - d * sinf((R - r) / r * nextT);

            DrawLine((int)(center.x + x1), (int)(center.y + y1), (int)(center.x + x2), (int)(center.y + y2), SKYBLUE); 
        }

		DrawCircleLines((int)smallX, (int)smallY, r, YELLOW); // Draw the rolling circle

		DrawLine((int)smallX, (int)smallY, (int)penX, (int)penY, RED); // Draw the line from the center of the rolling circle to the drawing point

		DrawCircle((int)penX, (int)penY, 5.0f, GREEN); // Draw the drawing point

        DrawText("Press R to reset, Q/W/E to increase R/r/d, A/S/D to decrease R/r/d", 10, 10, 20, WHITE);

        DrawText(TextFormat("Outer Circle Radius (R): %i", (int)R), 10, 40, 20, WHITE);

        DrawText(TextFormat("Inner Circle Radius (r): %i", (int)r), 10, 70, 20, WHITE);

        DrawText(TextFormat("Pen Distance (d): %i", (int)d), 10, 100, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
}

int main()
{
    HypotrochoidDrawing();
    return 0;
}