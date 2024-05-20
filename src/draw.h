#pragma once
#include <SDL.h>
#include <cassert>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <cassert>
#include <vector>

#define RGB32(r, g, b) static_cast<uint32_t>((((static_cast<uint32_t>(b) << 8) | g) << 8) | r)
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void line (SDL_Surface *s, int x1, int y1, int x2, int y2, int color);



struct Point
{
    int x;
    int y;
};

struct Affine_transform
{
    int Tx;
    int Ty;
    float scale;
    float alpha;
};

class Figure
{
    int num_vertex;
    std::vector<Point> point;
    Affine_transform koefs;
    Figure* nested_f;
    public:

    Figure()
    {
        num_vertex=4;
        koefs.Tx=SCREEN_WIDTH/2;
        koefs.Ty=SCREEN_HEIGHT/2;
        koefs.alpha=0;
        koefs.scale=1;
        nested_f=NULL;
        for(int i = 0; i < num_vertex; i++)
        {
            Point p;
            p.x = 100*cos(2 * M_PI * i / num_vertex);
            p.y =  100*sin(2 * M_PI * i / num_vertex);
            point.push_back(p);
        }


    }
    Figure(int x)
    {
        num_vertex=x;
        koefs.Tx=SCREEN_WIDTH/2;
        koefs.Ty=SCREEN_HEIGHT/2;
        koefs.alpha=0;
        koefs.scale=1;
        nested_f=NULL;

    }
    // Point& operator [](int i)
    // {
    //     return point[i];
    //

    void set_points(Point p1, Point p2, int n)
    {
        Point temp;
        int k=3;
        //float u = 0.1;
        float u = tan(k*M_PI/(num_vertex*n))/(tan(k*M_PI/(num_vertex*n))+1);;
        temp.x = (1-u)*p1.x+u*p2.x;
        temp.y = (1-u)*p1.y+u*p2.y;
        point.push_back(temp);

    }

    void draw(SDL_Surface *s)
    {
        for(int i = 0; i < num_vertex; i++)
        {
            if(i == num_vertex-1)
            {
                line(s, point[i].x, point[i].y, point[0].x, point[0].y, RGB32(0, 255, 0));
            }
            else
            {
                line(s, point[i].x, point[i].y, point[i+1].x, point[i+1].y, RGB32(0, 255, 0));
            }
        }
    }

    void get_affine_koef(int flag, float koef)
    {
        switch(flag)
        {
        case 1:
        koefs.Tx += koef;
        break;
        case 2:
        koefs.Ty += koef;
        break;
        case 3:
        koefs.alpha += koef;
        break;
        case 4:
        if(koefs.scale+koef > 0.01)
        {koefs.scale += koef;}
        break;
        case 5:
        if(num_vertex+koef>=3)
        {
             for(int j = 0; j < num_vertex; j++)
            {
                point.pop_back();
            }
            num_vertex+=koef;
            for(int i = 0; i < num_vertex; i++)
            {
            Point p;
            p.x = 100*cos(2 * M_PI * i / num_vertex);
            p.y =  100*sin(2 * M_PI * i / num_vertex);
            point.push_back(p);
            }
        }
        break;
        default:
        printf("Wrong affine koef\n");
        break;
        }

    }

    void transform()
    {
        for(int i=0; i<num_vertex; i++)
        {
            glm::vec4 Position = glm::vec4(point[i].x, point[i].y, 1.0f, 1.0f);
            glm::mat4 Translate = glm::translate(   glm::mat4(1.0f), glm::vec3(koefs.Tx, koefs.Ty, 1.0f));;
            glm::mat4 Rotate = glm::rotate(glm::mat4(1.0f), glm::radians(koefs.alpha), glm::vec3(0.0, 0.0, 1.0));;
            glm::mat4 Scale = glm::scale(glm::mat4(1.0f), glm::vec3(koefs.scale, koefs.scale, 1));

            glm::vec3 Transformed = Translate*Rotate*Scale*Position;
            point[i].x=Transformed.x;
            point[i].y=Transformed.y;
        }
    }

    void nested_figure(SDL_Surface *s, int n, int count)
    {
        nested_f = new Figure(num_vertex);

        if(n > 0)
        {
        for(int i = 0; i<num_vertex; i++)
        {
            if(i==num_vertex-1)
            {
                nested_f->set_points(point[i], point[0], count+1);
            }
            else
            {
                nested_f->set_points(point[i], point[i+1], count+1);

            }
        }
        nested_f->draw(s);

        nested_f->nested_figure(s, n-1, count);
        }
    }
};

void draw(SDL_Surface *s, Figure square, int n);
