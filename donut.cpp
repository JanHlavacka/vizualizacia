#include <iostream>
#include <cstdio>
#include <fstream>
#include <math.h>
# define M_PI           3.14159265358979323846

struct POINTS
{
    float x;
    float y;
    float z;
};
using namespace std;
int main()
{
    int equators = 15;
    int meridians = 23;
    int r = 5;
    int R = 10;
    float x0, y0, z0;
    x0 = 0.;
    y0 = 0.;
    z0 = 0.;
    int n = equators * meridians;

    POINTS* points = new POINTS[n];

    //points[0].x = x0 + r * sin(0) * cos(M_PI / 2);
    //points[0].y = y0 + r * sin(0) * cos(M_PI / 2);
    //points[0].z = z0 + r * cos(0);
    ////teta pi, cos sa ma rovnat -1 a sinus nule
    //points[equators * meridians + 1].x = x0 + r * sin(0) * cos(M_PI / 2);
    //points[equators * meridians + 1].y = y0 + r * sin(0) * sin(M_PI / 2);
    //points[equators * meridians + 1].z = z0 - r * cos(0);
    int k = 0;
    float equatorDiff = (2 * M_PI) / (equators);
    float meridianDiff = (2 * M_PI) / (meridians);
    for (int i = 0; i < meridians; i++)
    {
        //cout << i << endl;
        for (int j = 0; j < equators; j++)
        {
            
            //cout << k << endl;
            points[k].x = (R + r * cos(0 + (j * equatorDiff))) * cos(i * meridianDiff);
            points[k].y = (R + r * cos(0 + (j * equatorDiff))) * sin(i * meridianDiff);
            points[k].z = r * sin(0 + (j * equatorDiff));
            k++;
        }
    }

    ofstream outfile;
    outfile.open("donut_15_23_10_5.vtk");

    outfile << "# vtk DataFile Version 2.0" << endl;
    outfile << "torus" << endl;
    outfile << "ASCII" << endl;
    outfile << "DATASET POLYDATA" << endl;
    outfile << "POINTS " << n << " float" << endl;

    for (int i = 0; i < n; i++)
    {
        outfile << points[i].x << " " << points[i].y << " " << points[i].z << endl;
    }


    //*******budem musiet zmenit meridians*4 aby to sedelo aj pre rozne ine hodnoty meridians a equators

    outfile << "POLYGONS " << 2 * n << " " << 8 * n << endl;
    for (int i = 0; i < meridians; i++)
    {
        if (i != meridians - 1) {
            for (int j = 0; j < equators; j++)
            {
                if (j != equators - 1) {
                    outfile << 3 << " " << i * equators + j << " " << i * equators + 1 + j << " " << i * equators + 1 + j + equators << endl;
                    outfile << 3 << " " << i * equators + j << " " << i * equators + equators + 1 + j << " " << i * equators + equators + j << endl;
                }
                else {
                    outfile << 3 << " " << i * equators + j << " " << i * equators << " " << i * equators + equators << endl;
                    outfile << 3 << " " << i * equators + j << " " << i * equators + 1 + j << " " << i * equators + equators + j << endl;
                }
            }
        }
        else {
            for (int j = 0; j < equators; j++)
            {
                if (j != equators - 1) {
                    outfile << 3 << " " << i * equators + j << " " << i * equators + 1 + j << " " << 1 + j << endl;
                    outfile << 3 << " " << i * equators + j << " " << 1 + j << " " <<  j << endl;
                }
                else {
                    outfile << 3 << " " << i * equators + j << " " << i * equators << " " << 0 << endl;
                    outfile << 3 << " " << i * equators + j << " " << 0 << " " << j << endl;
                }
            }
        }

    }
    //int p = 0;
    //for (int i = 1; i < equators; i++)
    //{
    //    //cout << i << endl;
    //    for (int j = 0; j < meridians; j++)
    //    {
    //        p++;
    //        if (j == meridians - 1) {
    //            outfile << 3 << " " << p << " " << p + meridians << " " << p - meridians + 1 << endl;
    //            outfile << 3 << " " << p - meridians + 1 << " " << p + meridians << " " << p + 1 << endl;
    //        }
    //        else {
    //            outfile << 3 << " " << p << " " << p + meridians << " " << p + 1 << endl;
    //            outfile << 3 << " " << p + 1 << " " << p + meridians << " " << p + meridians + 1 << endl;
    //        }
    //    }
    //    p = meridians * i;
    //}
    /*int t = meridians * (equators - 1) + 1;
    for (int i = 0; i < meridians; i++)
    {
        if (i == meridians - 1) {
            outfile << 3 << " " << t + i << " " << t << " " << meridians * equators + 1 << endl;
        }
        else {
            outfile << 3 << " " << t + i << " " << t + i + 1 << " " << meridians * equators + 1 << endl;
        }
    }*/
    outfile.close();
    delete[]points;
    points = NULL;

    return 0;
}