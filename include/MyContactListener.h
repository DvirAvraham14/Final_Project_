#pragma once
#include "GameObject.h"

class MyContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact) {
        //check if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<GameObject*>(bodyUserData)->startContact();

        //check if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<GameObject*>(bodyUserData)->startContact();

    }

    void EndContact(b2Contact* contact) {

        //check if fixture A was a ball
        void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<GameObject*>(bodyUserData)->endContact();

        ////check if fixture B was a ball
        bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
        if (bodyUserData)
            static_cast<GameObject*>(bodyUserData)->endContact();

    }
};