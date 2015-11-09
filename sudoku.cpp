/*
 * sudoku.cpp
 *
 *  Created on: 5 Mar 2014
 *      Author: xc3913
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;


bool check_available(int position, int array[][9]);
void backtrack(int array[][9], int count);



int main(int argc, char*argv[]){
	int count=0;
	int sudoku[9][9];
	ifstream infile;

	infile.open(argv[1]);

	if(!infile.is_open()){
		cout<<"File is not found"<<endl;
		exit(EXIT_FAILURE);
	}

	int temp_number;
	int i=0, j=0;
	for(i=0;i<9;i++){
		for(j=0;j<9;j++){
			infile>>temp_number;
			sudoku[i][j]=temp_number;
		}
	}
	infile.close();
	backtrack(sudoku,count);


	return 0;
}


bool check_available(int position, int array[][9]){
	int row=position/9;
	int col=position%9;
		//check repeativity in horizontal line;
	for(int i=0;i<9;i++){
		if(i==col){
			continue;
		}
		else if(array[row][col]==array[row][i]){
			return false;
		}
	}

		//check repeativity in vertical line
	for(int i=0;i<9;i++){					;
			if(i==row){
				continue;
			}
			else if(array[row][col]==array[i][col]){
				return false;
			}
		}

		//check boxes;
	int box_row=(row/3)*3, box_col=(col/3)*3;
	for(int i=box_row;i<box_row+3;i++){
		for(int j=box_col;j<box_col+3;j++){
			if(col==j && row==i){
				continue;
			}
			else if(array[row][col]==array[i][j]){
				return false;
			}
		}
	}

	return true;
}


void backtrack(int array[][9],int count){
	clock_t start_time=clock();
	if(count==81){
		//cout<<"222"<<endl;
		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				cout<<array[i][j]<<" ";
			} cout<<endl;
		}


		terminate();					//terminate the program so that it wont recurse back
	}

	else if(array[count/9][count%9]==0){															//if cell filled
		for(int i=1;i<10;i++){
			array[count/9][count%9]=i;
			//cout<<"3"<<endl;

			if(check_available(count, array)){								//trying is valid;

				backtrack(array, count+1);									//im not using count++ or ++count, because dont expect to change value of count in this for loop

			}
		}

		array[count/9][count%9]=0;

	}else{
		backtrack(array, count+1);
	}

	return;
}
