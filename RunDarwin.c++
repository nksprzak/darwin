// -----------------------------
// projects/darwin/RunDarwin.c++
// Copyright (C) 2015
// Glenn P. Downing
// -----------------------------

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range

#include "Darwin.h"
// ----
// main
// ----

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
    Species food = Species('f');
    food.addInstruction("left");
    food.addInstruction("go 0");

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */

    Species hopper = Species('h');
    hopper.addInstruction("hop");
    hopper.addInstruction("go 0");


    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */


    Species rover = Species('r');
    rover.addInstruction("if_enemy 9");
    rover.addInstruction("if_empty 7");
    rover.addInstruction("if_random 5");
    rover.addInstruction("left");
    rover.addInstruction("go 0");
    rover.addInstruction("right");
    rover.addInstruction("go 0");
    rover.addInstruction("hop");
    rover.addInstruction("go 0");
    rover.addInstruction("infect");
    rover.addInstruction("go 0");


    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
    Species trap = Species('t');
    trap.addInstruction("if_enemy 3");
    trap.addInstruction("left");
    trap.addInstruction("go 0");
    trap.addInstruction("infect");
    trap.addInstruction("go 0");

    // ----
    // best
    // ----

    /*
     0. if_enemy 10
     1. if_empty 4
     3. left
     4. go 0
     5. if_random 
     6. if_random
     7. if_random
     8. if_random
     9. left
     10. go 0
     11. hop
     12. go 0
     13.infect
     14. go 0
     */
    Species best = Species('b');
    best.addInstruction("if_enemy 12");
    best.addInstruction("if_empty 4");
    best.addInstruction("left");
    best.addInstruction("go 0");
    best.addInstruction("if_random 10");
    best.addInstruction("if_random 10");
    best.addInstruction("if_random 10");
    best.addInstruction("if_random 10");
    best.addInstruction("left");
    best.addInstruction("go 0");
    best.addInstruction("hop");
    best.addInstruction("go 0");
    best.addInstruction("infect");
    best.addInstruction("go 0");

    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    Darwin z = Darwin(8,8);


    Creature f1 = Creature(&food,2);
    Creature h1 = Creature(&hopper,1);
    Creature h2 = Creature(&hopper,2);
    Creature h3 = Creature(&hopper,3);
    Creature h4 = Creature(&hopper,0);
    Creature f2 = Creature(&food,1);

    z.addCreature(&f1,0,0);
    z.addCreature(&h1,3,3);
    z.addCreature(&h2,4,3);
    z.addCreature(&h3,4,4);
    z.addCreature(&h4,3,4);
    z.addCreature(&f2,7,7);
    z.run(5);
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves. 
    Print every grid.
    */

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    srand(0);
    Darwin z2 = Darwin(9,7);
    Creature t1 = Creature(&trap,3);
    Creature t2 = Creature(&trap,0);
    Creature r1 = Creature(&rover,1);
    Creature h5 = Creature(&hopper,2);

    z2.addCreature(&t1,0,0);
    z2.addCreature(&h5,2,3);
    z2.addCreature(&r1,4,5);
    z2.addCreature(&t2,8,6);

    z2.run(10);
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */

    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    srand(0);
    Darwin z3 = Darwin(72,72);

    Creature foods[10];
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        foods[i]= Creature(&food,direct);
        z3.addCreature(&foods[i],pos%72,pos/72);
    }
  //  z3.addCreature(&trap,rand())
    Creature hops[10];
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        hops[i] = Creature(&hopper,direct);
        z3.addCreature(&hops[i],pos%72,pos/72);
    }
     Creature rovers[10];
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        rovers[i] = Creature(&rover,direct);
        z3.addCreature(&rovers[i],pos%72,pos/72);
    }
     Creature traps[10];
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        traps[i] = Creature(&trap,direct);
        z3.addCreature(&traps[i],pos%72,pos/72);
    }
    
    z3.run(1000);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    srand(0);
    Darwin z4 = Darwin(72,72);

    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        
        foods[i]= Creature(&food,direct);
        z4.addCreature(&foods[i],pos%72,pos/72);
    }
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        hops[i] = Creature(&hopper,direct);
        z4.addCreature(&hops[i],pos%72,pos/72);
    }
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        rovers[i] = Creature(&rover,direct);
        z4.addCreature(&rovers[i],pos%72,pos/72);
    }
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        traps[i] = Creature(&trap,direct);
        z4.addCreature(&traps[i],pos%72,pos/72);
    }
    Creature bests[10];
    for(int i = 0; i < 10; i++)
    {
        int pos = rand() % 5184;
        int direct = rand() % 4;
        bests[i] = Creature(&best,direct);
        z4.addCreature(&bests[i],pos%72,pos/72);
    }
    

    z4.run(1000);
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */

    return 0;}