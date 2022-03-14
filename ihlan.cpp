// ihlan.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
    int height = 3;
    int n = 12;
    int r = 4;
    
    POINTS *points = new POINTS[n];

    for (int i = 0; i < n; i++)
    {
        points[i].x = r * cos(i * (2 * M_PI)/n);
        points[i].y = r * sin(i * (2 * M_PI)/n);
        points[i].z = 0;
    }

    ofstream outfile;
    outfile.open("ihlan_5_tyzden.vtk");

    outfile << "# vtk DataFile Version 2.0" << endl;
    outfile << "ihlan s " << n << " bodovou podstavou" << endl;
    outfile << "ASCII" << endl;
    outfile << "DATASET POLYDATA" << endl;
    outfile << "POINTS " << n + 1 << " float" << endl;

    for (int i = 0; i < n; i++)
    {
        outfile << points[i].x << " " << points[i].y << " " << points[i].z << endl;
    }
    outfile << "0" << " " << "0" << " " << height << endl;


    //zakomentovavame kvoli farbeniu. Moze to ratat ako plochy na farbenie
    /*outfile << "LINES " << n * 2 << " " << n*2*3 << endl;
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1) {
            outfile << "2" << " " << i << " " << 0 << endl;
        }
        else {
            outfile << "2" << " " << i << " " << i + 1 << endl;
        }
        outfile << "2" << " " << i << " " << n << endl;
    }*/
    outfile << "POLYGONS " << n + 1 << " " << n * 2 * 2 << endl;
    outfile << n << " ";
    for (int i = 0; i < n; i++)
    {
        outfile << i << " ";
    }
    outfile << endl;
    for (int i = 0; i < n; i++)
    {
        if (i == n - 1) {
            outfile << "3" << " " << i << " " << "0" << " " << n << endl;
        }
        else {
            outfile << "3" << " " << i << " " << i + 1 << " " << n <<endl;
        }
        
    }

    //5te cvicenie, skalarne hodnor=ty na bunkach generovanych pomocou LOOKUP_TABLE

    outfile << "CELL_DATA " << n + 1 << endl;
    outfile << "SCALARS cell_scalars int 1" << endl;
    outfile << "LOOKUP_TABLE default" << endl;
    for (int i = 0; i < n+1; i++)
    {
        outfile << i << endl;
    }



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
