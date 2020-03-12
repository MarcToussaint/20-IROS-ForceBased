world{}

Include '../rai-robotModels/hubo/hubo.g'

start (world){ Q:<t(-3. 0 0)> shape:ssBox size:[.5 .5 .05 .02] color:[.3 .3 .3] }
joint (start hubo_base) { type:rigid }

goal (world){ Q:<t(3. 0 0)> shape:ssBox size:[.5 .5 .05 .02] color:[.3 .8 .3] }


step1 (world){ Q:<t(-2.5 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }
step2 (world){ Q:<t(-2. 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }
step3 (world){ Q:<t(-1.5 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }
step4 (world){ Q:<t(-.5 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }
step5 (world){ Q:<t(0 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }
step6 (world){ Q:<t(.5 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }
step7 (world){ Q:<t(1.5 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }
step8 (world){ Q:<t(2. 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }
step9 (world){ Q:<t(2.5 0 0)> shape:ssBox size:[.1 .2 .05 .02] color:[.3 .3 .3] }

