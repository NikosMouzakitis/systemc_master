#ifndef THERMAL_MODEL_H
#define THERMAL_MODEL_H

#include "systemc.h"
#include <vector>
#include <algorithm>

class MeshRouter;

class ThermalModel {
public:
    ThermalModel(int mesh_size);
    void update_temperatures();
    double get_temperature(int x, int y) const;
    void set_router_ptr(int x, int y, MeshRouter* router);

private:
    const double AMBIENT = 45.0;
    const double MAX_TEMP = 150.0;
    const double HEAT_TRANSFER_COEFF = 0.0005;
    const double MAX_HEATING = 	 0.00028;      // Max °C increase per update
    const double COOLING =	 0.00085;     // Cooling rate
    int mesh_size; 
    std::vector<std::vector<double>> router_temps;
    std::vector<std::vector<MeshRouter*>> router_ptrs;
};

#endif
