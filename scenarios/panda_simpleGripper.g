Include: '../rai-robotModels/panda/panda_clean.g'

## simplerCollisionModels.g

Delete panda_link0_0
Delete panda_link1_0
Delete panda_link2_0
Delete panda_link3_0
Delete panda_link4_0
Delete panda_link5_0
Delete panda_link6_0
Delete panda_link7_0
       
frame (panda_link0)	{ shape:capsule color:[.9 .9 .9 .1] size:[.1 .1] Q:<t(-.04 .0 .03) d(90 0 1 0)>, noVisual, contact:-2  }

frame (panda_joint1)	{ shape:capsule color:[.9 .9 .9 .1] size:[.2 .08] Q:<d(90 0 1 0) t(0 0 -.15)>, noVisual, contact:-2  }
frame (panda_joint3)	{ shape:capsule color:[.9 .9 .9 .1] size:[.2 .08] Q:<d(90 0 1 0) t(0 0 -.15)>, noVisual, contact:-2  }
frame (panda_joint5)	{ shape:capsule color:[.9 .9 .9 .1] size:[.22 .08] Q:<d(90 0 1 0) t(0 .02 -.2)>, noVisual, contact:-2  }

frame (panda_joint2)	{ shape:capsule color:[.9 .9 .9 .1] size:[.12 .08] Q:<d(90 0 1 0) t(0 0 .0)>, noVisual, contact:-2  }
frame (panda_joint4)	{ shape:capsule color:[.9 .9 .9 .1] size:[.12 .08] Q:<d(90 0 1 0) t(0 0 .0)>, noVisual, contact:-2  }
frame (panda_joint6)	{ shape:capsule color:[.9 .9 .9 .1] size:[.1 .07] Q:<d(90 0 1 0) t(0 .0 -.04)>, noVisual, contact:-2  }
frame panda_coll7(panda_joint7)	{ shape:capsule color:[.9 .9 .9 .1] size:[.1 .07] Q:<d(90 0 1 0) t(0 .0 .01)>, noVisual, contact:-2  }

## zero position

Edit panda_joint1 { q= 0.0 }
Edit panda_joint2 { q= -1. }
Edit panda_joint3 { q= 0. }
Edit panda_joint4 { q= -2.}
Edit panda_joint5 { q= -0. }
Edit panda_joint6 { q= 2. }
Edit panda_joint7 { q= 0.0 }
Edit panda_finger_joint1 { q=.05 }

## delete original gripper

Delete panda_hand_joint
Delete panda_hand_1
Delete panda_hand_0
Delete panda_hand>panda_finger_joint1
Delete panda_hand>panda_finger_joint2
Delete panda_finger_joint1
Delete panda_finger_joint2
Delete panda_leftfinger_1
Delete panda_leftfinger_0
Delete panda_rightfinger_1
Delete panda_rightfinger_0

Include: 'gripper.g'
joint (panda_joint7 gripper){
  Q:<d(-90 0 1 0) d(135 0 0 1) t(0 0 -.155)>
}
        
