//
// Created by gaagaagi on 2026-03-17.
//

#ifndef ORBITAL_MECHANICS_SIMULATION_STATE_H
#define ORBITAL_MECHANICS_SIMULATION_STATE_H

#include "app_state.h"
#include "draw_state.h"

class SimulationState : public AppState {
public:
    void handle_input() override;
    void update() override;
    void draw() override;
    void onEnter() override;
    void onExit() override;

    SimulationState(Camera2D* camera, std::vector<Shape>* shapes);

    AppState* drawState; // pointer to the draw state so we can switch to it when needed

};


#endif //ORBITAL_MECHANICS_SIMULATION_STATE_H