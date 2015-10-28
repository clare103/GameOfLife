//
//  Torus.h
//  GameOfLife
//
//  Created by David Clare on 2/26/14.
//  Copyright (c) 2014 David Clare. All rights reserved.
//

#ifndef __GameOfLife__Torus__
#define __GameOfLife__Torus__

#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

class Torus
{
public:
    Torus();
    ~Torus();
    
    void set_width(int);
    void set_height(int);
    
    int get_width();
    int get_height();
    
    void enter_dimensions();
    
    void set_random_percent(int);
    int get_random_percent();
    
    void set_random_number(int);
    int get_random_number();
    
    void pressentertoexit();
    void flat_file_config();
    void set_file(string);
    string get_file();
    
    void set_outfile_name(string);
    string get_outfile_name();
    void output_gen_tofile(char **a, int, int);
    
    int count_x(char **a, int , int);
    
    void pressentertocontinue();
    
    void torus_mode_config_text();
    void calculate_random_mode();
    
    void calculate_generation_settings();
    void calculate_generation_settings_output();
    
    void sleep_f();
    void random_mode_text();
    
    void set_random(int);
    void set_generation_settings(int);
    int get_random();
    int get_generation_settings();
    
    void set_count(int);
    int get_count();
    
    bool non_trivial(char **a, char **b, int height, int width);
    
    void random_board();
    void switchboard(char **a, char **b, int , int);
    void nextstate(char **a, int, int);
    
    void set_myArray(char **b);
    char **get_myArray();
    
    void menu();
    
private:
    int height, width, random_percent, random_number, count, generation_settings, random;
    char **myArray;
    string file, outfile_name;
};

#endif /* defined(__GameOfLife__Torus__) */
