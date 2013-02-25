Artemis-Cpp
===

A C++ port of [Artemis Entity System Framework](http://gamadu.com/artemis/tutorial.html).

The port was orignially written by [Sidar Talei](https://bitbucket.org/stalei/artemiscpp/src), in which he used several C++11 features such as deleted function, variadic templates, nullptr, etc… We wanted the framework to be portable, so we removed all C++11 feature usages so that it compiles well on "older" compiler.	


### PORTED CLASSES

- Component
- ComponentMapper
- ComponentType
- ComponentTypeManager
- Entity
- EntityProcessingSystem
- EntitySystem
- SystemBitManager
- ImmutableBag
- EntityManager
- DelayedEntityProcessingSystem
- DelayedEntitySystem
- GroupManager
- IntervalEntityProcessingSystem
- IntervalEntitySystem
- Manager
- SystemManager
- TagManager
- utils
- World
- Bag

### EXAMPLE

`VelocityComponent` and `PositionComponent`.

``` cpp
class VelocityComponent : public artemis::Component {
public:
    float velocityX;
    float velocityY;

    MovementComponent(float velocityX, float velocityY)
    {
        this->velocityX = velocityX;
        this->velocityY = velocityY;
    };
};

class PositionComponent : public artemis::Component
{

public:
    float posX;
    float posY;
    PositionComponent(float posX, float posY)
    {
        this->posX = posX;
        this->posY = posY;
    };
};
```
	
MovementSystem updates positions base on velocities

``` cpp
class MovementSystem : public artemis::EntityProcessingSystem {
private:
    artemis::ComponentMapper<MovementComponent> velocityMapper;
    artemis::ComponentMapper<PositionComponent> positionMapper;

public:
    MovementSystem() {
        addComponentType<MovementComponent>();
        addComponentType<PositionComponent>();
    };

    virtual void initialize() {
        velocityMapper.init(*world);
        positionMapper.init(*world);
    };

    virtual void processEntity(artemis::Entity &e) {
        positionMapper.get(e)->posX += velocityMapper.get(e)->velocityX * world->getDelta();
        positionMapper.get(e)->posY += velocityMapper.get(e)->velocityY * world->getDelta();
    };

};
```
	
Usage:

``` cpp
int main(int argc, char **argv) {

    artemis::World world;
    artemis::SystemManager * sm = world.getSystemManager();
    MovementSystem * movementsys = (MovementSystem*)sm->setSystem(new MovementSystem());
    artemis::EntityManager * em = world.getEntityManager();

    sm->initializeAll();

    artemis::Entity & player = em->create();

    player.addComponent(new MovementComponent(2,4));
    player.addComponent(new PositionComponent(0,0));
    player.refresh();

    PositionComponent * comp = (PositionComponent*)player.getComponent<PositionComponent>();

    while(true){

        world.loopStart();
        world.setDelta(0.0016f);
        movementsys->process();

        std::cout << "X:"<< comp->posX << std::endl;
        std::cout << "Y:"<< comp->posY << std::endl;
        Sleep(160);
    }

    return 0;
}
```
### LOGS


- Sept 11, 2012:
	- [Fixed critical bug](https://github.com/vinova/Artemis-Cpp/commit/731d2c3e6f4afbd32e4d33f08f23373d62b91dd9): deleting World doesn't delete/reset all neccessary data,
which will lead to memory violation when a World is deleted and a new one is created.
- Sept 12, 2012:
	- Removed all C++11 feature usages.


### LISENCE

Copyright 2011 GAMADU.COM. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY GAMADU.COM ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL GAMADU.COM OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of GAMADU.COM.
