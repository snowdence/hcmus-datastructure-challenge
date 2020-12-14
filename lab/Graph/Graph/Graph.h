#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;
enum GraphInputType {ADJ_LIST, ADJ_MATRIX};
class Graph
{
private:
	int _np = 0;
	vector<vector<int>> _adj_list; 
	vector<vector<int>> _adj_matrix;
public:
	Graph() {}
	vector<vector<int>> getList() {
		return _adj_list;
	}
	vector<vector<int>> getMatrix() {
		return _adj_matrix;
	}
	void readFromFile(string file) {
	
	}
	vector<vector<int>> cacheToList() {
		vector<vector<int>> newList;
		for (int i = 0; i < _np; i++) {
			vector<int> v;
			for (int j = 0; j < _np; j++) {
				if (_adj_matrix[i][j] == 1) {
					v.push_back(j);
				}
			}
			newList.push_back(v);
		}
		return newList;
	}
	vector<vector<int>> cacheToMatrix() {
		vector<vector<int>> newMatrix;
		for (auto row : _adj_list) {
			vector<int> v(_np, 0);
			for (auto el : row) {
				v[el] = 1;
			}
			newMatrix.push_back(v);
		}
		return newMatrix;
	}

	void readAdjFromFile(string file) {
		std::ifstream ifs(file);
		std::string tempstr;
		int tempint;
		char delimiter;
		std::getline(ifs, tempstr);
		_np = atoi(tempstr.c_str());
		while (std::getline(ifs, tempstr)) {
			stringstream iss(tempstr);
			std::vector<int> tempv;
			int idx = 0;
			while (iss >> tempint) {
				if(idx != 0){
					tempv.push_back(tempint);
				}
				idx++;
			}
			_adj_list.push_back(tempv);
		}
		
		this->_adj_matrix = cacheToMatrix();
	}
	void printAdjList() {
		cout << "ADJ List" << endl;

		for (auto row : _adj_list) {
			for (auto el : row) {
				std::cout << el << ' ';
			}
			std::cout << "\n";
		}
		cout << "End Adj List" << endl;
	}
	void printAdjMatrix() {
		cout << "Adj Matrix" << endl;

		for (auto row : _adj_matrix) {
			for (auto el : row) {
				std::cout << el << ' ';
			}
			std::cout << "\n";
		}
		cout << "End Adj Matrix" << endl;
	}
	void readMatrixFromFile(string file) {
		std::ifstream ifs(file);
		std::string tempstr;
		int tempint;
		char delimiter;
		std::getline(ifs, tempstr);

		_np = atoi(tempstr.c_str());
		while (std::getline(ifs, tempstr)) {
			stringstream iss(tempstr);
			std::vector<int> tempv;
			int idx = 0;
			while (iss >> tempint) {
				tempv.push_back(tempint);
				idx++;
			}
			_adj_matrix.push_back(tempv);
		}
		this->_adj_list = cacheToList();
	
	}
};

