//
//  main.cpp
//  GameOfLife
//
//  Created by David Clare on 2/25/14.
//  Copyright (c) 2014 David Clare. All rights reserved.
//

#include <iostream>
#include "Classic.cpp"
#include "Torus.cpp"
#include "Mirror.cpp"
#include "Sphere.cpp"

using namespace std;



void create_blah()
{
    
    
}

void create_3d()
{
    int first, second, third;
    first = 5;
    second = 360;
    third = 2;
    //cout << "enter first dimension for MASTER->";
    //cin >> first;
    int*** master = new int**[first];
    for(int i = 0; i < first; ++i) {
        //cout << "enter second dimension for MASTER->" << i+1 << " dimension?:";
        //cin >> second;
        master[i] = new int*[second];
        for(int j = 0; j < second; ++j) {
            //cout << "enter third dimension for MASTER->" << i+1 << "->" << j+1 << " dimension?:";
            //cin >> third;
            ++++third; //incrase third dimension to store data about dimension length's
            master[i][j] = new int[third];
            master[i][j][0] = second; //hold the value of second dimension
            master[i][j][1] = third; //hold the value of third dimensioNS for current second dimension.
            
            for(int k = 2; k < third; ++k)
                master[i][j][k] = 0; //initialize all the values to whatever
        }
    }
    cout << "\nlist of members:\n";
    for(int i = 0; i < first; ++i)
        for(int j = 0, sec = master[i][j][0]; j < sec; ++j) //second dimension is not always the same!!
            for(int k = 2; k < master[i][j][1]; ++k) //third dimension is not always the same as well!!
                cout << "MASTER->" << i+1 << "->" << j+1 << "->" << k-1 << ". member-> " << master[i][j][k] << endl;
    
    for(int i = 0; i < first; ++i) {
        for(int j = 0, sec = master[i][j][0]; j < sec; ++j) //second dimension is not always the same!!
            delete [] master[i][j];
        delete [] master[i];
    }
    delete [] master; // now it's time to kill last standing pointe
}


void main_menu()
{
    
    
    create_3d();
    /*
    int choice = 0;
    cout << "Please enter which type of mode you would like to play the game of life in" << endl;
    cout << "1.Classic Mode- The boundries off of the grid are empty." << endl;
    cout << "2.Torus Mode - The boundary of the grid is wrapped around itself as if it were a doughnut or 'Torus'." << endl;
    cout << "3.Mirror Mode- The boundaries off the grid are bounced back as reflections and the corners have a potential 3 neighbors." << endl;
    cout << "4.Sphere Mode(My personal favorite and own creation)- The grid is a sphere where the corners wrap to the inverse corner. " << endl;
    cin >> choice;
    if(choice == 1)
    {
        classic c;
        c.menu();
    }
    else if(choice == 2)
    {
        Torus t;
        t.menu();
    }
    else if(choice ==3)
    {
        Mirror m;
        m.menu();
    }
    else if(choice == 4)
    {
        Sphere s;
        s.menu();
    }
    else
    {
        cout << "Invalid input. The program will now exit. Please enter a number 1-4 next time.";
        exit(1);
    }
    */
    
}


int main(int argc, const char * argv[])
{
    main_menu();
    return 0;
};