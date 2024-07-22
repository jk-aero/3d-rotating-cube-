#include "raylib.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <stdexcept>

struct vec3D { float x; float y; float z; };
struct vec2D { float x; float y; };


std::vector<vec2D>sqrPnts = {
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0},
    {0,0}, 
};

std::vector<vec3D>points =
{
     { 100, 100, 100 },
     { 200, 100, 100 },
     { 200, 200, 100 },
     { 100, 200, 100 },

     { 100, 100, 200 },
     { 200, 100, 200 },
     { 200, 200, 200 },
     { 100, 200, 200 }


};

vec3D c{ 0,0,0 };


vec2D convertPoints(vec3D& point)
{   
    float x = 50*(point.x / (point.z * 0.5));
    float y = 50*( point.y / (point.z * 0.5));
    return vec2D{ x,y };
}
   
void rotate(vec3D& point, float x, float y, float z)
{
float rad = 0;
rad = x;
point.y = std::cos(rad) * point.y - std::sin(rad) * point.z;
point.z = std::sin(rad) * point.y + std::cos(rad) * point.z;

rad = y;
point.x = std::cos(rad) * point.x + std::sin(rad) * point.z;
point.z = -std::sin(rad) * point.x + std::cos(rad) * point.z;

rad = z;
point.x = std::cos(rad) * point.x - std::sin(rad) * point.y;
point.y = std::sin(rad) * point.x + std::cos(rad) * point.y;



}




int getDistance2D(vec2D p1, vec2D p2)
{
float dx = (p1.x - p2.x);
float dy = (p1.y - p2.y);

return std::sqrt(dx * dx + dy * dy);
}



int getDistance3D(vec3D p1, vec3D p2) 
{
   // d = ?[(x2 – x1)2 + (y2 – y1)2 + (z2 – z1)2].
    float dx = (p1.x - p2.x);
    float dy = (p1.y - p2.y);
    float dz = (p1.z - p2.z);
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}


int main(void)
{
    const int screenWidth = 900;
    const int screenHeight = 900; 
 //finding the centroids******************
    for (auto&p : points)
    {   
        c.x += p.x;
        c.z += p.z;
        c.y += p.y;
    
    }
    c.x /= points.size();
    c.y /= points.size();
    c.z /= points.size();
//********************************************



    InitWindow(screenWidth, screenHeight, "Cube Rotation Example");
    SetTargetFPS(40); // Set our game to run at 60 frames-per-second
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        //rotating*************************
        for (auto& p : points)
        {
            p.x -= c.x;
            p.y -= c.y;
            p.z -= c.z;

            rotate(p, 0.002, 0.001, 0.004);
            p.x += c.x;
            p.y += c.y;
            p.z += c.z;
        }
        

        for (int j = 0; j < points.size(); j++)
        {
            sqrPnts[j]=convertPoints(points[j]);
      
        }


        BeginDrawing();
        ClearBackground(BLACK);

        // Drawing**************************
       
        for (int i = 0; i < points.size();i++) {
            
            DrawCircle(points[i].x + 100, points[i].y + 100, 1, GREEN);
            for (int j = 0; j < points.size(); j++) 
            {
                int d = getDistance3D(points[i], points[j]);
                std::cout << "distance : " << d << '\n';
                if(d<=99)
                {
                    DrawLine(points[i].x + 100, points[i].y + 100, points[j].x + 100, points[j].y + 100, DARKBLUE);
                }
               


            }
            std::cout << '\n';
        } 



        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}
