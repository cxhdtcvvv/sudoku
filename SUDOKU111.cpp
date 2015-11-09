/*
 * SUDOKU111.cpp
 *
 *  Created on: 17 Mar 2014
 *      Author: xc3913
 */


#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include<time.h>

using namespace std;


bool check_num(int array[][9], int x,int y,int value);
void cell_availableforonly_one(int array[][9],int count_freecell);

int main(int argc, char*argv[]){
	int array[9][9];
	int count_freecell=0;
	ifstream infile;
	infile.open(argv[1]);

	if(!infile.is_open()){
		cout<<"can not open the file"<<endl;
		exit(EXIT_FAILURE);
	}

	for(int j=0;j<9;j++){
		for(int i=0;i<9;i++){
			infile>>array[i][j];			//input data to 2d array
			if(array[i][j]==0){
				count_freecell++;			//count empty cells
			}
		}
	}
	infile.close();

	cell_availableforonly_one(array, count_freecell);

	return 0;
}


bool check_num(int array[][9],int x,int y,int value){



	for(int i=0;i<9;i++){										//check if there is repeatancy in row or column
		if(array[x][i]==value||array[i][y]==value){
			return false;
		}
	}

	for(int i=(x/3)*3; i<((x/3)*3)+3; i++){						//check the repeatancy in sub grid
			for(int j=(y/3)*3; j<((y/3)*3)+3; j++){
			if(array[i][j]==value && i!=x){
				return false;
			}
		}
	}
	return true;
}


void cell_availableforonly_one(int array[][9],int count_freecell){

bool cell_assianged=1;


while((count_freecell!=0)&&(cell_assianged==1)){				//if Sudoku is not completely solved and there is no more cell can be assigned, sudoku is wrong

	cell_assianged=0;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(array[i][j]!=0){
				continue;
			}
			int temp=0;
			for(int k=1;k<10;k++){
				if(check_num(array,i,j,k)==1){
					if(temp==0){
						temp=k;
					}else{
						temp=0;						//if temp has already been assigned, this means second solution is possible. so this cell is useless, cell is still not assigned
						break;
					}
				}
			}
			if(temp!=0){				//if for a cell can be assigned by only one solution
				array[i][j]=temp;
				cell_assianged=1;
				count_freecell--;		//empty cell -1
			}
		}
	}									//finish scanning for the whole sudoku board once
}										//if there is still some empty cell, scan again


	if(count_freecell!=0){				//there is at least one cell which can not be assigned with a number
	cout<<"Sudoku is wrong"<<endl;
	}else{
		for(int j=0;j<9;j++){
		for(int i=0;i<9;i++){
			cout<<array[i][j]<<" ";
		}
			cout<<endl;
	}
}

}
