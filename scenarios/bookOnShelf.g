world {}

shelf (world){
    shape:ssBox, Q:<t(0 0. .6)>, size:[.3 1. .05 .01], color:[.3 .3 .3]
}

wall (shelf){
    shape:ssBox, Q:<t(0 -.475 .175)>, size:[.3 .05 .4 .01], color:[.3 .3 .3]
}

box (shelf){
    shape:ssBox, Q:<t(0 -.425 .125)>, size:[.15 .05 .2 .01], color:[.8 .8 .8]
    joint:rigid
}

target2 (shelf){
    shape:ssBox, Q:<t(.15 -.425 .125)>, size:[.15 .05 .2 .01], color:[.3 .8 .3 .6]
}

target (world){
    shape:ssBox, Q:<t(.3 -.2 .6) d(45 1 0 0)>, size:[.15 .05 .2 .01], color:[.3 .8 .3 .6]
}

#Include 'gripper.g'
Include 'panda_simpleGripper.g'
Edit panda_link0{ X:<t(0 .2 .625) d(-90 0 0 1)> }


