#include <systemc-ams>
#include <cmath>

// Sine wave generator module
SCA_TDF_MODULE(sine_generator) {
    sca_tdf::sca_out<double> out;
    
    sine_generator(sc_core::sc_module_name nm, double ampl_=1.0, double freq_=1.0)
        : out("out"), ampl(ampl_), freq(freq_), phase(0.0) {}
    
    void processing() {
        phase += 2.0 * M_PI * freq * get_timestep().to_seconds();
        if (phase >= 2.0 * M_PI) phase -= 2.0 * M_PI;
        out.write(ampl * sin(phase));
    }
    
    void set_attributes() {
        set_timestep(sca_core::sca_time(10, sc_core::SC_MS)); // 10ms timestep
    }
    
private:
    double ampl, freq, phase;
};

// Consumer module that traces the signal
SCA_TDF_MODULE(trace_consumer) {
    sca_tdf::sca_in<double> in;
    sca_util::sca_trace_file* tf;
    
    trace_consumer(sc_core::sc_module_name nm) 
        : in("in"), tf(sca_util::sca_create_vcd_trace_file("tdf_trace")) {
        // Trace the input signal
        sca_trace(tf, in, "sine_wave");
    }
    
    ~trace_consumer() {
        // Close the trace file
        sca_util::sca_close_vcd_trace_file(tf);
    }
    
    void processing() {
        // Just pass through - tracing happens automatically
    }
};

// Top-level module
SC_MODULE(top) {
    sine_generator *gen;
    trace_consumer *cons;
    sca_tdf::sca_signal<double> sig;
    
    SC_CTOR(top) {
        gen = new sine_generator("gen", 1.0, 0.5); // 1.0 amplitude, 0.5Hz frequency
        cons = new trace_consumer("cons");
        
        // Connect the modules
        gen->out(sig);
        cons->in(sig);
    }
};

int sc_main(int argc, char* argv[]) {
    top t1("t1");
    
    sc_core::sc_start(2.0, sc_core::SC_SEC); // Simulate for 2 seconds
    
    return 0;
}
