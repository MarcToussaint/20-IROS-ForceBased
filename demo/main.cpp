#include <Kin/kin.h>
#include <KOMO/komo.h>
#include <Kin/F_dynamics.h>
#include <Kin/TM_angVel.h>

#include <Gui/opengl.h>

//===========================================================================

void solve(KOMO& komo, const Skeleton& S){
//  komo.animateOptimization = 1;
  komo.verbose=4;
//  komo.reportProblem();

//  ofstream fil("z.log");  komo.logFile = &fil;

  komo.optimize();
//  komo.checkGradients();

  //-- KKT data
  FILE("z.graph") <<komo.getProblemGraph(true);

  //-- more output
//  FILE("z.contacts") <<komo.getContacts() <<endl;
//  FILE("z.energy") <<catCol( komo.getPath_tau(), komo.getPath_energies() ) <<endl;

  //-- nicer display:
  komo.displayCamera();
  komo.gl->resize(700,500);
  rai::String txt;
  double lastPhase=0.;
  for(const SkeletonEntry& s:S){
    if(s.phase0>0.){
      if(s.phase0>lastPhase) txt <<'\n';
      txt <<'(' <<s.symbol;
      for(const rai::String& f:s.frames) txt <<' ' <<f;
      txt <<')';
      lastPhase = s.phase0;
    }
  }

//  while(komo.displayTrajectory(2.5, true, true, 0, txt));
  komo.displayTrajectory(1., false, true, "z.vid/", txt);
}

//===========================================================================

void passive_ballBounce(){
  rai::KinematicWorld K;
  K.addFrame("base");
  K.addObject("floor", NULL, rai::ST_ssBox, {1., 1., .1, .02}, {}, {0., .0,.5});
  auto b = K.addObject("ball",  NULL, rai::ST_sphere, {.05}, {}, {.0, .0, 1.});
//  auto I = new rai::Inertia(*b);
//  I->mass = 1.;
//  I->defaultInertiaByShape();

  Skeleton S = {
    { .0, 5., SY_dynamic, {"ball"} },
    { 1., 1., SY_bounce, {"floor", "ball"} },
    { 2., 2., SY_bounce, {"floor", "ball"} },
    { 3., 3., SY_bounce, {"floor", "ball"} },
    { 4., 4., SY_bounce, {"floor", "ball"} },
  };

  KOMO komo;
  komo.setModel(K, false);
  komo.setPathOpt(4.5, 10., .2);
  komo.setTimeOptimization();
  komo.setSkeleton(S);

  solve(komo, S);
}

//===========================================================================

void passive_elasticBounce(){
  rai::KinematicWorld K;
  K.addFrame("base");
  K.addObject("floor", NULL, rai::ST_ssBox, {1., 1., .1, .02}, {}, {0.,-.6,.5}, {1., .1, 0., 0.});
  K.addObject("ball",  NULL, rai::ST_ssBox, {.0, .4, .1, .05}, {}, {.0, .0, 1.05});

  Skeleton S = {
    { 0., .1, SY_magicTrans, {"ball"} },
    { .1, 1., SY_dynamic, {"ball"} },
    { .5, .5, SY_bounce, {"floor", "ball"} },
  };

  KOMO komo;
  komo.setModel(K, false);
  komo.setPathOpt(1., 20, 1.);
  komo.setSkeleton(S);

  solve(komo, S);
}

//===========================================================================

void passive_complementarySlide(){
  rai::KinematicWorld K;
  K.addObject("floor", NULL, rai::ST_ssBox, {1., 1., .1, .02}, {}, {0.,.5,.5}, {1., .1, 0., 0.});
  K.addObject("box",  NULL, rai::ST_ssBox, {.4, .4, .2, .05}, {}, {.0, .0, .65}, {1., .1, 0., 0.3});

  Skeleton S = {
    { 0., 1., SY_dynamic, {"box"} },
    { 0., 1., SY_contactComplementary, {"floor", "box"} },
  };

  KOMO komo;
  komo.setModel(K, false);
  komo.setPathOpt(1., 50, 1.);
  komo.setTimeOptimization();
  komo.setSkeleton(S);

  solve(komo, S);
}

//===========================================================================

void passive_stickyTumbling(){
  rai::KinematicWorld K;
  K.addObject("floor", NULL, rai::ST_ssBox, {1., 1., .1, .02}, {}, {0.,0., .5}, {1., .3, 0., 0.});
  K.addObject("box",  NULL, rai::ST_ssBox, {.4, .2, .4, .05}, {}, {.0, .0, 1.1}, {1., 0., 0., .3});

  Skeleton S = {
    { 0., 1., SY_dynamic, {"box"} },
    { .2, 1., SY_contactStick, {"floor", "box"} },
  };

  KOMO komo;
  komo.setModel(K, false);
  komo.setPathOpt(1., 20, 1.);
  komo.setTimeOptimization();
  komo.setSkeleton(S);

  solve(komo, S);
}

//===========================================================================

enum Scenario{
  bookOnShelf,
  boxRearrangement,
  pushWithStick,
  pushWithStickFloat,
  walking,
  wrenchRing,
  liftRing,
  billards,
  forceGrasp,
  stableGrasp
};
template<> const char* rai::Enum<Scenario>::names [] = {
  "bookOnShelf",
  "boxRearrangement",
  "pushWithStick",
  "pushWithStickFloat",
  "walking",
  "wrenchRing",
  "liftRing",
  "billards",
  "forceGrasp",
  "stableGrasp"
};

void scenario(Scenario s){
  rai::KinematicWorld C;
  C.addFile(STRING("../scenarios/" <<rai::Enum<Scenario>(s) <<".g"));
  C.watch();

  Skeleton S;
  StringA collisions;
  switch(s){
    case pushWithStick:{
       S = {
//        {0., -1., SY_magic, {"gripper"} },
//        {0., -1., SY_dampMotion, {"gripper"} },

//        {1., 3., SY_inside, {"gripperCenter", "stick"} },
        {1., 3., SY_oppose, {"finger1", "finger2", "stick"} },
        {1., 3.5, SY_stable, {"gripper", "stick"} },
        {2., 3.5, SY_quasiStaticOn, {"table", "box"} },
        {2., 3., SY_contact, {"stick", "box"} },
        {3., 3.5, SY_poseEq, {"box", "target"} },
      };
      collisions = {"gripper", "box",
                    "gripper", "table",
                    "finger1", "box",
                    "finger1", "table",
                    "finger2", "box",
                    "finger2", "table",
                    "stick", "box",
                    "stick", "table"};

    } break;
    case pushWithStickFloat:{
       S = {
        {0., -1., SY_magic, {"gripper"} },
        {0., -1., SY_dampMotion, {"gripper"} },

//        {1., 3., SY_inside, {"gripperCenter", "stick"} },
        {1., 3., SY_oppose, {"finger1", "finger2", "stick"} },
        {1., 3.5, SY_stable, {"gripper", "stick"} },
        {2., 3.5, SY_quasiStaticOn, {"table", "box"} },
        {2., 3., SY_contact, {"stick", "box"} },
        {3., 3.5, SY_poseEq, {"box", "target"} },
      };
      collisions = {"gripper", "box",
                    "gripper", "table",
                    "gripper", "stick",
                    "finger1", "box",
                    "finger1", "table",
                    "finger1", "stick",
                    "finger2", "box",
                    "finger2", "table",
                    "finger2", "stick",
                    "stick", "box",
                    "stick", "table"};

    } break;
    case bookOnShelf:{
      S = {
//        {0., -1., SY_magic, {"gripper"} },
//        {0., -1., SY_dampMotion, {"gripper"} },

        {1., 2., SY_contact, {"finger1", "box"} },
        {1., 2., SY_quasiStaticOn, {"shelf", "box"} },

        {2., 2.5, SY_poseEq, {"box", "target2"} },

        {3., 4., SY_oppose, {"finger1", "finger2", "box"} },
        {3., 4., SY_stable, {"gripper", "box"} },

        {4., 4.5, SY_poseEq, {"box", "target"} },
     };
      collisions = {"finger1", "box",
                    "finger2", "box",
                    "gripper", "box",
                    "finger1", "wall",
                    "finger2", "wall",
                    "gripper", "wall",
                    "panda_coll7", "wall",
                    "box", "shelf",
                    "box", "wall"};
    } break;
    case liftRing:{
      S = {
//        {1., 4.5, SY_inside, {"gripperCenter", "stick"} },
        {1., 4.5, SY_oppose, {"finger1", "finger2", "stick"} },
        {1., 4.5, SY_stable, {"gripper", "stick"} },
        { 2., 3., SY_dynamic, {"box"} },
//        { 2., 3., SY_quasiStatic, {"box"} },
//        { 1., 2. , SY_contactStick, {"table", "box"} },
        { 2., 4.5, SY_contact, {"stick", "ring4"} },
        { 4., 4.5, SY_stableOn, {"target", "box"} },
        { 4., 4.5, SY_above, {"target", "box"} },
     };
      collisions = {"finger1", "stick",
                    "finger2", "stick",
                    "gripper", "stick",
                    "ring4", "stick",
                    "ring1", "stick",
                    "ring2", "stick",
                    "ring3", "stick",
//                    "box", "target",
                    "box", "table",
                   };
    } break;
    case billards:{
      S = {
        {2., 4., SY_oppose, {"finger1", "finger2", "ball"} },
        {2., 4., SY_stable, {"gripper", "ball"} },
        { 5., 8., SY_dynamic, {"ball"} },
        { 6., 6., SY_bounce, {"boxBo", "ball"} },
        { 7., 7., SY_bounce, {"boxLe", "ball"} },
//        { 7., 7., SY_bounce, {"boxBo", "ball"} },
        { 8., 8., SY_touch, {"target", "ball"} }
     };
      collisions = {"finger1", "ball",
                    "finger2", "ball",
                    "finger1", "boxBo",
                    "finger2", "boxBo",
                   };
    } break;
    case forceGrasp:{
      S = {
        {1., 2., SY_oppose, {"finger1", "finger2", "stick"} },
//        {2., 3., SY_touch, {"finger1", "stick"} },
//        {2., 3., SY_touch, {"finger2", "stick"} },
        {1., 2., SY_contactStick, {"finger1", "stick"} },
        {1., 2., SY_contactStick, {"finger2", "stick"} },
        {1., 2., SY_dynamic, {"stick"} },
        {2., 2., SY_poseEq, {"stick", "target"} },
     };
      collisions = {"finger1", "stick",
                    "finger2", "stick",
                   };
    } break;
    case stableGrasp:{
      S = {
        {1., 2., SY_oppose, {"finger1", "finger2", "stick"} },
        {1., 2., SY_stable, {"gripper", "stick"} },
        {2., 2., SY_poseEq, {"stick", "target"} },
     };
      collisions = {"finger1", "stick",
                    "finger2", "stick",
                   };
    } break;
    default: NIY;
  }

  double maxPhase=0;
  for(const SkeletonEntry& s:S){
    if(s.phase0>maxPhase) maxPhase=s.phase0;
    if(s.phase1>maxPhase) maxPhase=s.phase1;
  }

  KOMO komo;
  komo.setModel(C, false);
  komo.sparseOptimization=true;
  if(s==billards){
    komo.setPathOpt(maxPhase, 20, .3);
//    komo.setTimeOptimization();
    komo.setSquaredQAccVelHoming(0., -1., 1e-1, 0., 1e-2);
  }else{
    komo.setPathOpt(maxPhase, 40, 1.);
    komo.setSquaredQAccVelHoming(0., -1., 1e-1, 0., 1e-2);
  }


  komo.setSkeleton(S);


  if(s==bookOnShelf){
    komo.addObjective({3., -1.}, OT_sos, FS_scalarProductXY, {"gripper", "box"}, {1e1}, {-1.});
//    komo.addObjective({2.5, -1.}, OT_sos, FS_scalarProductXX, {"gripper", "box"}, {1e1});
//    komo.addObjective({2.5, -1.}, OT_sos, FS_scalarProductXZ, {"gripper", "box"}, {1e1});
  }
//  if(s==forceGrasp){
//    komo.addObjective({0., -1.}, OT_ineq, FS_jointLimits, {}, {1e1}, {1e1});
//  }



  for(uint i=0;i<collisions.N;i+=2){
    komo.addObjective({0,maxPhase+.5}, OT_ineq, FS_distance, {collisions(i), collisions(i+1)}, {1e1});
  }

  solve(komo, S);
}

//===========================================================================

int main(int argc,char **argv){
  rai::initCmdLine(argc, argv);

//  rnd.clockSeed();

#if 0
  passive_ballBounce();
  passive_elasticBounce();
  passive_complementarySlide();
  passive_stickyTumbling();
#endif

  scenario(stableGrasp);
  scenario(bookOnShelf);
  scenario(billards);
  scenario(liftRing);
  scenario(forceGrasp);
  scenario(pushWithStickFloat);
  scenario(pushWithStick);

  return 0;
}
