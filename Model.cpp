#include "Model.h"

bool Model::parseArguments(int argc, char* argv[]) {
    for(int i=1; i < argc; ++i ) {
        string arg = string(argv[i]);
        if (arg == "-h" || arg == "--help") {
            printHelp();
        }
        else if (arg == "-v" || arg == "--verbose") {
            Model::verbose = true;
        }
        else if (arg == "-p" || arg == "--physics") {
            try {
                double* physical_parameters[] = {&(Model::ax), &(Model::ay), &(Model::b), &(Model::c)};
                for (auto &physical_parameter : physical_parameters) {
                    i++;
                    *physical_parameter = stod(string(argv[i]));
                }
            }
            catch(const exception& e) {
                cerr << "Error: " << e.what() << endl;
                cerr << "-p/--physics option requires four arguments of type double (ax, ay, b, c)." << endl;
                return false;
            }
        }
        else if (arg == "-t" || arg == "--time") {
            try {
                i++;
                Model::T = stod(string(argv[i]));
            }
            catch(const exception& e) {
                cerr << "Error: " << e.what() << endl;
                cerr << "-t/--time option requires one argument of type double (T in seconds)." << endl;
                return false;
            }
        }
        else if (arg == "-g" || arg == "--geometry") {
            try {
                i++;
                Model::Lx = Model::Ly = stod(string(argv[i]));
            }
            catch(const exception& e) {
                cerr << "Error: " << e.what() << endl;
                cerr << "-g/--geometry option requires one argument of type double (L in meters)." << endl;
                return false;
            }
        }
        else if (arg == "-s" || arg == "--steps") {
            try {
                unsigned int* numerical_parameters[] = {&(Model::Nx), &(Model::Ny), &(Model::Nt)};
                for (auto &numerical_parameter : numerical_parameters) {
                    i++;
                    *numerical_parameter = stoi(string(argv[i]));
                }
            } catch(const exception& e) {
                cerr << "Error: " << e.what() << endl;
                cerr << "-s/--steps option requires three positive arguments of type int (Nx, Ny, Nt)." << endl;
                return false;
            }
        } else if (arg == "-x" || arg == "processes") {
            try {
                i++;
                Px = stoi(string(argv[i]));
                i++;
                Py = stoi(string(argv[i]));
            }
            catch (const exception &e) {
                cerr << "Error: " << e.what() << endl;
                cerr << "-x option requires two arguments of type int." << endl;
            }
        }
    }
    return true;
}

bool Model::validateParameters() {
    // Validate geometric parameters
    double* geometric_parameters[] = {&(Model::Lx), &(Model::Ly), &(Model::T)};
    for (auto &parameter : geometric_parameters) {
        if(*parameter < 0) return false;
    }

    // Validate numeric parameters
    unsigned int* numeric_parameters[] = {&(Model::Nx), &(Model::Ny), &(Model::Nt)};
    for (auto &parameter : numeric_parameters) {
        if(*parameter <= 0) return false;
    }

    // Set size of steps based on number of steps
    Model::dx = Model::Lx/(Model::Nx-1);
    Model::dy = Model::Ly/(Model::Ny-1);
    Model::dt = Model::T/Model::Nt;

    return true;
}

void Model::printHelp() {
    Model::help = true;
    cerr << "Usage: " << fname << "ax ay b c <option(s)>\n"
         << "\t-p,--physics <ax> <ay> <b> <c> \tSet physics parameters (default: ax=10, ay=0, b=0, c=0)\n"
         << "\t-g,--geometry <L> \tSet the length of velocity field considered (default: L=10)\n"
         << "\t-t,--time <end time in seconds> \tSet simulation end time (default: 1s)\n"
         << "\t-s,--steps <Nx> <Ny> <Nt> \tSet simulation numeric parameters (default: Nx=20, Ny=20, Nt=20)\n"
         << "\t-h,--help\t\t\t\tShow this help message\n"
         << "\t-v,--verbose\t\t\t\tRun in verbose mode\n"
         << endl;
}

void Model::printParameters() {
    cout << "The overall model is " << (Model::valid ? "valid." : "not valid.") << "\n\n"
         << "Physics Parameters:\n"
         << "\tax\t" << ":" << "\t" << Model::ax << "\n"
         << "\tay\t" << ":" << "\t" << Model::ay << "\n"
         << "\tb\t" << ":" << "\t" << Model::b << "\n"
         << "\tc\t" << ":" << "\t" << Model::c << "\n"
         << "Geometric Parameters:\n"
         << "\tLx\t" << ":" << "\t" << Model::Lx << "\n"
         << "\tLy\t" << ":" << "\t" << Model::Ly << "\n"
         << "\tx0\t" << ":" << "\t" << Model::x0 << "\n"
         << "\ty0\t" << ":" << "\t" << Model::y0 << "\n"
         << "Numerical Parameters:\n"
         << "\tNx\t" << ":" << "\t" << Model::Nx << "\n"
         << "\tNy\t" << ":" << "\t" << Model::Ny << "\n"
         << "\tNt\t" << ":" << "\t" << Model::Nt << "\n"
         << "\tT\t"  << ":" << "\t" << Model::T << "\n"
         << "\tdx\t" << ":" << "\t" << Model::dx << "\n"
         << "\tdy\t" << ":" << "\t" << Model::dy << "\n"
         << "\tdt\t" << ":" << "\t" << Model::dt << "\n"
         << endl;
}
