
# xv6 Kernel Scheduler Modifications
> kernel pult > cabbage pult
## Overview

This repository contains experimental modifications to the xv6 teaching operating system that implement and evaluate kernel scheduler enhancements. 

Key highlights

* Implemented custom scheduling algorithms and instrumentation in xv6.
* Patchset stored in `xv6/xv6_modifications.patch` (see `report.md` for details).
* Includes a short report (`xv6/report.md`) summarizing changes and results.

What this README contains

* Project overview and goals
* Design summary
* How to build, run, and test
* Patch application guide

## Design & scope

Focuses on modifying xv6’s round-robin scheduler to support fairness and metric collection. Typical changes include:

* Priority-based scheduling or aging mechanisms
* Runtime statistics and CPU usage tracking
* Comparative analysis against the default scheduler

Files changed / important artifacts

* `xv6/xv6_modifications.patch` — all source edits
* `xv6/report.md` — summary of design, experiments, and metrics

## Build and run (quick)

Requirements: GNU Make and QEMU configured locally.

```bash
cd xv6
make clean && make
make qemu
```

(If `make qemu-nox` is available, use that target.)

## Applying the patch manually

```bash
patch -p1 < xv6_modifications.patch
```

## high time we schedule a nap U///U
