//
// Created by Vishnu R Menon on 2019-03-14.
//

#ifndef COURSEWORK_MYMPI_H
#define COURSEWORK_MYMPI_H

#include "mpi.h"

class MyMPI {
    public:  
        MyMPI(int argc, char* argv[]);
        void createSubComm(MPI_Comm* myComm);
        bool isValid() { return valid; };
        int size() { return world_size; };
        int rank() { return world_rank; };
    private:
        int Np = 1;
        int Px = 1;
        int Py = 1;
        int world_size;
        int world_rank;
        bool valid = false;
};


#endif //COURSEWORK_MYMPI_H
