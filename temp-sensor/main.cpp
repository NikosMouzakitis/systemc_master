#include <systemc.h>
#include <cstdlib>
#include <ctime>

// Define the Sensor class
SC_MODULE(TemperatureSensor) {
    sc_out<int> sensor_value;  // Output port for sensor data

    // Constructor
    SC_CTOR(TemperatureSensor) {
        SC_THREAD(sensor_process);  // Process to simulate sensor readings
        srand(time(0));  // Initialize random seed
    }

    // Simulate sensor reading with random temperature values between 0 and 100
    void sensor_process() {
        while (true) {
            int temp = rand() % 101;  // Random temperature between 0 and 100
            sensor_value.write(temp);  // Send temperature value to output
            wait(10, SC_SEC);  // Wait for 10 seconds (simulation time)
        }
    }
};

// Top module to test the sensor
SC_MODULE(TopModule) {

    sc_signal <int> sensor_signal;  // Signal to connect the sensor to other modules

    TemperatureSensor sensor;  // Instance of the sensor module

    // Constructor
    SC_CTOR(TopModule) : sensor("sensor") {
        sensor.sensor_value(sensor_signal);  // Connect sensor output to the signal
        // Monitor the sensor's output
        SC_THREAD(monitor_sensor);
    }

    // Monitor and print the sensor value
    void monitor_sensor() {
        while (true) {
            wait(sensor_signal.value_changed_event());  // Wait until the value changes
            std::cout << "Sensor Value: " << sensor_signal.read() << "@" << sc_time_stamp() <<  std::endl;
        }
    }
};

int sc_main(int argc, char* argv[]) {
    TopModule top("top");  // Instantiate the top module

    sc_start();  // Start the simulation

    return 0;
}
