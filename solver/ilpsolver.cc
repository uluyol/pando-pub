#include <cstring>
#include <iostream>

#include <ilcplex/ilocplex.h>

int main(int argc, char **argv) {
  if (argc < 3) {
    std::cerr << "usage: ilpsolver [options] input.lp output.sol\n\n";
    std::cerr << "\t-par         parallelize computation (non-deterministic)\n";
    std::cerr << "\t-probe n     probing level [0 (auto), 1, 2, 3] (default 3)\n";
    std::cerr << "\t-cuts-agg n  cut agg level [0 (auto), 1, 2, 3] (default 0)\n";
    return 1;
  }

  char *model_path = argv[argc - 2];
  char *solution_path = argv[argc - 1];
  bool run_parallel = false;
  int probe_level = 3;
  int cuts_agg = 0;

  for (int i = 1; i < argc - 2; i++) {
    if (strcmp(argv[i], "-par") == 0) {
      run_parallel = true;
    } else if (strcmp(argv[i], "-probe") == 0) {
      i++;
      if (i >= argc - 2) {
        std::cerr << "need to pass probe level for -probe\n";
        return 2;
      }
      probe_level = std::stoi(argv[i]);
    } else if (strcmp(argv[i], "-cuts-agg") == 0) {
      i++;
      if (i >= argc - 2) {
        std::cerr << "need to pass aggresiveness level for -cuts-agg\n";
        return 2;
      }
    } else {
      std::cerr << "unknown argument: " << argv[i] << std::endl;
      return 2;
    }
  }

  IloEnv env;
  try {
    IloModel model(env);
    IloCplex cplex(env);

    if (!run_parallel) {
      cplex.setParam(IloCplex::Param::Threads, 1);
      cplex.setParam(IloCplex::ParallelMode, IloCplex::Deterministic);
    }
    cplex.setParam(IloCplex::Probe, probe_level);
    if (cuts_agg != 0) {
      cplex.setParam(IloCplex::Cliques, cuts_agg);
      cplex.setParam(IloCplex::Covers, cuts_agg);
      cplex.setParam(IloCplex::DisjCuts, cuts_agg);
      cplex.setParam(IloCplex::FlowCovers, cuts_agg);
      cplex.setParam(IloCplex::FlowPaths, cuts_agg);
      cplex.setParam(IloCplex::FracCuts, cuts_agg);
      cplex.setParam(IloCplex::GUBCovers, cuts_agg);
      cplex.setParam(IloCplex::ImplBd, cuts_agg);
      cplex.setParam(IloCplex::MIRCuts, cuts_agg);
      cplex.setParam(IloCplex::MCFCuts, cuts_agg);
      cplex.setParam(IloCplex::ZeroHalfCuts, cuts_agg);
    }
    //cplex.setParam(IloCplex::Param::TimeLimit, 600);

    cplex.importModel(model, model_path);
    cplex.extract(model);

    cplex.solve();
    env.out() << "Solution status = " << cplex.getStatus() << std::endl;
    env.out() << "Solution value  = " << cplex.getObjValue() << std::endl;

    cplex.writeSolution(solution_path);
  } catch (IloException &e) {
    std::cerr << "ilpsolver: cplex exception occurred: " << e << std::endl;
    return 1;
  }
  env.end();
}
