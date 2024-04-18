#pragma once

#include <iostream>
#include <vector>
#include <random>
#include <tuple>

enum class Action { UP, DOWN, LEFT, RIGHT };

class GridWorld {
public:
	int rows;
	int columns;

	std::tuple<int, int> startPoint;
	std::tuple<int, int> endPoint;
	std::tuple<int, int> wallPoint;
	std::tuple<int, int> burn;

	std::vector<std::vector<float>> state_values;
	std::vector<std::vector<float>> reward_values;


	GridWorld(int &rows, int &columns) :rows(rows), columns(columns) {
		// Generate Initial State Values for each State
		for (int i = 0; i < rows; ++i) {
			std::vector<float> state_values_ph;
			for (int j = 0; j < columns; ++j) {
				state_values_ph.push_back(0);
			}
			state_values.push_back(state_values_ph);
			state_values_ph.clear();
		}

		// Generate Reward Values for each State
		for (int i = 0; i < rows; ++i) {
			std::vector<float> reward_values_ph;
			for (int j = 0; j < columns; ++j) {
				reward_values_ph.push_back(0);
			}
			reward_values.push_back(reward_values_ph);
			reward_values_ph.clear();
		}

		pickStartPoint();
		pickTerminalPoint();

		
	};

	void pickStartPoint(){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis_row(0, rows-1);
		std::uniform_int_distribution<int> dis_col(0, columns-1);
		startPoint = { dis_row(gen), dis_col(gen) };
	}

	void pickTerminalPoint(){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis_row(0, rows-1);
		std::uniform_int_distribution<int> dis_col(0, columns-1);
		endPoint = { dis_row(gen), dis_col(gen) };
		
		state_values[std::get<0>(endPoint)][std::get<1>(endPoint)] = 1;
		burn = get_next_state(std::get<0>(endPoint), std::get<1>(endPoint), Action::DOWN);
		state_values[std::get<0>(burn)][std::get<1>(burn)] = -1;
		reward_values[std::get<0>(endPoint)][std::get<1>(endPoint)] = 1;
	}

	void addRandomWalls(){
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> dis_row(0, rows);
		std::uniform_int_distribution<int> dis_col(0, columns);
		wallPoint = { dis_row(gen), dis_col(gen) };
		state_values[std::get<0>(wallPoint)][std::get<1>(wallPoint)] = -1;
	}

	// Function to get the next state given the current state and action
	std::tuple<int, int> get_next_state(int row, int col, Action action) {
		switch (action) {
		case Action::UP:
			if (row > 0) return std::make_tuple(row - 1, col);
			break;
		case Action::DOWN:
			if (row < rows - 1) return std::make_tuple(row + 1, col);
			break;
		case Action::LEFT:
			if (col > 0) return std::make_tuple(row, col - 1);
			break;
		case Action::RIGHT:
			if (col < columns - 1) return std::make_tuple(row, col + 1);
			break;
		}
		// If the action leads to an invalid state, return the current state
		return std::make_tuple(row, col);
	}

	void printGridWorld(std::vector<std::vector<float>> &state_values){
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				std::cout << state_values[i][j] << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << "Start Point: \t" << std::get<0>(startPoint) << " , " << std::get<1>(startPoint) << std::endl;
		std::cout << "Terminal Point: \t" << std::get<0>(endPoint) << " , " << std::get<1>(endPoint) << std::endl;
	}
};