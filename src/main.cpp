#include <iostream>
#include <SDL3/SDL.h>
#define _USE_MATH_DEFINES
#include <cmath>

#define WIDTH 1800
#define HEIGHT 950
#define COLOR_BLACK 0x00000000
#define COLOR_RAY 0xffd100
#define RAYS_NUMBER 100
#define COLOR_SHADOW 0x21618c
#define COLOR_SUN 0xf9e79f

struct Circle
{
    double x;
    double y;
    double r;
};

struct Ray
{
    double x_start, y_start;
    double angle;
};

void FillCircle(SDL_Surface *surface, struct Circle circle, Uint32 color)
{
    double radius_squared = std::pow(circle.r, 2);
    for (int x = static_cast<int>(circle.x - circle.r); x <= static_cast<int>(circle.x + circle.r); x++)
    {
        for (int y = static_cast<int>(circle.y - circle.r); y <= static_cast<int>(circle.y + circle.r); y++)
        {
            double distance_squared = std::pow(x - circle.x, 2) + std::pow(y - circle.y, 2);
            if (distance_squared < radius_squared)
            {
                SDL_Rect pixel = SDL_Rect{x, y, 1, 1};
                SDL_FillSurfaceRect(surface, &pixel, color);
            }
        }
    }
}

void GenerateRays(struct Circle circle, struct Ray rays[RAYS_NUMBER])
{
    for (int i = 0; i < RAYS_NUMBER; i++)
    {
        double angle = ((double)i / RAYS_NUMBER) * 2 * M_PI;
        struct Ray ray = {circle.x, circle.y, angle};
        rays[i] = ray;
    }
}

void ReflectionofFillRays(SDL_Surface *surface, struct Ray rays[RAYS_NUMBER], Uint32 color, struct Circle object)
{

}

void FillRays(SDL_Surface *surface, struct Ray rays[RAYS_NUMBER], Uint32 color, struct Circle object)
{
    double radius_squared = pow(object.r, 2);
    for (int i = 0; i < RAYS_NUMBER; i++)
    {
        struct Ray ray = rays[i];
        int end_of_screen = 0;

        double step = 1.0000;

        double x_draw = ray.x_start;
        double y_draw = ray.y_start;

        while (!end_of_screen)
        {
            x_draw += step * cos(ray.angle);
            y_draw += step * sin(ray.angle);

            SDL_Rect ray_thickness = SDL_Rect{static_cast<int>(x_draw), static_cast<int>(y_draw), 2, 2};
            SDL_FillSurfaceRect(surface, &ray_thickness, color);

            if (x_draw < 0.0000 || x_draw > WIDTH)
                end_of_screen = 1;
            if (y_draw < 0.0000 || y_draw > HEIGHT)
                end_of_screen = 1;

            double distance_squared = std::pow(x_draw - object.x, 2) + std::pow(y_draw - object.y, 2);
            if (distance_squared < radius_squared)
            {
                break;
            }
        }
    }
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("RayTracing", WIDTH, HEIGHT, 0);

    SDL_Surface *surface = SDL_GetWindowSurface(window);

    struct Circle circle = {100, 700, 40};
    struct Circle shadow_circle = {1000, 500, 140};
    SDL_Rect erase_rect = {0, 0, WIDTH, HEIGHT};

    struct Ray rays[RAYS_NUMBER];
    GenerateRays(circle, rays);

    double obstacle_speed_y = 1.0000;
    int simulation_running = 1;
    SDL_Event event;

    while (simulation_running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                simulation_running = 0;
            }
            
            /*Mouse motion of the Sun*/
            // if (event.type == SDL_EVENT_MOUSE_MOTION && event.motion.state != 0)
            // {
            //     circle.x = event.motion.x;
            //     circle.y = event.motion.y;
            //     GenerateRays(circle, rays);
            // }
        }

        SDL_FillSurfaceRect(surface, &erase_rect, COLOR_BLACK);

        FillRays(surface, rays, COLOR_RAY, shadow_circle);
        FillCircle(surface, circle, COLOR_SUN);
        FillCircle(surface, shadow_circle, COLOR_SHADOW);

        /*Speed of the shadow circle*/
        // shadow_circle.y += obstacle_speed_y;
        // if (shadow_circle.y - shadow_circle.r < 0)
        //     obstacle_speed_y = -obstacle_speed_y;
        // if (shadow_circle.y + shadow_circle.r > HEIGHT)
        //     obstacle_speed_y = -obstacle_speed_y;

        SDL_UpdateWindowSurface(window);
        SDL_Delay(10);
    }
}