//-- MyEngine - DIG DUG - Cem's Edition --//
//-- 2DAE06 - ASSIGNMENT - PROG04 --//

--------------------------------------------------------------------------
--GITHUB LINK--
https://github.com/Cem-Alagozlu/MyEngine
---------------

----------------------PROJECT INFORMATION BELOW---------------------------

I study at Kortrijk, Howest, Digital Arts and Entertainment and I'm in the
fourth semester, 

for our last semester for PROG04, we had to create our own engine and
recreate Dig Dug, 

The assignment is part of our end score (50%)

If you have any questions, feel free to send me a message. 




-----------------------ENGINE INFORMATION BELOW---------------------------

//--COMPONENTS--//
--------------------------------------------------------------------------

The engine has several components, they are enough to create 
a complete 2D basic game like Dig Dug.

The following components are included:
- BaseComponent
- CollisionComponent
- FPSComponent
- SpriteComponent
- TextDrawComponent
- TextureComponent
- TransformComponent

//--BaseComponent--//
Every component inherits from the base component, 
this is your blueprint to start with if you want to add new components


//--CollisionComponent--//
This component will give your object handy functions to check
if it has collision with another object that has a collision box.

it works with overlapping functions & callbacks

You can also choose between static & dynamic collision
(this will change the way how your collision gets computed)

static = less computing time
dynamic = more computing time

How does it work?
with two rectfs overlapping each other


//--FPSComponent--/
This is a simple component that checks & gives you the FPS 

//--SpriteComponent--/
This is a component based on an engine we got last year from our school, but I changed it 
in a way so you can import it in the minigin,
also new functions added! 

you can mirror & set the angle of your sprites so you don't need a large sprite sheet
for all your directions


//--TextDrawComponent--//
this component takes a string as parameter, you simply give the source of your font
(in your dir) and the class itself will do the magic! 

after that , you can use the font of your choice to render the text you want.


//--TextureComponent--//
Here you can add a static image to your game object and use it in any way possible 
if you combine it with the TransformComponent


//--TransformComponent--//
I didn't add too much to it
i've just added Scaling to it


//--FSM--//
--------------------------------------------------------------------------
I've got the inspiration from UNREAL ENGINE, so i made a
simplefied version of the state machines they use. 

basically, you have:
- State class
- StateMachine class
- Blackboard class


//--StateClass--//
In the state class (base class)
you get a few functions, 
ENTER	-> to enter the state, (how you can enter it)
EXIT	-> when you exit the state,(what will happen if you exit)

You also can add the transition
-> which state is accessible from which state;
example, you can go from run to idle, 
but you cant go from jump to idle, 

here you can give your blackboard (more info later on)

//--StateMachineClass--//
This class will "merge" everything together, 
which state can transition to which state,
also which state gets which blackboard info, etc..


//--Blackboard--//

In the state machine, you don't create new variables, 
all of this will be made in the blackboard, and here 
the variables are accessible by every state (you predefine which state can have which blackboard)

//--HELPERS--//
--------------------------------------------------------------------------
You have a few helpers, 
Events -> for achievements (used for oberver pattern)
Font -> to do your font magic with the TextDrawComponent
Observer -> base to create observers (so far , one in game for achievements)
Singleton
Timing -> basic timing functions, to get elapsedSec & FPS

//--STRUCTS--//

Here, i've created a Vector2f variable that gets x,y values, 
,included overload operators: +,-,==

included distance calculator (for A.I.)
included Normalize calculator (for A.I.)

included Color3i
included Rectf (for sprites & collision)


//--MAIN--//
--------------------------------------------------------------------------
has the basic files for your main, 
the collective includes of what you use in the engine, for example:
sstream, map, algorithm, etc... just so you don't need to include
it everytime

//--MANAGER--//
--------------------------------------------------------------------------
this map has some handy classes, 
like : 
Commands -> input for keyboard & controller (keyboard is not 100% functional)
CommandManager -> goes hand in hand with the commands class & the input manager class
Input manager -> manages your input (with callbacks)
Physics manager-> to manage your physics with your Collision component RECTS
Thread 
&
Thread Manager 
-> so far this is only being used for the movement of Fygar & Pooka


//--SceneGraph--//
--------------------------------------------------------------------------
contains your GameObject (the main player of our engine)
its not final & also I inherit GameObject in different classes to create
prefabs

Scene & Scene manager, manages your scenes, you can switch between them
(same implementation as in Overlord Engine (engine from our school DAE))

//--SOUND--//
--------------------------------------------------------------------------
Every game needs music & sound effects! this is a mix of them, so you can
add new songs & sfx to two maps, 
these maps are being managed by the sound manager, you can also controll 
the volume with the manager & stop every sound at any time,
its a singleton, because you only need one sound manager.

TLDR; this is a basic summary of the engine, there is alot more to tell about it,
the best thing to do is, dive in the engine by your self, feel free to ask a question at any time!


