#include <iostream>
#include <numeric>
#include "gridworld/gridworld.h"




int main()
{
    int rows = 4;
    int cols = 4;
    int states = rows * cols;
    int actions = 4;

    GridWorld gridworld(rows, cols);
    std::vector<std::vector<float>> v_s = gridworld.state_values;
    std::vector<std::vector<float>> r_s = gridworld.reward_values;

    gridworld.printGridWorld(v_s);

    // Value Iteration to find the Optimal Point
    int it = 100;
    float theta = 0.01;
    float delta = 0.0;
    float gamma = 0.9;

    while (true) {
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                float v = v_s[r][c];
                std::vector<float> v_s_k;
                if (r == std::get<0>(gridworld.endPoint) && c == std::get<1>(gridworld.endPoint) or
                    r == std::get<0>(gridworld.burn) && c == std::get<1>(gridworld.burn)) {
                    ;
                }
                else {
                    for (Action action : {Action::UP, Action::DOWN, Action::LEFT, Action::RIGHT}) {
                        int next_col = std::get<1>(gridworld.get_next_state(r, c, action));
                        int next_row = std::get<0>(gridworld.get_next_state(r, c, action));
                        v_s_k.push_back((0.8 * gamma * v_s[next_row][next_col]));// + (0.1 * gamma * v_s[next_row][next_col]) + (0.1 * gamma * v_s[next_row][next_col]));
                    }

                   
                    // find the max element
                    auto max_iter = std::max_element(v_s_k.begin(), v_s_k.end());
                    if (max_iter != v_s_k.end()) {
                        v_s[r][c] = *max_iter;
                    }
                }
                // Check whether new state value is greater than previous state value.
                //float d = abs(v - v_s[r][c]);
                //delta = std::max(delta, d);
                //delta = d;
                //std::cout << "D: " << d << "\tDelta: " << delta << "\n";
            }
        }

        gridworld.printGridWorld(v_s);

        //Check for convergence to know whether to stop.
       /* if (delta < theta) {
            std::cout << "Final Delta: " << delta << "\n";
            break;
        }*/
        it--;
    }


    //Print final grid
    gridworld.printGridWorld(v_s);
}



//float sum_of_elems = 0;
//for (std::vector<float>::iterator it = v_s_k.begin(); it != v_s_k.end(); ++it)
//sum_of_elems += *it;
//std::cout << sum_of_elems << "\n";
//v_s[r][c] = sum_of_elems;