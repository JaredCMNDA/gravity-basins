//
// Created by gaagaagi on 2026-03-17.
//

#ifndef ORBITAL_MECHANICS_DRAW_STATE_H
#define ORBITAL_MECHANICS_DRAW_STATE_H

#include "app_state.h"
#include "simulation_state.h"

class DrawState : public AppState {
public:
    void handle_input() override;
    void update() override;
    void draw() override;
    void onEnter() override;
    void onExit() override;

    DrawState(Camera2D* camera, std::vector<Shape>* shapes);

    AppState* simulationState;

};


#endif //ORBITAL_MECHANICS_DRAW_STATE_H