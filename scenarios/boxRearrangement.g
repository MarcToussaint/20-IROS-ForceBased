world {}

table (world){
    shape:ssBox, Q:<t(0 0. .6)>, size:[1. 2. .1 .02], color:[.3 .3 .3]
    fixed, contact, logical:{ }
}

gripper1 (world){
    shape:ssCvx, mesh:'gripper.arr', color:[.8, .8, .2], size:[.01]
    Q:<t(.05 0 1.)>
    joint:free
}

gripper2 (world){
    shape:ssCvx, mesh:'gripper.arr', color:[.8, .8, .2], size:[.01]
    Q:<t(-.05 0 1.)>
    joint:free
}

box (table){
    shape:ssBox, Q:<t(0 0. .1)>, size:[.2 .3 .1 .02], color:[.6 .6 .6]
    joint:rigid
}

target (table){
    shape:ssBox, Q:<t(.2 .2 .2) d(90 1 0 0)>, size:[.2 .3 .1 .02], color:[.3 .6 .3 .6]
    joint:rigid
}
