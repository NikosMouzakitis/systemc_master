#include "thermal_model.h"
#include "mesh_router.h"

ThermalModel::ThermalModel(int mesh_size)
	: mesh_size(mesh_size),
	  router_temps(mesh_size, std::vector<double>(mesh_size, AMBIENT)),
	  router_ptrs(mesh_size, std::vector<MeshRouter*>(mesh_size, nullptr)) {}

void ThermalModel::set_router_ptr(int x, int y, MeshRouter* router) {
	router_ptrs[y][x] = router;
}
void ThermalModel::update_temperatures() {

	for(int y=0; y<router_temps.size(); y++) {
		for(int x=0; x<router_temps[y].size(); x++) {

			if(router_ptrs[y][x]) {
				// Update activity first
				router_ptrs[y][x]->update_activity();

				// Get normalized activity (0-1)
				double activity = router_ptrs[y][x]->get_activity_factor();
				cout << "for " << y << " , " << x << endl;
				cout <<  " activity " << activity << endl;
				cout <<  " router_temp1 " << router_temps[y][x] << endl;

				// Apply heating proportional to activity
				router_temps[y][x] += activity * MAX_HEATING;

				cout << " router_temp2 " << router_temps[y][x] << endl;
				// Apply cooling
				router_temps[y][x] -= COOLING * (router_temps[y][x] - AMBIENT);
				cout << " router_temp3 " << router_temps[y][x] << endl;

				// Clamp to reasonable values
				//    router_temps[y][x] = std::clamp(router_temps[y][x], AMBIENT, MAX_TEMP);
				cout << " router_temp4 " << router_temps[y][x] << endl;
			}


			// Heat transfer between neighbors (simplified)
			if (x > 0) {  // West
				double diff = router_temps[y][x-1] - router_temps[y][x];
				router_temps[y][x] += HEAT_TRANSFER_COEFF * diff;
			}
			if (y > 0) {  // North
				double diff = router_temps[y-1][x] - router_temps[y][x];
				router_temps[y][x] += HEAT_TRANSFER_COEFF * diff;
			}
			if (x < mesh_size - 1) {  // East
				double diff = router_temps[y][x+1] - router_temps[y][x];
				router_temps[y][x] += HEAT_TRANSFER_COEFF * diff;
			}
			if (y < mesh_size - 1) {  // South
				double diff = router_temps[y+1][x] - router_temps[y][x];
				router_temps[y][x] += HEAT_TRANSFER_COEFF * diff;
			}
		}
	}
}
double ThermalModel::get_temperature(int x, int y) const {
	return router_temps[y][x];
}
