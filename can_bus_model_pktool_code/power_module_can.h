#ifndef POWER_MODULE_CAN_H
#define POWER_MODULE_CAN_H
#include "can.h"
// ----------------------------------------------------------------------------
//  CLASS : can power_module
//  power_module associated to can_node sc_module
// -----------------------------------------------------------------------------
POWER_MODULE_CLASS( can_node )
{

	PK_USES_ENERGY_MODELS

	// constructor
	POWER_MODULE_CTOR(can_node)
	{
		PK_MODULE_SENSITIVITY
		sensitive<<clock.pos();
	};
};

// ----------------------------------------------------------------------------
//  CLASS : wrapper sc_module
//
//  sc_module wrapping a can_node power_module created dynamically
// -----------------------------------------------------------------------------

SC_MODULE(wrapper)
{

	sc_in_clk clock;
	sc_in<bit > access_granded, bus_tx;
	sc_in< sc_uint<32> > rx_id, rx_data;
	sc_out< sc_uint<32> > tx_data, tx_id;
	sc_out< bit > access_req;

	// power_module pointer
	POWER_MODULE(can_node)*  dyn_cannode ;
	SC_CTOR(wrapper)
	{
		//power_module creation
		dyn_cannode = new POWER_MODULE(can_node)("dyn_cannode");
		//connection instructions
		dyn_cannode->clock(clock);
		dyn_cannode->access_granded(access_granded);
		dyn_cannode->rx_id(rx_id);
		dyn_cannode->rx_data(rx_data);
		dyn_cannode->bus_tx(bus_tx);
		dyn_cannode->tx_id(tx_id);
		dyn_cannode->tx_data(tx_data);
		dyn_cannode->access_req(access_req);
	};
};
#endif
