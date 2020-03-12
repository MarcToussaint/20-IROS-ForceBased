frame world{}

### box
box { X=<t(.0 0 .5)> }

boxBo (box){ shape=ssBox, Q=<t(.0 .1 0)>, size=[1.5 2.8 .3 .04], color:[.5 .5 .5], contact }
boxLe (box){ shape=ssBox, Q=<t(-.75 0 .75) d(90 0 1 0)>, size=[1.5 2. .1 .04], color:[.5 .5 .5], contact }
boxBa (box){ shape=ssBox, Q=<t(0 -1. .75) d(90 1 0 0)>, size=[1.5 1.5 .1 .04], color:[.5 .5 .5], contact }


ball  {
    size=[.04] color=[.8 .8 .8] shape=sphere contact
    X=<t(.4 .7 .7)> }

target (boxBa) {
    shape=ssBox size=[.3 .3 .04 .01] color=[.3 .6 0],
    joint=rigid
    from=<t(0 .0 -.05)>, logical={ table }
}

Include 'panda_simpleGripper.g'
Edit panda_link0{ X:<t(-.2 .9 .65) d(-90 0 0 1)> }
