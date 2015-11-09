/*
 * HEURISTIC.cpp
 *
 *  Created on: 20 Mar 2014
 *      Author: xc3913
 */



#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

int fail=0;

using namespace std;

struct ranking{												//structure contains position of cell and its rank in term of number of assigned cells surrounding it
	int count;
	int rank;
};

bool check_available(int position, int array[][9]);
int heuristic(int array[][9], int empty_cell, int next_count);
int min_possible (vector<ranking> possible_sol);						//return the the position of cell which has minimum amount of zero around it
int around_unassignned(int array[][9],int position);					//return the number of zero around a particular cell



int main(int argc, char*argv[]){

	int sudoku[9][9];
	ifstream infile;
	int empty_cell=0;
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
			if(temp_number==0){
				empty_cell++;
			}
			sudoku[i][j]=temp_number;
		}
	}
	infile.close();

	heuristic(sudoku,empty_cell, 0);


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

int around_unassignned(int array[][9],int position){
	int row=position/9;
	int col=position%9;
	int possible=0;
	int box_row=(row/3)*3, box_col=(col/3)*3;
	int mark[10]={0,0,0,0,0,0,0,0,0,0};								//mask[0~9] represents if number 1~9 has been used in a cell's relevant cells;

	for(int i=0;i<9;i++){
		mark[array[row][i]]=1;
	}

	for(int i=0;i<9;i++){
		mark[array[i][col]]=1;
	}


	for(int i=box_row;i<box_row+3;i++){
		for(int j=box_col;j<box_col+3;j++){
			mark[array[i][j]]=1;
		}
	}

	for(int i=0; i<10;i++){
		if(mark[i]==0){
			possible++;
		}
	}
	return possible;
}

int min_possible (vector<ranking> possible_sol){				//return the count value of cell with smallest possible solution
	int min=possible_sol[0].rank;
	int temp=possible_sol[0].count;

	for(int i=0;i<possible_sol.size();i++){							//find the minimum number
		if(possible_sol[i].rank<min){
			temp=possible_sol[i].count;
			min=possible_sol[i].rank;
		}
	}
	return temp;
}


int heuristic(int array[][9],int empty_cell, int next_count){
	ranking temp;
	int count;
	vector<ranking> possible_sol;


	if(empty_cell==0){							//Base condition: there is non empty cells left

		for(int i=0;i<9;i++){
			for(int j=0;j<9;j++){
				cout<<array[i][j]<<" ";
			} cout<<endl;
		}
		cout<<endl;
		cout<<fail<<endl;
		terminate();
	}

if(next_count==0){									//check if this is first time program enter this recursion
	for(int i=0;i<81;i++){										//find out number of unassigned cells around the cell we looking at(row/col/subgrid);
		if(array[i/9][i%9]==0){
			temp.rank=around_unassignned(array,i);
			temp.count=i;
			possible_sol.push_back(temp);
		}else{
			continue;
		}
	}

	count=min_possible(possible_sol); 						//find out the cell with smallest unassigned cells around it;


}else{
	count=next_count;							//if it already entered this recursion, position of the cell we choose should be unchanged

}


	for(int k=1;k<10;k++){
		if(k==1){
			next_count=0;
		}
		array[count/9][count%9]=k;

		if(check_available(count,array)==1){

			//cout<<next_count<<endl;
			next_count=heuristic(array,empty_cell-1, next_count);				//enter the next recursion, but decrement empty_cell by one, but keep its value in this state of recursion
			fail++;
		}
	}


	array[count/9][count%9]=0;							//non of 9 solution can be assigned, set this cell back to 0, and return to last recursion

	return count;
}


