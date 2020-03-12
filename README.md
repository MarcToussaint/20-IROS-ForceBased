# ICRA 2020 submission on Describing Physics For Physical Reasoning: Force-based Sequential Manipulation Planning

## Description

This repository is a the ICRA submission
> M. Toussaint, JS. Ha, D. Driess:
> Describing Physics For Physical Reasoning: Force-based Sequential Manipulation Planning

Please also see the [supplementary video](https://www.youtube.com/watch?v=YxKuVit_23E) to get an impression on the method.

The repository checks out [rai](https://github.com/MarcToussaint/rai/) (as submodule) and allows you to reproduce the experiments.

## Bugs

When going through all examples, the demo code (in branch
19-ICRA-submission) sometimes raises a "timeout to end Thread::main of
'GlfwSpinnerSpi'" issue. Perhaps pick only individual examples in
main.cpp. Also note, that the computed trajectories depend on the
random seed.

## Quick Start

On Ubuntu 18.04:
```
git clone https://github.com/MarcToussaint/20-IROS-ForceBased.git
cd 20-IROS-ForceBased
git submodule init
git submodule update

make -j1 installUbuntuAll    # calls sudo apt-get install; you can always interrupt
make                         # builds libs
cd demo; make; ./x.exe       # run the demo
```

If you need to run in a docker, please have a look at the [docker setup](https://github.com/MarcToussaint/rai-maintenance/tree/master/docker) I use to test rai. A slight modification of the Dockerfile and run scripts should allow you to setup the appropriate environment also for this repo, including X.
