# IROS 2020 submission on Describing Physics For Physical Reasoning: Force-based Sequential Manipulation Planning

## Description

This repository is a the RA-L/IROS submission
> M. Toussaint, JS. Ha, D. Driess:
> Describing Physics For Physical Reasoning: Force-based Sequential Manipulation Planning

Please see also the [arxiv paper 2002.12780](https://arxiv.org/abs/2002.12780) and the [supplementary video](https://www.youtube.com/watch?v=YxKuVit_23E).

The repository checks out [rai](https://github.com/MarcToussaint/rai/) (as submodule) and allows you to reproduce the experiments.

## Versions

The 19-ICRA-submission branch contains the literal verion used to
generate the experiments in the paper (and sometimes raises a "timeout
to end Thread::main of 'GlfwSpinnerSpi'" when going through all
examples). The master branch instead uses a newer version of the rai
submodule.

## Quick Start

On Ubuntu 18.04:
```
git clone https://github.com/MarcToussaint/20-IROS-ForceBased.git
cd 20-IROS-ForceBased
git submodule init
git submodule update

make -j1 installUbuntuAll    # calls sudo apt-get install; you can always interrupt
make -j $(command nproc)     # builds libs
cd demo; make; ./x.exe       # run the demo
```

If you need to run in a docker, please have a look at the
[docker setup](https://github.com/MarcToussaint/rai-maintenance/tree/master/docker)
I use to test rai. A slight modification of the Dockerfile and run
scripts should allow you to setup the appropriate environment also for
this repo, including X.
