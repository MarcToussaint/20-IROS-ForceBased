world {}

table (world){
    shape:ssBox, Q:<t(0 0. .6)>, size:[1. 2. .1 .02], color:[.3 .3 .3]
}

stick (table){
    shape:capsule, Q:<t(-.3 .2 .1) d(90 1 0 0)>, size:[.6 .02], color:[.6 .6 .6]
    joint:rigid
}

target (table){
    shape:capsule, Q:<t(-.3 .2 .3) d(90 1 0 0)>, size:[.6 .02], color:[.3 .6 .3 .6]
}

Include 'panda_simpleGripper.g'
Edit panda_link0{ X:<t(0 .5 .65) d(-90 0 0 1)> }
