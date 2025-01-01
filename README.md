# Aura

Developed with Unreal Engine 5

## Part I: Introduction

### 1.1 Project Overview

Aura is a multiplayer action RPG game that is developed with Unreal Engine 5. The game is set in a
fantasy world where players can explore the world, fight monsters, and complete quests. The game
features a real-time combat system, character progression, and a rich story.

### 1.2 Project Goals

The goal of this project is to create a multiplayer action RPG game that is fun to play and has a
high level of polish. The game should have engaging gameplay, interesting characters, and a compelling
story. The game should also have a high level of visual fidelity and run smoothly on a variety of
hardware.

### 1.3 Project Scope

The scope of this project is to create a prototype of the game that showcases the core gameplay
mechanics and features. The prototype will include a small open world area that players can explore,
a combat system that allows players to fight monsters, and a quest system that gives players objectives
to complete. The prototype will also include a character progression system that allows players to
level up their characters and improve their abilities.

### 1.4 Project Timeline

The project will be developed over the course of 6 months. The first 3 months will be spent on
developing the core gameplay mechanics and features. The next 2 months will be spent on polishing
the game and adding additional content. The final month will be spent on testing and bug fixing.

## Part II: Project Setup and Character Creation

- Create a new project with the `Third Person` template

I will be using the `Third Person` template for this 
project. This template comes with a character that has a 
skeletal mesh and animations. The character is controlled 
by the player using the keyboard and mouse.

- Set Up the Editor and Project settings


- Import the Game Assets


- Create the Character Classes and Animations


- Set Up the Player Controller and Game Mode


- Case: Highlight the Enemy Character when we put the 
  cursor over it -- Implement the `OnHover` and `OnUnhover`
  functions in the `AuraCharacter` class to highlight the 
  enemy character when the cursor is over it.

### 2.1 UI (Widget, Widget Controller and Model)

#### Overview of the UI structure

How can we inform our players with their pawn's attributes? How to make them know their current health,
mana and note them when there's an interactable object in front of them. UI is important in game, which
can directly deliver your thoughts to your players.

UI is usually composed of many widgets, which are used to show information. Then, under the interface,
we have the widget controller to control the widget, and the model possess attributes to be shown.
From a software engineering perspective, these three parts should only have a one-way dependency, which
means the model should have no idea about the widget controller, and widget controller should not know
which widget it is related to. The relationship between these three parts is shown below:

![UI Structure](./Images/Relationship_between_UIs.png)

According to this picture, the widget is responsible for showing the data, and the

#### Widget Controller

If you try to search for the widget controller in all UE base c++ classes, you will find nothing.
Widget Controller is not an integrated base class in UE, so we should create it from scratch.

The base class of all widget controllers is `UWidgetController`, which is a subclass of `UObject
`. The `UWidgetController` class has a `UUserWidget` pointer to point to the widget it controls.
The `UWidgetController` class has a `UWidgetController` pointer to point to the widget controller
it belongs to. The `UWidgetController` class has a pure virtual function called `Init` to initialize
the widget controller. The `UWidgetController` class has a pure virtual function called `Update` to
update the widget controller. The `UWidgetController` class has a pure virtual function called `Destroy`
to destroy the widget controller.

## Part III: The GAS System

![GAS System](./Images/GAS_in_Multiplayer.png)
![GAS System](./Images/How_to_replicate.png)


### 3.1 The PlayerState

PlayerState is a class to record the state of a player, like health,
mana or other attributes. According to the figure above, the PlayerState
is mounted on the PlayerController to avoid character states being lost 
when the character is destroyed. Steps to create a PlayerState class is
followed:

* Create a new C++ class called `AuraPlayerState` that inherits from `APlayerState`
* Set the `NetUpdateFrequency` to higher value like 100.0f, the 
original value is too slow.
* Add the `AuraPlayerState` to your `GameMode` class

### 3.2 Multiplayer Game Ability System

#### When should we Init Ability Actor Info?
**Answer**: Must be done after possession (the Controller has been set
for the Pawn)

* Player-Controlled Character
  * ASC Lives on the Pawn (Both Owner and Avatar is the Pawn)
    * Server
    
      Called in `PossessedBy` server-only function.
    * Client
    
      Called in `AcknowledgePossession` client-only function.
  * ASC Lives on the PlayerState (Owner is the PlayerState, Avatar is the Pawn)
    * Server
    
      Called in `PossessedBy` server-only function.
    * Client
    
      Called in `OnRep_PlayerState` client-only function.
* AI-Controlled Character
  * ASC Lives on the Pawn (Both Owner and Avatar is the Pawn)
    * Server
    
      Called in `BeginPlay` server-only function.
    * Client
    
      Called in `BeginPlay` client-only function.

`PossessedBy` is a server-only function that is called 
when the Pawn is possessed by a Controller.

`AcknowledgePossession` is a client-only function that is
called when the possession has been established.

`OnRep_PlayerState` is a client-only OnRep-notify function that is 
called when the PlayerState is available on the client.

<mark>!! Note</mark>: The `InitAbilityActorInfo` function should be called with **OwnerActor**'s
**Owner** to be a **Controller**. If it's not, then manually call `SetOwner` function
to set the **Owner** of **OwnerActor** to be a **Controller**.


### 3.3 Gameplay Effect

#### Overview of the Gameplay Effect

The Gameplay Effect is a class that is used to define the effect of an ability. It can be used to
define the damage, healing, or any other effect that an ability can have. The Gameplay Effect
can be applied to a target to change its state. The Gameplay Effect can be applied instantly,
over a duration, or periodically. The Gameplay Effect can also be infinite, which means it will
last forever until it is removed manually.

##### Gameplay Effect & Gameplay Effect Spec

The Gameplay Effect is a class that defines the effect of an ability. The Gameplay Effect Spec
is a class that defines the parameters of the Gameplay Effect. The Gameplay Effect Spec is used
to create a Gameplay Effect. The Gameplay Effect Spec can be created from a Gameplay Effect
class, or it can be created from a Gameplay Effect Spec class.

#### Instant Gameplay Effect

#### Duration Gameplay Effect

#### Periodic Gameplay Effect

#### Infinite Gameplay Effect