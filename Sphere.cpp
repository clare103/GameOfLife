//
//  Sphere.cpp
//  GameOfLife
//
//  Created by David Clare on 3/29/14.
//  Copyright (c) 2014 David Clare. All rights reserved.
//

#include "Sphere.h"

Sphere::Sphere(){
    
}
Sphere::~Sphere()
{
    
}

void Sphere::menu()
{
    sphere_mode_config_text();
}
void Sphere::sphere_mode_config_text()
{
    int random =0;
    int generation_settings=0;
    cout << "Please enter if you would like a random configuration or would like a flat_file configuration:" << endl;
    cout << "Enter 1 for a random_configuration or enter 2 for a flat_file configuration:" << endl;
    cin >> random;
    if(random < 1 || random > 2)
    {
        cout << "Invalid input. Exiting program";
        exit(1);
    }
    set_random(random);
    
    cout << "Please enter if you would like to have a brief pause after every generation, press enter after every generation, or output the generations to a text file one your desktop." << endl;
    cout << "Please press 1 for a pause, 2 for enter, or 3 for output to a file" << endl;
    cin >> generation_settings;
    set_generation_settings(generation_settings);
    if(generation_settings < 1 || generation_settings > 3)
    {
        cout << "Invalid input. Exiting program";
        exit(1);
    }
    
    calculate_random_mode();
}

void Sphere::calculate_random_mode()
{
    if(get_random() == 1)
    {
        enter_dimensions();
        random_board();
    }
    else
    {
        flat_file_config();
    }
}
void Sphere::calculate_generation_settings()
{
    if(get_generation_settings() == 1)
    {
        sleep_f();
    }
    else if(get_generation_settings() == 2)
    {
        pressentertocontinue();
    }
}
void Sphere::calculate_generation_settings_output()
{
    if(get_generation_settings() == 3)
    {
        output_gen_tofile(get_myArray(), get_height(), get_width());
    }
}
void Sphere::sleep_f()
{
    cout << "Brief pause" << endl;
    sleep(5);
}
void Sphere::set_random(int a)
{
    random = a;
}
void Sphere::set_generation_settings(int a)
{
    generation_settings= a;
}

int Sphere::get_random()
{
    return random;
}
int Sphere::get_generation_settings()
{
    return generation_settings;
}

void Sphere::enter_dimensions()
{
    int r;
    cout << "Please enter the height:";
    cin >> height;
    set_height(height);
    
    cout << "Please enter the width:";
    cin >> width;
    set_width(width);
    
    cout << "Please enter a number between 1-100, this number will represent the density of the grid" << endl;
    cout << "For example, if the number you enter is 80 then there is an 80% chance that the cell will be populated" << endl;
    cin >> r;
    set_random_percent(r);
    
}

void Sphere::set_file(string a)
{
    file = a;
}
string Sphere::get_file()
{
    return file;
}


void Sphere::flat_file_config()
{
    string stuff, next2;
    DIR *dir;
    struct dirent *ent;
    string filename11 = "sample1.txt";
    const char *directory_name = "/Users/davidclare/Desktop/";
    
    outfile_name = directory_name + filename11;
    set_outfile_name(outfile_name);
    
    if ((dir = opendir(directory_name)) != NULL) {
        //print all the files and directories within directory //
        while ((ent = readdir (dir)) != NULL) {
            string s1= "SAMPLE.txt";
            string stuff = directory_name + (string)ent->d_name;
            if(stuff.find(s1) != string::npos)
            {
                set_file(stuff);
                cout << stuff << endl;
                cout << endl;
                cout << "The contents are: " << endl;
                ifstream inFile(get_file());
                inFile.open(get_file());
                next2.assign((istreambuf_iterator<char>(inFile)),
                             istreambuf_iterator<char>());
                if(next2 != "")
                {
                    
                    cout << next2 << endl;
                    char a = next2[0];
                    string b;
                    b+= a;
                    int c = atoi(b.c_str());
                    set_height(c);
                    a = next2[2];
                    b ="";
                    b += a;
                    c = atoi(b.c_str());
                    set_width(c);
                    
                    char** myArray = 0;
                    myArray = new char*[get_height()];
                    for(unsigned int x=0; x < get_height(); x++)
                    {
                        myArray[x] = new char[get_width()];
                    }
                    cout << endl;
                    int count =0;
                    int size = next2.size();
                    for(int i =0; i < size; ++i)
                    {
                        if(isdigit(next2[i]) || next2[i] == '\n')
                        {
                            count++;
                            for(int z=i; z < size; z++)
                            {
                                next2[z] = next2[z+1];
                            }
                            size--;
                        }
                    }
                    
                    int new_next_size = next2.size()-count;
                    char new_next[new_next_size];
                    for(int i=0; i < new_next_size; ++i)
                    {
                        new_next[i] = next2[i];
                    }
                    count=1;
                    for(int i =0; i < get_height(); ++i)
                    {
                        for(int g =0; g < get_width(); ++g)
                        {
                            if(i >= 1 && i < get_height()-1 && g >= 1 && g < get_width()-1)
                            {
                                count++;
                                myArray[i][g] = new_next[count];
                                cout << myArray[i][g];
                            }
                            else
                            {
                                myArray[i][g] = '-';
                                cout << myArray[i][g];
                            }
                        }
                        cout << endl;
                    }
                    while(check == true)
                    {
                        nextstate(myArray, get_height(), get_width());
                    }
                }
                else if(next2 == "")
                {
                    cout << "The contents of the file is empty." << endl;
                }
                inFile.close();
                cout << endl;
            }
        }
        closedir (dir);
    }
    else
    {
        // could not open directory
        perror ("");
        //return EXIT_FAILURE;
    }
}

void Sphere::set_outfile_name(string a)
{
    outfile_name = a;
}
string Sphere::get_outfile_name()
{
    return outfile_name;
}

void Sphere::set_myArray(char **b)
{
    **myArray = **b;
}
char** Sphere::get_myArray()
{
    return myArray;
}

void Sphere::output_gen_tofile(char **a, int height, int width)
{
    string filename = "sample1.txt";
    string directory = "/Users/davidclare/Desktop/";
    
    
    ofstream outfile;
    outfile_name = directory + filename;
    set_outfile_name(outfile_name);
    
    outfile.open(outfile_name, ofstream::in | ofstream::out | ofstream::app);
    
    outfile << "Next Gen:" << endl;
    for(int i =0; i < height; ++i)
    {
        for(int g =0; g < width; ++g)
        {
            outfile << a[i][g];
        }
        outfile << endl;
    }
    outfile.close();
}

void Sphere::pressentertoexit()
{
    cout << "Press the enter key to exit, you may have to press enter twice.";
    cin.get();
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n');
    exit(1);
}

void Sphere::pressentertocontinue()
{
    std::cout << "Press ENTER to continue... " << flush;
    std::cin.ignore( std::numeric_limits <std::streamsize> ::max(), '\n' );
}

void Sphere::random_board()
{
    srand(time(0));
    char** myArray = 0;
    myArray = new char*[get_height()];
    for(unsigned int x=0; x < get_height(); x++)
    {
        myArray[x] = new char[get_width()];
    }
    for(int i=0; i < get_height(); ++i)
    {
        for(int g=0; g < get_width(); ++g)
        {
            
            if(i>=1 && i <= get_height()-2 && g >= 1 && g <= get_width()-2)
            {
                int r = 1 + rand()%100;
                set_random_number(r);
                if(get_random_number() > get_random_percent())
                {
                    myArray[i][g] = '-';
                    cout << myArray[i][g];
                }
                else
                {
                    myArray[i][g] = 'X';
                    cout<< myArray[i][g];
                }
            }
            
            else if( i == 0 && g == 0)
            {
                myArray[i][g] = '0';
                cout << myArray[i][g];
            }
            else if(i == get_height() -1 && g == 0)
            {
                myArray[i][g] = '0';
                cout << myArray[i][g];
            }
            else if(i == 0 && g == get_width()-1)
            {
                myArray[i][g] = '0';
                cout << myArray[i][g];
            }
            else if(i == get_height()-1 && g == get_width()-1)
            {
                myArray[i][g] = '0';
                cout << myArray[i][g];
            }
            else
            {
                myArray[i][g] = '-';
                cout << myArray[i][g];
            }
        }
        cout << endl;
    }
    for(int i=0; i < get_height(); i++)
    {
        for(int g =0 ; g < get_width(); ++g)
        {
            if(i == 0 && g > 0 && g < get_width()-1)
            {
                myArray[i][g] = myArray[get_height()-2][g];
            }
            else if(i == get_height()-1 && g > 0 && g < get_width()-1)
            {
                myArray[i][g] = myArray[1][g];
            }
            else if(g== 0 && i >0 && i < get_height()-1)
            {
                myArray[i][g] = myArray[i][get_width()-2];
            }
            else if(g == get_width()-1 && i > 0 && i < get_height()-1)
            {
                myArray[i][g] = myArray[i][1];
            }
            else if( i == 0 && g == 0)
            {
                myArray[i][g] = myArray[get_height()-2][get_width()-2];
            }
            else if(i == get_height() -1 && g == 0)
            {
                myArray[i][g] = myArray[1][get_width()-2];
            }
            else if(i == 0 && g == get_width()-1)
            {
                myArray[i][g] = myArray[get_height()-2][1];
            }
            else if(i == get_height()-1 && g == get_width()-1)
            {
                myArray[i][g] = myArray[1][1];
            }
            
            
        }
    }
    cout << endl;
    cout << "Transpose" << endl;
    cout << endl;
    for(int i=0; i < get_height(); ++i)
    {
        for(int g =0 ; g < get_width(); ++g)
        {
            cout << myArray[i][g];
        }
        cout << endl;
    }
    cout << endl;
    cout << endl;
    while(check == true)
    {
        nextstate(myArray, get_height(), get_width());
    }
};

void Sphere::switchboard(char **a, char **b, int height, int width)
{
    calculate_generation_settings();
    cout << endl;
    cout << "Next Gen: " << endl;
    for(int r=0; r < height; r++)
    {
        for(int c=0; c < width; c++)
        {
            a[r][c] = b[r][c];
            cout << a[r][c];
        }
        cout << endl;
    }
    if(get_generation_settings() == 3)
    {
        output_gen_tofile(a, get_height(), get_width());
    }
}


int Sphere::count_x(char **a,int r, int c)
{
    int count =0;
    
    if(a[r-1][c-1]=='X')
    {
        ++count;
    }
    if(a[r-1][c]=='X')
    {
        ++count;
    }
    if(a[r-1][c+1]=='X')
    {
        ++count;
    }
    
    if(a[r][c-1]=='X')
    {
        ++count;
    }
    
    if(a[r][c+1]=='X')
    {
        ++count;
    }
    if(a[r+1][c-1]=='X')
    {
        ++count;
    }
    if(a[r+1][c] == 'X')
    {
        ++count;
    }
    if(a[r+1][c+1] == 'X')
    {
        ++count;
    }
    
    set_count(count);
    return count;
    
}
void Sphere::set_count(int a)
{
    count = a;
}
int Sphere::get_count()
{
    return count;
}

void Sphere::nextstate(char **a, int height, int width)
{
    char** nextArray = 0;
    nextArray = new char*[height];
    for(unsigned int x=0; x < height; x++)
    {
        nextArray[x] = new char[width];
    }
    for(int i=0; i < height; i++)
    {
        for(int g=0; g < width; g++)
        {
            nextArray[i][g] = '-';
        }
    }
    for(int r=1; r < get_height()-1; r++)
    {
        for(int c=1; c < get_width()-1; c++)
        {
            count_x(a,r,c);
            
            if(a[r][c] == 'X' && get_count() <=1)
            {
                nextArray[r][c]='-';
            }
            else if(a[r][c] == '-' && get_count() == 2)
            {
                nextArray[r][c] = '-';
            }
            else if(a[r][c] == 'X' && (get_count() == 2 || get_count() == 3))
            {
                nextArray[r][c] = 'X';
            }
            else if(a[r][c] == '-' && get_count() == 3)
            {
                nextArray[r][c]='X';
            }
            else if(a[r][c] == 'X' && get_count() > 3)
            {
                nextArray[r][c] = '-';
            }
            
        }
    }
    for(int i=0; i < get_height(); i++)
    {
        for(int g =0 ; g < get_width(); ++g)
        {
            if(i == 0 && g > 0 && g < get_width()-1)
            {
                nextArray[i][g] = nextArray[get_height()-2][g];
            }
            else if(i == get_height()-1 && g > 0 && g < get_width()-1)
            {
                nextArray[i][g] = nextArray[1][g];
            }
            else if(g== 0 && i >0 && i < get_height()-1)
            {
                nextArray[i][g] = nextArray[i][get_width()-2];
            }
            else if(g == get_width()-1 && i > 0 && i < get_height()-1)
            {
                nextArray[i][g] = nextArray[i][1];
            }
            
        }
    }
    
    if(non_trivial(a, nextArray, height, width) == false)
    {
        switchboard(a, nextArray, height, width);
    }
    else
    {
        cout << "You have reached a non trivial solution." << endl;
        pressentertoexit();
    }
}

bool Sphere::non_trivial(char **a, char **b, int height, int width)
{
    int count = 0;
    for(int i =0; i < height; ++i)
    {
        for(int g =0; g < width; g++)
        {
            if(a[i][g] == b[i][g])
            {
                count++;
            }
        }
    }
    if(count == (get_height()*get_width()))
    {
        check = false;
        return true;
    }
    else
    {
        return false;
    }
};

void Sphere::set_random_number(int r)
{
    random_number = r;
};
int Sphere::get_random_number()
{
    return random_number;
}
void Sphere::set_random_percent(int r)
{
    random_percent = r;
};
int Sphere::get_random_percent()
{
    return random_percent;
}

void Sphere::set_width(int n)
{
    width = n+2;
}
void Sphere::set_height(int n)
{
    height = n+2;
}
int Sphere::get_height()
{
    return height;
}
int Sphere::get_width()
{
    return width;
}