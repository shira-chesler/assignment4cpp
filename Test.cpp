#include "doctest.h"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"
#include <iostream>

#define OLD_NINJA_SPEED 8
#define TRAINED_NINJA_SPEED 12
#define YOUNG_NINJA_SPEED 14

using namespace ariel;

TEST_SUITE("initializing charachters and Team( add(),stillAlive() )"){
    TEST_CASE("intializing Cowboy correct"){
        Point woody_loc(25.3,87.6);
        Cowboy woody("Woody",woody_loc);
        Cowboy dummy("dummy", Point(0,0));
        for(int i=0; i<6; i++){ //initializes with no less than 6 bullets
            CHECK(woody.hasboolets());
            woody.shoot(&dummy);
        }
        CHECK_FALSE(woody.hasboolets()); //initializes with only 6 bullets
        CHECK("Woody"==woody.getName()); //initializes name correctly
        CHECK(woody_loc==woody.getLocation()); //initializes location correctly
    }

    TEST_CASE("initializing old ninja correctly"){
        OldNinja Jiraiya("Jiraiya", Point(3,5));
        
        Cowboy dummy("dummy", Point(1000,1000));
        
        //checking initialization of old ninja's speed
        Point jirayia_initial = Jiraiya.getLocation();
        Jiraiya.move(&dummy);
        Point jirayia_moved = Jiraiya.getLocation();
        CHECK(jirayia_initial.distance(jirayia_moved)==OLD_NINJA_SPEED);

        //checking initialization of old ninja's hp
        int num_was_shot;
        while(Jiraiya.isAlive()){
            if(dummy.hasboolets()){
                dummy.shoot(&Jiraiya);
                num_was_shot++;
            }
            else{
                dummy.reload();
            }
        }
        CHECK(num_was_shot*10 == 150);

    }

    TEST_CASE("initializing trained ninja correctly"){
        TrainedNinja Kakashi("Kakashi", Point(0,7));
        
        Cowboy dummy("dummy", Point(1000,1000));

        //checking initialization of trained ninja's speed
        Point kakashi_initial = Kakashi.getLocation();
        Kakashi.move(&dummy);
        Point kakashi_moved = Kakashi.getLocation();
        CHECK(kakashi_initial.distance(kakashi_moved)==TRAINED_NINJA_SPEED);

        //checking initialization of trained ninja's hp
        int num_was_shot;
        while(Kakashi.isAlive()){
            if(dummy.hasboolets()){
                dummy.shoot(&Kakashi);
                num_was_shot++;
            }
            else{
                dummy.reload();
            }
        }
        CHECK(num_was_shot*10 == 120);
    }

    TEST_CASE("initializing young ninja correctly"){
        YoungNinja Naruto("Naruto", Point(5, 5));
        
        Cowboy dummy("dummy", Point(1000,1000));

        //checking initialization of young ninja's speed
        Point naruto_initial = Naruto.getLocation();
        Naruto.move(&dummy);
        Point naruto_moved = Naruto.getLocation();
        CHECK(naruto_initial.distance(naruto_moved)==YOUNG_NINJA_SPEED);

        //checking initialization of young ninja's hp
        int num_was_shot;
        while(Naruto.isAlive()){
            if(dummy.hasboolets()){
                dummy.shoot(&Naruto);
                num_was_shot++;
            }
            else{
                dummy.reload();
            }
        }
        CHECK(num_was_shot*10 == 100);
    }

    TEST_CASE("Team initialization") {
        Cowboy* cowboy = new Cowboy("cob", Point(1000,1000));
        YoungNinja* ninja = new YoungNinja("nin", Point(54, 42));
        OldNinja* old = new OldNinja("oldi", Point(67, 83));
        Team team{cowboy};
        CHECK_EQ(team.stillAlive(), 1);

        Team2 team2{ninja};
        CHECK_EQ(team2.stillAlive(), 1);

        SmartTeam team3{old};
        CHECK_EQ(team3.stillAlive(), 1);
    }

    TEST_CASE("Team class add() and stillAlive() methods") {
        Cowboy* captain1 = new Cowboy("cob", Point(1000,1000));
        YoungNinja* captain2 = new YoungNinja("nin", Point(54, 42));
        OldNinja* captain3 = new OldNinja("oldi", Point(67, 83));

        Team team1{captain1};
        Team2 team2{captain2};
        SmartTeam team3{captain3};

        // Every addition should rise the value returned by stillAlive()
        for (int i = 0; i < 9; i++) {
            TrainedNinja* cur1 = new TrainedNinja("another one", Point(8,8));
            Cowboy* cur2 = new Cowboy("another cby", Point(9,9));
            YoungNinja* cur3 = new YoungNinja("another yn", Point(33,33));
            team1.add(cur1);
            team2.add(cur2);
            team3.add(cur3);

            CHECK_EQ(team1.stillAlive(), i + 2);
            CHECK_EQ(team2.stillAlive(), i + 2);
            CHECK_EQ(team3.stillAlive(), i + 2);
        }

        Cowboy* tmp = new Cowboy("getting inserted", Point(45, 67));
        CHECK_THROWS(team1.add(tmp));
        CHECK_THROWS(team2.add(tmp));
        CHECK_THROWS(team3.add(tmp));
        delete tmp;
    }
}

TEST_SUITE("Checking exceptions throwing"){
    TEST_CASE("Sending nullptr to the attack() method") {
        Cowboy* cowboy = new Cowboy("cob", Point(1000,1000));
        TrainedNinja* ninja = new TrainedNinja("nin", Point(38,47));
        Team team{cowboy};
        Team2 team2{ninja};

        CHECK_THROWS_AS(team.attack(nullptr), std::invalid_argument);
        CHECK_THROWS_AS(team2.attack(nullptr), std::invalid_argument);
    }

    TEST_CASE("Sending negative value to hit()") {
        Cowboy* cowboy = new Cowboy("cob", Point(1000,1000));
        YoungNinja* yninja = new YoungNinja("ynin", Point(38,47));
        TrainedNinja* tninja = new TrainedNinja("tnin", Point(38,47));
        OldNinja* oninja = new OldNinja("onin", Point(38,47));

        CHECK_THROWS_AS(cowboy->hit(-37), std::invalid_argument);
        CHECK_THROWS_AS(yninja->hit(-42), std::invalid_argument);
        CHECK_THROWS_AS(oninja->hit(-58), std::invalid_argument);
        CHECK_THROWS_AS(tninja->hit(-3000), std::invalid_argument);

        delete cowboy;
        delete yninja;
        delete oninja;
        delete tninja;
    }

    TEST_CASE("reload and shooting by a dead cowboy"){
        Point woody_loc(0,0);
        Cowboy woody("Woody",woody_loc);
        Cowboy enemy("enemy", Point(0,0.5));
        for (int i = 0; i < 11; i++)
        {
            enemy.shoot(&woody);
        }
        CHECK_THROWS(woody.reload());
        CHECK_THROWS(woody.shoot(&enemy));
        
    }

    TEST_CASE("moving and slashing by a dead ninja"){
        //OldNinja
        Cowboy enemy("enemy", Point(0,0.5));
        OldNinja Jiraiya("Jiraiya", Point(3,5));
        
        for (int i = 0; i < 15; i++)
        {
            enemy.shoot(&Jiraiya);
            if(i%6 == 5){
                enemy.reload();
            }
        }
        CHECK_THROWS(Jiraiya.move(&enemy));
        CHECK_THROWS(Jiraiya.slash(&enemy));
        
        //TrainedNinja
        TrainedNinja Kakashi("Kakashi", Point(3,5));
        
        for (int i = 0; i < 12; i++)
        {
            enemy.shoot(&Kakashi);
            if(i%6 == 5){
                enemy.reload();
            }
        }
        CHECK_THROWS(Kakashi.move(&enemy));
        CHECK_THROWS(Kakashi.slash(&enemy));

        //YoungNinja
        YoungNinja Naruto("Naruto", Point(3,5));
        
        for (int i = 0; i < 10; i++)
        {
            enemy.shoot(&Naruto);
            if(i%6 == 5){
                enemy.reload();
            }
        }
        CHECK_THROWS(Naruto.move(&enemy));
        CHECK_THROWS(Naruto.slash(&enemy));
    }

    TEST_CASE("self harm"){
        Cowboy Woody("Woody", Point(0,0.5));
        OldNinja Jiraiya("Jiraiya", Point(3,5));
        TrainedNinja Kakashi("Kakashi", Point(4,5));
        YoungNinja Naruto("Naruto", Point(5,5));

        CHECK_THROWS(Woody.shoot(&Woody));
        CHECK_THROWS(Jiraiya.slash(&Jiraiya));
        CHECK_THROWS(Kakashi.slash(&Kakashi));
        CHECK_THROWS(Naruto.slash(&Naruto));
    }

    TEST_CASE("add an existing member to team"){
        Cowboy* Woody = new Cowboy("Woody", Point(0,0.5));
        Team bestt(Woody);
        CHECK_THROWS(bestt.add(Woody));
    }

    TEST_CASE("move towards got a negtive distance"){
        Point from(5,8);
        Point to(3,-4);
        CHECK_THROWS(Point::moveTowards(from, to, -9));
    }

    TEST_SUITE("slashing/ shooting a dead character"){
        TEST_CASE("cowboy shooting dead cowboy"){
            Cowboy deadc("dead cowboy",Point(0,0));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 11; i++)
            {
                Woody.shoot(&deadc);
            }
            CHECK_THROWS(Woody.shoot(&deadc));
        }

        TEST_CASE("cowboy shooting dead young ninja"){
            YoungNinja deadyn("dead young ninja", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 10; i++)
            {
                Woody.shoot(&deadyn);
            }
            CHECK_THROWS(Woody.shoot(&deadyn));
        }

        TEST_CASE("cowboy shooting dead trained ninja"){
            TrainedNinja deadtn("dead trained ninja", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 12; i++)
            {
                Woody.shoot(&deadtn);
            }
            CHECK_THROWS(Woody.shoot(&deadtn));
        }

        TEST_CASE("cowboy shooting dead old ninja"){
            OldNinja deadon("dead old ninja", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 15; i++)
            {
                Woody.shoot(&deadon);
            }
            CHECK_THROWS(Woody.shoot(&deadon));
        }

        TEST_CASE("young ninja slashing dead cowboy"){
            Cowboy deadc("dead cowboy",Point(0,0));
            YoungNinja Naruto("Naruto", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 11; i++)
            {
                Woody.shoot(&deadc);
            }
            CHECK_THROWS(Naruto.slash(&deadc));
        }

        TEST_CASE("young ninja slashing dead young ninja"){
            YoungNinja deadyn("dead young ninja", Point(5,5));
            YoungNinja Naruto("Naruto", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 10; i++)
            {
                Woody.shoot(&deadyn);
            }
            CHECK_THROWS(Naruto.slash(&deadyn));
        }

        TEST_CASE("young ninja slashing dead trained ninja"){
            TrainedNinja deadtn("dead trained ninja", Point(5,5));
            YoungNinja Naruto("Naruto", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 12; i++)
            {
                Woody.shoot(&deadtn);
            }
            CHECK_THROWS(Naruto.slash(&deadtn));
        }

        TEST_CASE("young ninja slashing dead old ninja"){
            OldNinja deadon("dead old ninja", Point(5,5));
            YoungNinja Naruto("Naruto", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 15; i++)
            {
                Woody.shoot(&deadon);
            }
            CHECK_THROWS(Naruto.slash(&deadon));
        }

        TEST_CASE("trained ninja slashing dead cowboy"){
            Cowboy deadc("dead cowboy",Point(0,0));
            TrainedNinja Kakashi("Kakashi", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 11; i++)
            {
                Woody.shoot(&deadc);
            }
            CHECK_THROWS(Kakashi.slash(&deadc));
        }

        TEST_CASE("trained ninja slashing dead young ninja"){
            YoungNinja deadyn("dead young ninja", Point(5,5));
            TrainedNinja Kakashi("Kakashi", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 10; i++)
            {
                Woody.shoot(&deadyn);
            }
            CHECK_THROWS(Kakashi.slash(&deadyn));
        }

        TEST_CASE("trained ninja slashing dead trained ninja"){
            TrainedNinja deadtn("dead trained ninja", Point(5,5));
            TrainedNinja Kakashi("Kakashi", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 12; i++)
            {
                Woody.shoot(&deadtn);
            }
            CHECK_THROWS(Kakashi.slash(&deadtn));
        }

        TEST_CASE("trained ninja slashing dead old ninja"){
            OldNinja deadon("dead old ninja", Point(5,5));
            TrainedNinja Kakashi("Kakashi", Point(5,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 15; i++)
            {
                Woody.shoot(&deadon);
            }
            CHECK_THROWS(Kakashi.slash(&deadon));
        }

        TEST_CASE("old ninja slashing dead cowboy"){
            Cowboy deadc("dead cowboy",Point(0,0));
            OldNinja Jiraiya("Jiraiya", Point(3,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 11; i++)
            {
                Woody.shoot(&deadc);
            }
            CHECK_THROWS(Jiraiya.slash(&deadc));
        }

        TEST_CASE("old ninja slashing dead young ninja"){
            YoungNinja deadyn("dead young ninja", Point(5,5));
            OldNinja Jiraiya("Jiraiya", Point(3,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 10; i++)
            {
                Woody.shoot(&deadyn);
            }
            CHECK_THROWS(Jiraiya.slash(&deadyn));
        }

        TEST_CASE("old ninja slashing dead trained ninja"){
            TrainedNinja deadtn("dead trained ninja", Point(5,5));
            OldNinja Jiraiya("Jiraiya", Point(3,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 12; i++)
            {
                Woody.shoot(&deadtn);
            }
            CHECK_THROWS(Jiraiya.slash(&deadtn));
        }

        TEST_CASE("old ninja slashing dead old ninja"){
            OldNinja deadon("dead old ninja", Point(5,5));
            OldNinja Jiraiya("Jiraiya", Point(3,5));
            Cowboy Woody("Woody",Point(0,0.5));
            
            //kiling the one that supposed to be dead
            for (int i = 0; i < 15; i++)
            {
                Woody.shoot(&deadon);
            }
            CHECK_THROWS(Jiraiya.slash(&deadon));
        }
    }
}

TEST_SUITE("operations on teams correctly"){
    TEST_CASE("Team operations"){
        Cowboy* Woody = new Cowboy("Woody", Point(0, 0.8));
        Team tem(Woody);
        CHECK_EQ(tem.stillAlive(), 1);
        Character* ldr = tem.getLeader();
        tem.add(new YoungNinja("Naruto", Point(9, 8)));
        tem.add(new OldNinja("sushi", Point(97,5)));
        CHECK_EQ(tem.stillAlive(), 3);
        Cowboy enemy("enemy", Point(7,8));
        for (int i = 0; i < 11; i++)
        {
            enemy.shoot(Woody);
        }
        CHECK_EQ(tem.stillAlive(),2);
        CHECK(ldr != tem.getLeader());
        
    }

    TEST_CASE("Team2 operations"){
        Cowboy* Woody = new Cowboy("Woody", Point(0, 0.8));
        Team2 tem(Woody);
        CHECK_EQ(tem.stillAlive(), 1);
        Character* ldr = tem.getLeader();
        tem.add(new YoungNinja("Naruto", Point(9, 8)));
        tem.add(new OldNinja("sushi", Point(97,5)));
        CHECK_EQ(tem.stillAlive(), 3);
        Cowboy enemy("enemy", Point(7,8));
        for (int i = 0; i < 11; i++)
        {
            enemy.shoot(Woody);
        }
        CHECK_EQ(tem.stillAlive(),2);
        CHECK(ldr != tem.getLeader());
    }

    TEST_CASE("SmartTeam operations"){
        Cowboy* Woody = new Cowboy("Woody", Point(0, 0.8));
        SmartTeam tem(Woody);
        CHECK_EQ(tem.stillAlive(), 1);
        Character* ldr = tem.getLeader();
        tem.add(new YoungNinja("Naruto", Point(9, 8)));
        tem.add(new OldNinja("sushi", Point(97,5)));
        CHECK_EQ(tem.stillAlive(), 3);
        Cowboy enemy("enemy", Point(7,8));
        for (int i = 0; i < 11; i++)
        {
            enemy.shoot(Woody);
        }
        CHECK_EQ(tem.stillAlive(),2);
        CHECK(ldr != tem.getLeader());
    }
}

TEST_SUITE("operations in battles"){
    TEST_CASE("Cowboy shoot() and reload() methods") {
        Cowboy* cowboy = new Cowboy("cob", Point(1000,1000));
        OldNinja* target = new OldNinja("trgt", Point(8,7));

        auto shoot = [&](int times) {
            for (int i = 0; i < times; i++) {
                cowboy->shoot(target);
            }
        };

        shoot(6);
        CHECK_FALSE(cowboy->hasboolets());
        CHECK_NOTHROW(cowboy->shoot(target)); // This should not damage the target
        cowboy->reload();

        shoot(2);
        cowboy->reload();
        shoot(6);
        CHECK(target->isAlive()); // Target should still be alive with 10 hit points if the cowboys damage is 10
        shoot(1);
        CHECK(target->isAlive()); // Reloading when the magazine isn't empty shouldn't result in more than 6 bullets, the previous shoot should have no effect
        cowboy->reload();
        shoot(1);
        CHECK_FALSE(target->isAlive()); // Target should be dead
        delete cowboy;
        delete target;
    }

    TEST_CASE("Ninjas can only slash when distance is less than 1") {
        OldNinja old{"Bob", Point{0, 0}};
        TrainedNinja trained{"Kung fu panda", Point{0, 0}};
        YoungNinja young{"Karate kid", Point{0.5, 0.5}};
        Cowboy cowboy{"Clint", Point{0.5, 0.5}};

        for (int i = 0; i < 1; i++) {
            old.slash(&cowboy);
            young.slash(&cowboy);
        }

        CHECK(cowboy.isAlive());

        old.slash(&cowboy);
        CHECK_FALSE(cowboy.isAlive());

        YoungNinja ninja{"Bob", Point{-0.5, 0.5}}; // Distance from young is exactly one
        OldNinja ninja2{"Bob", Point{2, 2}};

        // These attacks should have no affect
        for (int i = 0; i < 20; i++) {
            trained.slash(&ninja2);
            old.slash(&ninja2);
            young.slash(&ninja2);
        }

        for(int i = 0 ; i < 1 ; i++){
            old.slash(&ninja);
            young.slash(&ninja);
        }
        CHECK(ninja.isAlive());
        CHECK(ninja2.isAlive());
    }
}

TEST_SUITE("point tests"){
    TEST_CASE("Point distance") {
    ariel::Point p1(0, 0);
    ariel::Point p2(3, 4);
    double expected_distance = 5;
    double actual_distance = p1.distance(p2);
    CHECK(expected_distance == actual_distance);
}

TEST_CASE("Point moveTowards") {
    Point p1(0, 0);
    Point p2(3, 4);
    double distance = 2;
    Point expected_point(1.2, 1.6);
    Point actual_point = Point::moveTowards(p1, p2, distance);
    CHECK(expected_point == actual_point);
}

TEST_CASE("Point operator==") {
    ariel::Point p1(1, 2);
    ariel::Point p2(1, 2);
    CHECK(p1 == p2);
    ariel::Point p3(3, 4);
    CHECK(!(p1 == p3));
}
}