#include "doctest.h"
#include "sources/Team.hpp"
#include "sources/Team2.hpp"
#include "sources/SmartTeam.hpp"
#include <iostream>

#define OLD_NINJA_SPEED 8
#define TRAINED_NINJA_SPEED 12
#define YOUNG_NINJA_SPEED 14

using namespace ariel;

TEST_SUITE("initializing charachters"){
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

    TEST_CASE("slashing and shooting decreasing hp by correct number"){

    }
}

TEST_SUITE("Checking exceptions throwing"){
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

    //TEST_CASE("trying to hit character with a negative number"){

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