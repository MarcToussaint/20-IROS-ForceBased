world {}

table (world){
    shape:ssBox, Q:<t(0 0. .6)>, size:[1. 2. .1 .02], color:[.3 .3 .3]
}

box (table){
    shape:ssBox, Q:<t(0 -.2 .1)>, size:[.2 .3 .1 .02], color:[.8 .8 .8]
    joint:rigid
}

target (table){
    shape:ssBox, Q:<t(.2 0. .1) d(120 0 0 1)>, size:[.2 .3 .1 .02], color:[.3 .6 .3 .6]
}

#stick (table){
#    shape:ssBox, Q:<t(-.3 .3 .365)>, size:[.03 .6 .03 .01], color:[.6 .6 .6]
#    joint:rigid
#}
stick (table){
    shape:capsule, Q:<t(-.3 .2 .1) d(90 1 0 0)>, size:[.6 .02], color:[.6 .6 .6]
    joint:rigid
}

#Include 'gripper.g'
Include 'panda_simpleGripper.g'
Edit panda_link0{ X:<t(0 .5 .65) d(-90 0 0 1)> }
