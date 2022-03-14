# Pando Formulations

This repository contains the formulations used to generate
the data for our paper,
"[Near-Optimal Latency Versus Cost Tradeoffs in Geo-Distributed Storage]," published in NSDI'20.

Unfortunately, most of the analysis and some of the
implementation code is in a difficult to reuse state.
As a result, we do not have plans to release that code at this time.
Please contact us if you need guidance with reproducing our results.

This code is derived from the [SPANStore formulations].

## Quick Start Guide

```
$ . environ # setup environment variables
$ f-avail-ecc-pando \
      --access-sets data/example-access-set \
      --max-failures 1 \
      --max-storage-overhead 3 \
      --lp-path formulation.lp # generate MIP problem in LP format
$ solver/bin/ilpsolver formulation.lp out.sol # solve the MIP
```

To build ilpsolver, you will need to have the CPLEX SDK installed.
You do not need to use CPLEX specifically —
other solvers can also read formulations in LP format.
However, we have only tested the results using CPLEX.
The open source solvers we have tested are not fast enough
to solve the generated MIPs.

## Other notes

* The --access-sets flag (plural even though it should be singular)
  specifies the access set.
* Values for --max-failures other than 1 may be broken.
  The formulations do assume this and make some simplifying assumptions.
* --max-storage-overhead is the correct storage flag.
  Do not use --max-storage.
* If the paper's description of the lower bound isn't precise enough,
  see the first few pages of this [tech report] for a more precise
  description of the constraints with associated justification.
  Of course the MIP contains the full gory details.

[Near-Optimal Latency Versus Cost Tradeoffs in Geo-Distributed Storage]: https://www.usenix.org/conference/nsdi20/presentation/uluyol
[SPANStore formulations]: https://github.com/halfprice/spanstore_formulation
[tech report]: https://sosp19submission316.github.io/pando-tr.pdf
