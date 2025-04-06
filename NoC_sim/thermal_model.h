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
    const double HEAT_TRANSFER_COEFF = 0.005;
    
    std::vector<std::vector<double>> router_temps;
    std::vector<std::vector<MeshRouter*>> router_ptrs;
};

#endif
