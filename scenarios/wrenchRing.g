world {}

table (world){
    shape:ssBox, Q:<t(0 0. .6)>, size:[1. 2. .1 .02], color:[.3 .3 .3]
    fixed, contact, logical:{ }
}

box (table){
    shape:ssBox, Q:<t(0 0. .15)>, size:[.1 .1 .2 .02], color:[.6 .6 .6]
}

ring (box){
    Q:<t(0 0 .2)>
    joint:hingeZ
}

ring0(ring){ shape:capsule, Q:<t(0 0 -.1)>, size:[.05 .02], color:[.6 .6 .6] }
ring1(ring){ shape:ssBox, Q:<t(.05 0 0)>, size:[.05 .05 .15 .02], color:[.6 .6 .6] }
ring2(ring){ shape:ssBox, Q:<t(-.05 0 0)>, size:[.05 .05 .15 .02], color:[.6 .6 .6] }
ring3(ring){ shape:ssBox, Q:<t(0 0 -.05)>, size:[.15 .05 .05 .02], color:[.6 .6 .6] }
ring4(ring){ shape:ssBox, Q:<t(0 0 .05)>, size:[.15 .05 .05 .02], color:[.6 .6 .6] }

stick (table){
    shape:ssBox, Q:<t(0 .3 .065)>, size:[.6 .03 .03 .01], color:[.6 .6 .6]
}

gripper(world){
    shape:ssBox, size:[.2 .05 .05 .01], color:[.8, .8, .2]
    Q:<t(.0 .6 .8)>
    joint:free
}
    
gripper1 (gripper){
    shape:ssCvx, mesh:'gripper.arr', color:[.8, .8, .2], size:[.01]
    A:<d(-90 1 0 0) d(90 0 1 0)>
    limits:[.01 .1],
    q:.01
    joint:transZ
}
gripper2 (gripper){
    shape:ssCvx, mesh:'gripper.arr', color:[.8, .8, .2], size:[.01]
    A:<d(-90 1 0 0) d(-90 0 1 0)>
    joint:transZ,
    mimic:"gripper1"
}

#Include '../rai-robotModels/panda/panda.g'
#joint (table panda_link0){ joint:rigid Q:<t(-.3 0 .05)> }
