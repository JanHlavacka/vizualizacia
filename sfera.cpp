// sfera.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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
    int equators = 13;
    int meridians = 12;
    int r = 4;
    float x0, y0, z0;
    x0 = 0.;
    y0 = 0.;
    z0 = 0.;
    int n = equators * meridians + 2;

    POINTS* points = new POINTS[n];

    points[0].x = x0 + r * sin(0) * cos(M_PI / 2);
    points[0].y = y0 + r * sin(0) * cos(M_PI / 2);
    points[0].z = z0 + r * cos(0);
    //teta pi, cos sa ma rovnat -1 a sinus nule
    points[equators * meridians + 1].x = x0 + r * sin(0) * cos(M_PI / 2);
    points[equators * meridians + 1].y = y0 + r * sin(0) * sin(M_PI / 2);
    points[equators * meridians + 1].z = z0 - r * cos(0);
    int k = 0;
    float equatorDiff = (M_PI) / (equators + 1);
    float meridianDiff = (2 * M_PI) / (meridians);
    for (int i = 1; i <= equators ; i++)
    {
        //cout << i << endl;
        for (int j = 0; j < meridians; j++)
        {   
            k++;
            //cout << k << endl;
            points[k].x = x0 + r * sin(0 + (i * equatorDiff)) * cos(j * meridianDiff);
            points[k].y = y0 + r * sin(0 + (i * equatorDiff)) * sin(j * meridianDiff);
            points[k].z = z0 + r * cos(0 + (i * equatorDiff));
            
        }
    }

    ofstream outfile;
    outfile.open("sphere.vtk");

    outfile << "# vtk DataFile Version 2.0" << endl;
    outfile << "sfera"<< endl;
    outfile << "ASCII" << endl;
    outfile << "DATASET POLYDATA" << endl;
    outfile << "POINTS " << equators * meridians + 2 << " float" << endl;

    for (int i = 0; i < (equators * meridians + 2); i++)
    {
        outfile << points[i].x << " " << points[i].y << " " << points[i].z << endl;
    }
    

    //*******budem musiet zmenit meridians*4 aby to sedelo aj pre rozne ine hodnoty meridians a equators

    outfile << "POLYGONS " << 2*(meridians * (equators-1))+2*meridians  << " " << (2 * (meridians * (equators - 1)) + 2 * meridians) * 4 << endl;
    for (int i = 0; i < meridians ; i++)
    {
        if (i == meridians) {
            outfile << 3 << " " << "0" << " " << i + 1 << " " << "1" << endl;
        }
        else {
            outfile << 3 << " " << "0" << " " << i + 1 << " " << i + 2 << endl;
        }
    }
    int p = 0;
    for (int i = 1; i < equators; i++)
    {
        //cout << i << endl;
        for (int j = 0; j < meridians; j++)
        {
            p++; 
            if (j == meridians - 1) {
                outfile << 3 << " " << p << " " << p + meridians << " " << p -meridians +1 << endl;
                outfile << 3 << " " << p - meridians + 1 << " " << p + meridians << " " << p+1 << endl;
            }
            else {
                outfile << 3 << " " << p << " " << p + meridians << " " << p + 1 << endl;
                outfile << 3 << " " << p + 1 << " " << p + meridians << " " << p + meridians + 1 << endl;
            }
        }
        p = meridians * i;
    }
    int t = meridians*(equators-1)+1;
    for (int i = 0; i < meridians; i++)
    {
        if (i == meridians-1) {
            outfile << 3 << " " << t + i  << " " << t   << " " << meridians * equators + 1 << endl;
        }
        else {
            outfile << 3 << " " << t + i  << " " << t + i +1 << " " << meridians * equators + 1 << endl;
        }
    }
    //outfile << endl;
    //for (int i = 0; i < n; i++)
    //{
    //    if (i == n - 1) {
    //        outfile << "3" << " " << i << " " << "0" << " " << n << endl;
    //    }
    //    else {
    //        outfile << "3" << " " << i << " " << i + 1 << " " << n << endl;
    //    }

    //}

    outfile.close();
    delete[]points;
    points = NULL;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
